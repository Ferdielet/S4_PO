import random
import timeit
import matplotlib.pyplot as plt

def particao(lista, inicio, fim):
    pivo = lista[fim - 1]
    for i in range(inicio, fim):
        if not lista[i] > pivo:
            lista[inicio], lista[i] = lista[i], lista[inicio]
            inicio += 1
    return inicio-1

def quick_sort(lista, inicio, fim):
    if inicio < fim:
        pivo = escolhe_pivo_aleatorio(lista, inicio, fim)
        quick_sort(lista, inicio, pivo)
        quick_sort(lista, pivo + 1, fim)
    return lista

def escolhe_pivo_aleatorio(lista, inicio, fim):
    rand = random.randrange(inicio, fim)
    lista[fim - 1], lista[rand] = lista[rand], lista[fim - 1]
    return particao(lista, inicio, fim)

def desenha_grafico(x, y, file_name, label1, xl="Variáveis de Entradas", yl=" Respostas das Saídas"):
    fig = plt.figure(figsize=(12, 10))
    ax = fig.add_subplot(111)
    ax.plot(x, y, label=label1)
    ax.legend(bbox_to_anchor=(1, 1),bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    fig.savefig(file_name)

f1 = 100000
f2 = 200000
f3 = 300000
f4 = 400000
f5 = 500000

tam = [f1, f2, f3, f4, f5]
times = []

for i in range(len(tam)):
    lista_invertida = list(range(tam[i], 0, -1))
    times.append(timeit.timeit("quick_sort({}, {}, {})".format(lista_invertida, 0, len(lista_invertida)),
                               setup="from __main__ import quick_sort, escolhe_pivo_aleatorio, particao", number=1))

desenha_grafico(tam, times, "GraficoTempo.png", "Tempo despendido pelo algoritmo QuickSort", xl="Grandeza da lista", yl="Tempo Corrido")
