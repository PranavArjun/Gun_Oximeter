import serial
import time
import schedule
from django.http import JsonResponse
import numpy as np

def Arduino(request):
    arduino = serial.Serial('com3', 9600)
    print('Established serial connection to Arduino')
    data = arduino.readline()
    data = str(data,'utf')
    data=data.strip('\r\n')
    data=data.split(",")

    # Decalring the varibales
    dist=(data[0])
    temp = (data[1])
    spo2 = (data[2])

    arduino.close()
    return JsonResponse({'temp': temp, 'spo2': spo2})
        