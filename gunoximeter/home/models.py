from operator import truediv
from unicodedata import name
from django.db import models

# Create your models here.

class datasheet(models.Model):
    sno = models.AutoField(primary_key=True)
    name = models.CharField(max_length=255)
    phone = models.CharField(max_length=13)
    date = models.DateField()
    city = models.CharField(max_length=20)
    areaName = models.CharField(max_length=100)
    age = models.IntegerField()
    vacination = models.CharField(max_length=40)
    temperature = models.CharField(max_length=10)
    spo2 = models.CharField(max_length=10)

    def __str__(self) :
        return 'Area ' + self.areaName + ' -->' + self.city
