
void printCommande (int device, int pulse, int wait){
      Serial.print("\nDevice=");
      Serial.print(device);
      
      Serial.print(" | pulse=");
      Serial.print(pulse);
      
      Serial.print(" | wait=");
      Serial.print(wait);
      
      Serial.println();
  }

void Traite_message (int device, int pulse, int wait){
  
  switch (device){
    case 1:
      Serial.println("cas 1");
      Commande_relais (RELAIS_1_PIN, pulse, wait);
      break;
      
    case 2:
      Serial.println("cas 2");
      Commande_relais (RELAIS_2_PIN, pulse, wait);
      break;
      
    case 3:
      Serial.println("cas 3");
      Commande_relais (RELAIS_3_PIN, pulse, wait);
      break;
      
    case 4:
      Serial.println("cas 4");
      Commande_relais (RELAIS_4_PIN, pulse, wait);
      break;

    case 5:
      Serial.println("cas 5");
      Commande_relais (RELAIS_5_PIN, pulse, wait);
      break;
      
    case 6:
      Serial.println("cas 6");
      Commande_relais (RELAIS_6_PIN, pulse, wait);
      break;
      
    case 7:
      Serial.println("cas 7");
      Commande_relais (RELAIS_7_PIN, pulse, wait);
      break;
      
    case 8:
      Serial.println("cas 8");
      Commande_relais (RELAIS_8_PIN, pulse, wait);
      break;      
        
    case 9:
      Serial.println("cas 9");
      for(int i = 0 ; i < pulse ; i++ ){
        digitalWrite(RELAIS_1_PIN, HIGH);  
        digitalWrite(RELAIS_2_PIN, HIGH);  
        digitalWrite(RELAIS_3_PIN, HIGH);  
        digitalWrite(RELAIS_4_PIN, HIGH);  
        digitalWrite(RELAIS_5_PIN, HIGH);  
        digitalWrite(RELAIS_6_PIN, HIGH);  
        digitalWrite(RELAIS_7_PIN, HIGH); 
        digitalWrite(RELAIS_8_PIN, HIGH);  
        delay(wait);    // waits for XX
        digitalWrite(RELAIS_1_PIN, LOW);  
        digitalWrite(RELAIS_2_PIN, LOW);  
        digitalWrite(RELAIS_3_PIN, LOW);  
        digitalWrite(RELAIS_4_PIN, LOW);  
        digitalWrite(RELAIS_5_PIN, LOW);  
        digitalWrite(RELAIS_6_PIN, LOW);  
        digitalWrite(RELAIS_7_PIN, LOW); 
        digitalWrite(RELAIS_8_PIN, LOW); 
        delay(wait);  
        }
      break;  
      
      
    case 10:
      Serial.println("cas 10");
      for(int i = 0 ; i < pulse ; i++ ){
        digitalWrite(RELAIS_1_PIN, HIGH);  
        digitalWrite(RELAIS_2_PIN, HIGH);  
        digitalWrite(RELAIS_3_PIN, HIGH);  
        digitalWrite(RELAIS_4_PIN, HIGH);  
        delay(wait);    // waits for XX
        digitalWrite(RELAIS_1_PIN, LOW);  
        digitalWrite(RELAIS_2_PIN, LOW);  
        digitalWrite(RELAIS_3_PIN, LOW);  
        digitalWrite(RELAIS_4_PIN, LOW);  
        delay(wait);  
        }
      break;
    
    case 11:
      Serial.println("cas 11");
      for(int i = 0 ; i < pulse ; i++ ){
        digitalWrite(RELAIS_5_PIN, HIGH);  
        digitalWrite(RELAIS_6_PIN, HIGH);  
        digitalWrite(RELAIS_7_PIN, HIGH);  
        digitalWrite(RELAIS_8_PIN, HIGH);  
        delay(wait);    // waits for XX
        digitalWrite(RELAIS_5_PIN, LOW);  
        digitalWrite(RELAIS_6_PIN, LOW);  
        digitalWrite(RELAIS_7_PIN, LOW); 
        digitalWrite(RELAIS_8_PIN, LOW); 
        delay(wait);  
        }
      break;
   
    case 12:
      Serial.println("cas 12");
      for(int i = 0 ; i < pulse ; i++ ){
        digitalWrite(RELAIS_1_PIN, HIGH);  
        digitalWrite(RELAIS_7_PIN, HIGH);  
        digitalWrite(RELAIS_8_PIN, HIGH); 
        delay(wait);    // waits for XX
        digitalWrite(RELAIS_1_PIN, LOW);  
        digitalWrite(RELAIS_7_PIN, LOW);  
        digitalWrite(RELAIS_8_PIN, LOW);  
        delay(wait);  
        }
      break;    

    case 13:
      Serial.println("cas 13");
      for(int i = 0 ; i < pulse ; i++ ){
        digitalWrite(RELAIS_2_PIN, HIGH);  
        digitalWrite(RELAIS_3_PIN, HIGH); 
        digitalWrite(RELAIS_4_PIN, HIGH);  
        digitalWrite(RELAIS_5_PIN, HIGH);  
        digitalWrite(RELAIS_6_PIN, HIGH);  
        delay(wait);    // waits for XX
        digitalWrite(RELAIS_2_PIN, LOW);  
        digitalWrite(RELAIS_3_PIN, LOW); 
        digitalWrite(RELAIS_4_PIN, LOW);  
        digitalWrite(RELAIS_5_PIN, LOW);  
        digitalWrite(RELAIS_6_PIN, LOW);  
        delay(wait);  
        }
      break;  
      
    default:
      // if nothing else matches, do the default
      // default is optional
      Serial.println(" -*-*- ERROR UNKNOW COMMAND -*-*-");
      break;
  }
}
  
  
  
  
  
  
  
  /***********************************************
   Commande_relais
   Commande de relais dans differents modes
   Input : Pin relais (int)
           impulsion(vrai)/(faux) (byte)
           Nb d'impulsion (int)
           Temps actif (ms) (int)
   Output : code (int) : 0 = success
                         not 0 = not a valid message
***********************************************/    
  int Commande_relais (int Pin_relais, int Nb_imp, int Tps_actif){
    
      Serial.print("Relais=");
      Serial.print(Pin_relais);
      
      Serial.print(" | pulse=");
      Serial.print(Nb_imp);
      
      Serial.print(" | delais=");
      Serial.print(Tps_actif);
      
      Serial.println();
    
     int i; 
     for(i=0;i<Nb_imp;i++){
       
       Serial.println("\nRelais ON");
       digitalWrite(LED_PIN, HIGH);   
       digitalWrite(Pin_relais, HIGH);
        
       delay(Tps_actif);                        // waits for a second
       
       Serial.println("Relais OFF"); 
       digitalWrite(LED_PIN, LOW);
       digitalWrite(Pin_relais, LOW);
       
       delay(Tps_actif);  
     }
  }   
