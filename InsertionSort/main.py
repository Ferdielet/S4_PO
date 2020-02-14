import timeit
from random import randint
import matplotlib.pyplot as plt


def geraLista(tam):
    lista = []
    for i in range(tam):
        n = randint(1, 1 * tam)
        if n not in lista: lista.append(n)
    return lista


def geraListaInvertida(tam):
    lista = []
    while tam:
        lista.append(tam)
        tam -= 1
    return lista


def desenhaGrafico(x, lista1, lista2, xl="Variáveis de Entradas", yl="Y", name="out", label1="Lista Estocástica",
                   label2="Lista Invertida"):
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111)
    ax.plot(x, lista1, label=label1)
    ax.plot(x, lista2, label=label2)
    ax.legend(bbox_to_anchor=(1, 1), bbox_transform=plt.gcf().transFigure)
    plt.ylabel(yl)
    plt.xlabel(xl)
    plt.savefig(name)


graf_operacoes = []


def sort(lista):
    count = 0
    for x in range(0, len(lista)):
        key = lista[x]
        y = x - 1
        while key < lista[y] and y >= 0:
            lista[y + 1] = lista[y]
            y -= 1
            count += 1
        lista[y + 1] = key
        count += 1
    graf_operacoes.append(count)


l1 = 1000
l2 = 10000
l3 = 30000
l4 = 60000
quant = [l1, l2, l3, l4]
graf_tempoRandomica = []
graf_tempoInvertida = []
print("Lista Estocástica")
for i in range(len(quant)):
    print(quant[i])
    listaRandomica = geraLista(quant[i])
    graf_tempoRandomica.append(
        timeit.timeit("sort({})".format(listaRandomica), setup="from __main__ import sort", number=1))
graf_operacoesRandomica = graf_operacoes
graf_operacoes = []

print("Lista Invertida")
for i in range(len(quant)):
    print(quant[i])
    listaInvertida = geraListaInvertida(quant[i])
    graf_tempoInvertida.append(
        timeit.timeit("sort({})".format(listaInvertida), setup="from __main__ import sort", number=1))

graf_operacoesInvertida = graf_operacoes
graf_operacoes = []

desenhaGrafico(quant, graf_tempoRandomica, graf_tempoInvertida, "Tamanho", "Tempo", "Tempo")
desenhaGrafico(quant, graf_operacoesRandomica, graf_operacoesInvertida, "Tamanho", "Operacoes", "Operacoes")
