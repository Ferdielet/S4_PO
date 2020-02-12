import matplotlib as mpl
import matplotlib.pyplot as plt
from random import randint, shuffle
import timeit

def plot_grafico(x, y, z, file_name, label1, label2, xl = "Entradas", yl = "Saídas"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    ax.plot(x, y, label= label1)
    ax.plot(x, z, label= label2)
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)

    fig.savefig(file_name)

def geraLista(tam):
    lista = list(range(1, tam+1))
    shuffle(lista)
    return lista

def selection_sort(lista):
    count = 0
    flag = False
    for i in range(len(lista)):
        min = i
        for j in range(i + 1, len(lista)):
            count += 1
            if lista[min] > lista[j]:
                min = j

        aux = lista[i]
        lista[i] = lista[min]
        lista[min] = aux


    return count

x = [10000, 20000, 50000, 100000]
y = []
y_des = []
tempo_ord = []
count_ord = []
tempo_des = []
count_des = []

for i in range(len(x)):
    y.append(geraLista(x[i]))
    count_ord.append(selection_sort(y[i]))
    aux = list(range(1, x[i]))
    aux.reverse()
    y_des.append(aux)
    count_des.append(selection_sort(y_des[i]))

for i in range(len(x)):
    tempo_ord.append(timeit.timeit("selection_sort({})".format(y[i]), setup="from __main__ import selection_sort", number=1))
    tempo_des.append(timeit.timeit("selection_sort({})".format(y_des[i]), setup="from __main__ import selection_sort", number=1))

plot_grafico(x, tempo_ord, tempo_des, "Tempo.png", "Tempo Embaralhado", "Tempo Invertido")
plot_grafico(x, count_ord, count_des, "Interacoes.png", "Numero de Interacoes Embaralhado", "Numero de Interacoes Invertido")
