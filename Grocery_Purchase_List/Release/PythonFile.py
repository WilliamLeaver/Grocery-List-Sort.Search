import re
import string


def DailyList():
    SaleList = {}
    f = open("List.txt", "r")
    for x in f:
        if x.strip() in SaleList:
            SaleList[x.strip()] = SaleList[x.strip()] + 1
        if x.strip() not in SaleList:
            SaleList[x.strip()] = 1
    f.close
    for x, y in sorted(SaleList.items()):
        print(x + ": " + str(y))
        

def DailyItem(v):
    counter = 0
    f = open("List.txt", "r")
    for x in f:
        if x.strip() == v:
            counter = counter + 1
    f.close
    return counter

def DailyHisto():
    SaleList = {}
    f = open("List.txt", "r")
    for x in f:
        if x.strip() in SaleList:
            SaleList[x.strip()] = SaleList[x.strip()] + 1
        if x.strip() not in SaleList:
            SaleList[x.strip()] = 1
    f.close
    f = open("frequency.dat", 'w')
    for x in sorted(SaleList, key=SaleList.get, reverse=False):
         f.write(x + " " + str(SaleList[x]) + "\n")
    f.close


