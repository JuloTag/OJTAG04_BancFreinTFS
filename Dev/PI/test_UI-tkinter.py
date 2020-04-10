#!/usr/bin/python

from tkinter import *
from tkinter.ttk import Combobox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import pandas as pd

class Window(Frame):
    def __init__(self, master=None):
        Frame.__init__(self, master)
        self.master = master
        
Data1 = {'Country': ['US','CA','GER','UK','FR'],
        'GDP_Per_Capita': [45000,42000,52000,49000,47000]
       }

df1 = DataFrame(Data1, columns= ['Country', 'GDP_Per_Capita'])
df1 = df1[['Country', 'GDP_Per_Capita']].groupby('Country').sum()

        
        

# initialize tkinter
mainWindow = Tk()
app = Window(mainWindow)
# add widgets here
lbl=Label(mainWindow, text="This is Label widget", fg='red', font=("Helvetica", 16))
lbl.place(x=60, y=50)
btn=Button(mainWindow, text="This is Button widget", fg='blue')
btn.place(x=80, y=100)
txtfld=Entry(mainWindow, text="This is Entry Widget", bd=5)
txtfld.place(x=80, y=150)

var = StringVar()
var.set("one")
data=("one", "two", "three", "four")
cb=Combobox(mainWindow, values=data)
cb.place(x=60, y=250)

lb=Listbox(mainWindow, height=5, selectmode='multiple')
for num in data:
    lb.insert(END,num)
lb.place(x=250, y=250)

v0=IntVar()
v0.set(1)
r1=Radiobutton(mainWindow, text="male", variable=v0,value=1)
r2=Radiobutton(mainWindow, text="female", variable=v0,value=2)
r1.place(x=300,y=50)
r2.place(x=380, y=50)
                
v1 = IntVar()
v2 = IntVar()
C1 = Checkbutton(mainWindow, text = "Cricket", variable = v1)
C2 = Checkbutton(mainWindow, text = "Tennis", variable = v2)
C1.place(x=300, y=100)
C2.place(x=380, y=100)


mainWindow.title('Banc Frein TFS')
mainWindow.geometry("800x800+10+40")
mainWindow.mainloop()
