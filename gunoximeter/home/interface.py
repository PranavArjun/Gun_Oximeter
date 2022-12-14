import serial
import time
import schedule
from django.http import JsonResponse

# from vpython import*


import numpy as np
 

 
 
# boxX=10
# # boxY=6
# boxZ=.4
# offsetRight = boxX/2+2
# myCase=box(color=color.white,size=vector(boxX,boxY,boxZ),pos=vector(offsetRight,0,-boxZ/2))
 
# arrowLength=boxY-2
# arrowWidth=.15
# arrowz = .25
# myArrow=arrow(length=arrowLength,shaftwidth=arrowWidth,color=color.red,pos=vector(offsetRight,-0.9*boxY/2,arrowz))
 
# tickL=.1
# tickW=.02
# tickH=.02
 
# for theta in np.linspace(5*np.pi/6,np.pi/6,6):
#     tickMajor=box(color=color.black,pos=vector(arrowLength*np.cos(theta),arrowLength*np.sin(theta),0),size=vector(tickL,tickW,tickH),axis=vector(arrowLength*np.cos(theta),arrowLength*np.sin(theta),0))


# digValue=label(text='50',height=20,box=False,pos=vector(0,-2.5,2))
# bulb=sphere(radius=1,color=color.red,pos=vector(0,-3,0))
# cyl=cylinder(radius=.6,color=color.red,axis=vector(0,1,0),length=6,pos=vector(0,-3,0))
# bulbGlass=sphere(radius=1.2,color=color.white,opacity=.25,pos=vector(0,-3,0))
# cylGlass=cylinder(radius=.8,color=color.white,axis=vector(0,1,0),opacity=.25,length=6,pos=vector(0,-3,0))
# for temp in range(0,115,10):
#     tickPos=4.5/115*temp+1.5
#     tick=cylinder(radius=.7,color=color.black,length=.1,axis=vector(0,1,0),pos=vector(0,tickPos-3,0))
#     label=text(text=str(temp),color=color.white,pos=vector(-2,tickPos-3,0),height=.3)






# while True:
#     arduino = serial.Serial('com3', 9600)
#     print('Established serial connection to Arduino')
#     data = arduino.readline()
#     data = str(data,'utf')
#     data=data.strip('\r\n')
#     data=data.split(",")
   
    #decalring the varibales
    # dist=(data[0])
    # temp = (data[1])
    # spo2 = (data[2])

    # temp2 = float(temp)
    # len=(4.5/115)*temp2+1.5
    # cyl.length=len
    # digValue.text=str(temp)

    # potVal = float(spo2)
    # theta=-2*np.pi/3069*potVal+5*np.pi/6
    # myArrow.axis=vector(arrowLength*np.cos(theta),arrowLength*np.sin(theta),0)

    
    # arduino.close()
    
    # print('<---------------------------->')
    
    # print("Temp = " , temp)
    # print("dist = " , dist)
    # print("spo2 = " , spo2)