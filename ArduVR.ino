// Module de commande relais via commande http
//http://192.168.0.56/?d=3p=1w=10

//Version avec contr^le d'envoi en cascade propre au mode TCP/IP


#include <EtherCard.h>
#include <IPAddress.h>


#define RELAIS_1_PIN A0
#define RELAIS_2_PIN A1
#define RELAIS_3_PIN A2
#define RELAIS_4_PIN A3
#define RELAIS_5_PIN A4
#define RELAIS_6_PIN A5
#define RELAIS_7_PIN 6  // On ne peut pas utiliser A6 Input seulement
#define RELAIS_8_PIN 7  // On ne peut pas utiliser A7 Input seulement

#define LED_PIN 13 // LED intégrée à la carte


static BufferFiller bfill;  // used as cursor while filling the buffer
byte Ethernet::buffer[500];

int cpt=0;
static uint32_t tempo = 0;
int lastDevice = 0;

/***************** Network configuration ********************/
uint8_t mymac[6] = { 0x54,0x55,0x58,0x10,0x00,0x25 };
uint8_t myip[4] = { 192,168,0,135 };
uint8_t gwip[4] = { 192,168,0,254};
  
/*******************************************************************************/

 static int getArg(const char* data, const char* key,char sortie[],int nbChar) {
    if (ether.findKeyVal(data + 6, sortie, nbChar, key) > 0){
        return 0;
    }else{
        return -1;
    }
}

const char page[] PROGMEM =
"HTTP/1.0 503 Service Unavailable\r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head><title>"
    "Module VR!"
  "</title></head>"
  "<body>"
    "<h3>command accept!</h3>"
  "</body>"
"</html>";
/*******************************************************************************/

void setup()
{
  // Serial debugging
  Serial.begin(115200);
  Serial.println(F("-- PROG V0.1.2 du 13/01/2018 --"));
  Serial.println(F("-- Compil with Arduino 1.6.3 --"));
  Serial.println(F("-=- Setup arduino begin -=- \n"));
  
  Serial.println(F("ENCL initialisation DHCP \n"));
//  ether.begin(sizeof Ethernet::buffer, mymac,10);
//  ether.staticSetup(myip, gwip);
  
   if (ether.begin(sizeof Ethernet::buffer, mymac,10) == 0){ 
     Serial.println( F("Failed to access Ethernet controller"));
     }  
   
   if (!ether.dhcpSetup()){
     Serial.println(F("DHCP failed switch static ip"));
     ether.staticSetup(myip, gwip);
     }
   
   ENC28J60::disableMulticast(); //disable multicast filter means enable multicast reception

  // Affichage
    ether.printIp("IP:  ", ether.myip);
    ether.printIp("GW:  ", ether.gwip);  
    ether.printIp("DNS: ", ether.dnsip);  
  
 // Set pin's mode
    pinMode(RELAIS_1_PIN, OUTPUT);
    pinMode(RELAIS_2_PIN, OUTPUT);
    pinMode(RELAIS_3_PIN, OUTPUT);
    pinMode(RELAIS_4_PIN, OUTPUT);
    pinMode(RELAIS_5_PIN, OUTPUT);
    pinMode(RELAIS_6_PIN, OUTPUT);
    pinMode(RELAIS_7_PIN, OUTPUT);
    pinMode(RELAIS_8_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    
    digitalWrite(RELAIS_1_PIN, LOW);
    digitalWrite(RELAIS_2_PIN, LOW);
    digitalWrite(RELAIS_3_PIN, LOW);
    digitalWrite(RELAIS_4_PIN, LOW);
    digitalWrite(RELAIS_5_PIN, LOW);
    digitalWrite(RELAIS_6_PIN, LOW);
    digitalWrite(RELAIS_7_PIN, LOW);
    digitalWrite(RELAIS_8_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  
}


void loop()
{
  word len = ether.packetReceive();
  word pos = ether.packetLoop(len);
  

  if (pos) {
    cpt++;
    char* data = (char *) Ethernet::buffer + pos;

    if (data[5] == '?') {



      char cdevice[4];  // permet 3 chiffres
      getArg(data,"d",cdevice,sizeof cdevice);
      
      char cpulse[4];  // permet 3 chiffres
      getArg(data,"p",cpulse,sizeof cpulse);
      
      char cwait[5];   // permet 4 chiffres
      getArg(data,"w",cwait,sizeof cwait);
      
      int device = atoi(cdevice);
      int pulse = atoi(cpulse);
      int wait = atoi(cwait);
      
   // ether.httpServerReplyAck(); // send ack to the request
    // Renvoi d'une page obligatoire pour vider le buffer
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    ether.httpServerReply(sizeof page - 1);
      
      
      // Implémenter un contrôle de validite de la commande
      
      Serial.println("\n***********************************************");
      Serial.print("\npos : ");
      Serial.println(pos);
      Serial.print("cpt : ");
      Serial.println(cpt);
     
      printCommande (device, pulse, wait);
     
      if ((millis() < tempo) && (device == lastDevice)) {
        
        Serial.println("--- COMMAND FILTERED ACTION TO SHORT ---");
      } else {
        lastDevice = device;
        Traite_message(device, pulse, wait);
        tempo = millis() + 2000;
      }
          
      
    
    // On fixe le delais avant prise en compte d'une autre demande
    //delay(1000);
    }
   }

}
