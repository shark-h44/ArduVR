# ArduVR
ArduVR esst un programme qui permet de contrôler une carte 8 relais en mode impulsionnel depuis une liaison Etherne, le tout en utilisant des commandes http.
Ce système à été conçu pour piloter des volets roulants équipés de modules Yokis MVR500E via JEEDOM.

## Matériel nécessaire
- Une carte Arduino Nano (ou autre en adaptant le code).
- Une carte ENC28J60 pour la liaison Ethernet
- Une carte 8 relais.
- Jeedom (option)
- Modules volets roulant MVR500e (option)
- des diodes en cas de double commande des modules Yokis (option)

## Exemple de commande
Commande du relais 1 (3 impulsions de 10ms) : http://IPArduino/?d=1p=3w=10
Paramétres utilisés dans la commande
d : N° de relais (device)
p : Nombre d'impulsions (pulse)
w : temps d'attente entre chaque impulsion en millisecondes (wait)

## Limitation et amélioration
Ce programme est trés simpliste, il est dépourvu d'interface web, mais fonctionne sans bug (tourne depuis plus depuis 2016)
Le programme home Automation disponible dans mon dépôt reprend les fonctionnalitées développées dans ce programme (en cour de développement)
