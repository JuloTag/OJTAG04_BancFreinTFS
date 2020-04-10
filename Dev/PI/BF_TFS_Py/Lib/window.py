from tkinter import *

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