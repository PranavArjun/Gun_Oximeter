from turtle import home
from unicodedata import name
from django.shortcuts import render,HttpResponse
from home.models import datasheet
import home.interface
import requests

def index(request):
    res = requests.get("http://127.0.0.1:5000/")
    data = res.json()
    temp = data.get("temp")
    spo2 = data.get("spo2")
    if request.method=='POST':
        name=request.POST['name']
        phone=request.POST['phone']
        date=request.POST['date']
        city=request.POST['city']
        areaName=request.POST['areaName']
        age=request.POST['age']
        vacination=request.POST['vact']

        res = requests.get("http://127.0.0.1:5000/")
        data = res.json()
        temp = data.get("temp")
        spo2 = data.get("spo2")
        info = datasheet(name=name , phone=phone , date=date , city=city , areaName=areaName , age=age , vacination=vacination, temperature=temp,spo2=spo2)
        info.save()
    # return render(request,'index.html',{'variable': temp, 'variable2': spo2})
    return render(request,'index.html',{'variable': temp, 'variable2': spo2})


