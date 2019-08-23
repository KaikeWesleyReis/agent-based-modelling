# -*- coding: cp1252 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
#Gerando as variaveis de dados:
fw,fr = np.loadtxt('winnertypesimulations.txt',delimiter=',',unpack=True)
cf,ca = np.loadtxt('winnerpersimulations.txt',delimiter=',',unpack=True)
rogues = np.loadtxt('sr.txt')
warriors = np.loadtxt('sw.txt')
''' FORCA VS AGILIDADE
plt.plot(ca,cf,'ro')
plt.title('Strength versus Agility [Base 10]')
plt.ylabel('Strength')
plt.xlabel('Agility')
plt.show()
'''
'''DECAIMENTO DE LUTADORES
x = range(len(warriors))
plt.plot(x,warriors,'red',x,rogues,'blue')
plt.title('Decaimento da quantidade de guerreiros por classe')
plt.ylabel('Quantidade de guerreiros')
plt.xlabel('Rodadas x100')
red_patch = mpatches.Patch(color='red',label='warrior')
blue_patch = mpatches.Patch(color='blue',label='rogue')
plt.legend(handles=[red_patch,blue_patch])
plt.show()
'''
''' FREQUENCIAS
y_axis = [fw,fr]
x_axis = range(len(y_axis))
width_n = 1
plt.bar(x_axis, y_axis, width=width_n, color=['green','red'])
plt.title('Frequencia dos 3 finalistas')
plt.ylabel('Quantidade de campeoes')
plt.xlabel(['Warriors', 'Rogue'])
plt.show()
'''

