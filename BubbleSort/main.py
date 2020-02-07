import timeit
from random import randint
import matplotlib.pyplot as plt

def geraLista(tam):
    lista = []
    while len(lista) < tam:
        n = randint(1,1*tam)
        if n not in lista: lista.append(n)
    return lista

def desenhaGrafico(x,BbleSort,xl = "Valores de Entradas", yl = "Repetições",bble="img"):
    fig = plt.figure(figsize=(20, 23))
    ax = fig.add_subplot(111)
    ax.plot(x,BbleSort, label = "Bubble Sort")
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    plt.savefig(bble)

def bubbleSort(arr):
    count = 0
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            count+=1
            if arr[j] > arr[j+1] :
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return count

l1 = 1000
l2 = 10000
l3 = 30000
l4 = 60000
lista = [l1,l2,l3,l4]
saidaB = []
saidaL = []


for i in range(len(lista)):
  saidaB.append(timeit.timeit("bubbleSort({})".format(geraLista(lista[i])),setup="from __main__ import geraLista,bubbleSort",number=1))

desenhaGrafico(lista,saidaB,bble="tempo")

for i in range(len(lista)):

  saidaL.append(bubbleSort(geraLista(lista[i])))

desenhaGrafico(lista,saidaL,bble="cont")
