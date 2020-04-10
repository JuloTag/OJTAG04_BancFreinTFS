
#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Le Raspbery Pi demande une information à l'Arduino,
# puis il affiche la réponse à l'écran
#
# http://electroniqueamateur.blogspot.com/2014/05/communication-par-usb-entre-raspberry.html

import serial                   # bibliothèque permettant la communication série
import time                     # pour le délai d'attente entre les messages
import string

ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)                   #on attend un peu, pour que l'Arduino soit prêt.

while True:                     # boucle répétée jusqu'à l'interruption du programme
    ser.write(b'A') # envoi le code ascii 65
    messageIN= ser.readline()
    messageIN= messageIN.rstrip()# supprime les \n\t\r
    messageIN= messageIN.decode()# convertie en str?
   # print(messageIN)       #on affiche la réponse
    time.sleep(1)               # on attend pendant 1 seconde
    ser.write(b'a') # envoi le code ascii 97
    messageIN= ser.readline()
    messageIN= messageIN.rstrip()# supprime les \n\t\r
    messageIN= messageIN.decode()# convertie en str?
    print(messageIN)  
    time.sleep(1)     
    