from tkinter import *
from PIL import Image, ImageTk
import serial
import time                     # pour le délai d'attente entre les messages
import string
import CSV
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

#ser = serial.Serial('/dev/ttyUSB0', 9600)

debugOn=1

ser = serial.Serial('/dev/ttyACM0', 9600)
print(ser.name)
###############################################################
class FenetreCarac():
    def __init__(self):
        #print("carac f")
        self.root = Tk()
        self.root.overrideredirect(1)
        self.frame = Frame(self.root, width=800, height=480, borderwidth=2, relief=RAISED)
        self.frame.pack_propagate(False)
        self.frame.pack()
        framecarac= LabelFrame(self.frame, text="Caracterisation PC",borderwidth=10,labelanchor= N, font='freemono 20 bold')
        framecarac.pack(fill="both", expand="yes")
        self.bStartCarac = Button(self.frame, text="Start", command=self.cStartCarac, height=10, width=15, bg="orange", font='freemono 20 bold')
        self.bStartCarac.place(x= 70, y= 110)


        
        self.bQuit = Button(self.frame, text="Quit", command=self.root.destroy)
        self.bQuit.place(x= 750,y= 450)
    def cStartCarac(self):
        if (debugOn == 1):
            debug.Info("Start Caracterisation")
###############################################################
class FenetreCycle():
    def __init__(self):
        #print("cycle f")
        self.root = Tk()
        self.root.overrideredirect(1)
        self.frame = Frame(self.root, width=800, height=480, borderwidth=2, relief=RAISED)
        self.frame.pack_propagate(False)
        self.frame.pack()  
        framecycle= LabelFrame(self.frame, text="cycle Auto",borderwidth=10,labelanchor= N, font='freemono 20 bold')
        framecycle.pack(fill="both", expand="yes")
        self.bStartCycle = Button(self.frame, text="Start", command=self.cStartCycle, height=10, width=15, bg="orange", font='freemono 20 bold')
        self.bStartCycle.place(x= 70, y= 110)                  
        
        self.bQuit = Button(self.frame, text="Quit", command=self.root.destroy)
        self.bQuit.place(x= 750,y= 450)
    def cStartCycle(self):
        if (debugOn == 1):
            debug.Info("Start Cycle Auto")
###############################################################
class FenetrePrincipal():
    
    def __init__(self):
        self.root = Tk()
        self.root.overrideredirect(1)
        self.frame = Frame(self.root, width=800, height=480, borderwidth=2, relief=RAISED)
        self.frame.pack_propagate(False)
        self.frame.pack()
        #################
        frameChoix= LabelFrame(self.frame, text="Choix du mode",borderwidth=10,labelanchor= N, font='freemono 20 bold')
                ######
        image = Image.open('nom_du_fichier.png')
        Logotag = ImageTk.PhotoImage(image)
        canvas = self.Canvas()
        canvas = self.create_image(200,500, image=Logotag)
        canvas.pack()


        label = self.Label(fenetre, image=Logo)
        label.pack()
        #################        
        labelcarac=Label(self.frame, text="Carac. \nauto",font='freemono 20 bold')
        labelcarac.place(x=80, y=80)
        self.bCarac = Button(self.frame, text="Carac. \nauto", command=self.cCarac, height=10, width=15, bg="orange", font='freemono 20 bold')
        self.bCarac.place(x= 70, y= 110)
        #################
        labelcycle=Label(self.frame, text="Cycle auto",font='freemono 20 bold')
        labelcycle.place(x= 450, y= 80)
        self.bCycle = Button(self.frame, text="start", command=self.cCycle, height=10, width=15, bg="green", font='freemono 20 bold')
        self.bCycle.place(x=440, y=110)
        #################       
        self.bQuit = Button(self.frame, text="Quit", command=self.root.destroy)
        self.bQuit.place(x= 750,y= 450)    
    #################         
    def cCarac(self):                 # fonction de caracterisation automatique de la valve pc
        if (debugOn == 1):
            debug.Info("Caracterisation")
        FenetreCarac()
        comSerial.sendSerial(self,b'A')
        comSerial.receiveSerial(self,'a')
    def cCycle(self):                 # fonction de cycle automatique du fonctionnement de la centrale.
        if (debugOn == 1):
            debug.Info("cycle Auto")       
        FenetreCycle()
        comSerial.sendSerial(self,b'a')
        comSerial.receiveSerial(self,'NULL')
class comSerial():
###############################################################
    #ser = serial.Serial('/dev/ttyUSB0', 9600)
    def __init__(self):
       # ser = serial.Serial('/dev/ttyUSB0', 9600)
        ser = serial.Serial('/dev/ttyACM0', 9600)
        time.sleep(2)                 # On attend un peu, pour que l'Arduino soit prêt.
 
    def sendSerial(self, message):
        if (debugOn == 1):
            debug.Info("send message: " + str(message))  
        #print("send message")
        ser.write(message)
        
    def receiveSerial(self, messageIN):    
        if(ser.in_waiting >0):
            messageIN = ser.readline()
            messageIN= messageIN.rstrip()# supprime les \n\t\r
            messageIN= messageIN.decode()# convertie en str?
            
        if (debugOn == 1):
            debug.Info("receive message: " + str(messageIN)) 
            #print(messageIN)

class debug():                   # Utiliser pour le debugage, genere les "print" en fonction de la variable debugOn
    def __init__(self):
        print("DEBUG")
    def Info(debuginfo):    
        print("INFO: "+debuginfo)
    def Warning(debuginfo):
        print("WARN: "+debuginfo)
    def Error(debuginfo):
        print("ERRO: "+debuginfo)



class WriteCSV():
    def __init__(self):
        print("create CSV file")

    def Create
        with open("datafile.csv", "w") as new_file:
        csv_writer = csv.writer(new_file)

        line_count = 0
        while True:
            # Strip whitespace on the left and right side
            # of the line
            line = ser.readline().strip()

            # Check whether line starts with a B and ends
            # with an E, and ignore it otherwise
            is_valid = line.startswith("B") and line.endswith("E")
            if not is_valid:
                print("Ignored invalid line: " + line)
                continue

            # Strip B and E
            datalog_line = line[1:-1]

            # Split the string "180,3600,1234" into a list ["180", "3600", "1234"]
            datalog_triplet = datalog_line.split(",")
            if len(datalog_triplet) != 3:
                print("Ignored invalid data line: " + datalog_line)
                continue

            # Convert the numbers from string format to integer
            courantPC = int(datalog_triplet[0])
            courantPGO = int(datalog_triplet[1])
            z = int(datalog_triplet[2])

            # Write XYZ to the CSV file
            csv_writer.writerow([courantPC, courantPGO, z])

            # Increment the line count, and stop the loop
            # once we have 10 lines
            line_count += 1
            if line_count >= 10:
                break







app = FenetrePrincipal()
app.root.mainloop()
