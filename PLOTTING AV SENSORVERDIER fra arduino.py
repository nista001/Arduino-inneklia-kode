#Henter inn biblotekene som brukes senere i koden
from pylab import *
import pylab as py
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker


#Åpner filen som målingene er lagret på
fil=open("SENSORVERDIERons.txt", "r")

#Setter arrays for verdiene
tid=[]
luftfuktighet=[]
temp=[]
CO2=[]

#Henter verdier fra filen 
for rad in fil:
    data=rad.strip().split(",")
    tid.append(float(data[0]))
    luftfuktighet.append(float(data[1]))
    temp.append(float(data[2]))
    CO2.append(float(data[3])*3.6)

#Setter at N er lik antall målinger og setter arrays med N verdier 
N=len(tid)
y=py.zeros(N) 
b=py.zeros(N) 
c=py.zeros(N)
d=py.zeros(N)
Tid=py.zeros(N)
maxx=py.zeros(N) 
minst=py.zeros(N)
h=py.zeros(N)
x=py.zeros(N)
w=py.zeros(N)
hours=py.zeros(N)
minutes=py.zeros(N)
time=py.zeros(N)
TIME=[]

#For-løkke som setter starttiden av målingene til null 
for i in range(N):
    Tid[i]=tid[i]-1249
    
    #Finner summen av de forskjellige variablene 
    c[i]=c[i-1]+temp[i]
    d[i]=d[i-1]+CO2[i]
    x[i]=x[i-1]+luftfuktighet[i]
    
    #Regner ut tiden i minutter om til klokke timer 
    hours = int((Tid[i]/60))
    minutes = int ((Tid[i]) % 60)
    if hours<2:
        time=('0{hours}:{minute}'.format(hours=hours+8, minute=minutes))
    else:
        time=('{hours}:{minute}'.format(hours=hours+8, minute=minutes))
    
    TIME.append(time)
 
#Finner gjennomsnitt av variablene og setter xakser for forskjellige grenseverdier hentet fra helsedirektoratet 
for i in range(N):
    x[i]=x[N-1]/(N)
    y[i]=c[N-1]/(N)
    b[i]=d[N-1]/(N)
    maxx[i]=24
    minst[i]=20
    h[i]=1000
    w[i]=30


#Her kan du plotte Tempratur
    
plt.plot(TIME,temp, label = " Data temp")
#plt.plot(TIME, y, label = "Snitt temp")
#plt.plot(TIME, maxx, label = "Ideell max temp")
#plt.plot(TIME, minst, label = "Ideell minst temp")
#title('tempratur')
#xlabel('tid')
#ylabel('tempratur i celsius')
    
    
#Her kan du plotte CO2
    
#plt.plot(TIME, CO2, label = "CO2 i PPM")
#plt.plot(TIME, b, label = "snitt CO2")
#plt.plot(TIME,h, label = "Max CO2")
#title('CO2')
#xlabel('tid')
#ylabel('PPM CO2')

#Her kan du plotte Luftfuktighet

#plt.plot(TIME, luftfuktighet, label = "Luftfuktighet")
#plt.plot(TIME, x, label = "snitt luftfuktighet")
#plt.plot(TIME,w, label = "Laveste grenseverdi")
#title('Relativ luftfuktighet')
#xlabel('tid')
#ylabel('Relativ luftfuktighet i prosent')


    

#Plotter grafen med bare 8 verdier langs x-aksen og med rutete bakgrunn
loc = matplotlib.ticker.LinearLocator(numticks = 8)
plt.gca().xaxis.set_major_locator(loc)
grid()
plt.legend()
plt.show()











