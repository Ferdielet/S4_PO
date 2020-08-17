# coding=utf-8

"""
author = Fernando
PYTHON 3.3.5
"""

from __future__ import (nested_scopes, generators, division, absolute_import, with_statement,
                        print_function, unicode_literals)

class BTree(object):
  """Uma implementação BTree com funções de pesquisa e inserção. Capaz de qualquer ordem t."""

  class Node(object):
    """Um nó B-Tree simples."""

    def __init__(self, t):
      self.keys = []
      self.children = []
      self.leaf = True
      
      # t é a ordem da B-Tree pai. Os nós precisam desse valor para definir o tamanho máximo e a divisão.
      self._t = t

    def split(self, parent, payload):
      """Divida um nó e reatribua chaves / filhos."""
      new_node = self.__class__(self._t)

      mid_point = self.size//2
      split_value = self.keys[mid_point]
      parent.add_key(split_value)

      # Adicione chaves e filhos aos nós apropriados
      new_node.children = self.children[mid_point + 1:]
      self.children = self.children[:mid_point + 1]
      new_node.keys = self.keys[mid_point+1:]
      self.keys = self.keys[:mid_point]

      # Se o new_node tiver filhos, defina-o como um nó interno
      if len(new_node.children) > 0:
        new_node.leaf = False

      parent.children = parent.add_child(new_node)
      if payload < split_value:
        return self
      else:
        return new_node

    @property
    def _is_full(self):
      return self.size == 2 * self._t - 1

    @property
    def size(self):
      return len(self.keys)

    def add_key(self, value):
      """Adicione uma chave a um nó. O nó terá espaço para a chave por definição."""
      self.keys.append(value)
      self.keys.sort()

    def add_child(self, new_node):
      """
      Adicione um filho a um nó. Isso classificará os filhos do nó, permitindo que os filhos
       a ser ordenado mesmo após a divisão dos nós do meio.
       retorna: uma lista de ordem de nós filhos
      """
      i = len(self.children) - 1
      while i >= 0 and self.children[i].keys[0] > new_node.keys[0]:
        i -= 1
      return self.children[:i + 1]+ [new_node] + self.children[i + 1:]


  def __init__(self, t):
    """
    Crie a árvore B. t é a ordem da árvore. A árvore não tem chaves quando criada.
     Esta implementação permite valores-chave duplicados, embora isso não tenha sido verificado
     vigorosamente.
    """
    self._t = t
    if self._t <= 1:
      raise ValueError("B-Tree must have a degree of 2 or more.")
    self.root = self.Node(t)

  def insert(self, payload):
    """Insira uma nova chave de carga útil de valor na B-Tree."""
    node = self.root
    
    # A raiz é tratada explicitamente, pois requer a criação de 2 novos nós em vez do usual.
    if node._is_full:
      new_root = self.Node(self._t)
      new_root.children.append(self.root)
      new_root.leaf = False
      
      # o nó está sendo definido como o nó que contém os intervalos que desejamos para a inserção de carga útil.
      node = node.split(new_root, payload)
      self.root = new_root
    while not node.leaf:
      i = node.size - 1
      while i > 0 and payload < node.keys[i] :
        i -= 1
      if payload > node.keys[i]:
        i += 1

      next = node.children[i]
      if next._is_full:
        node = next.split(node, payload)
      else:
        node = next
        
    # Como dividimos todos os nós completos no caminho para baixo, podemos simplesmente inserir a carga útil na folha.
    node.add_key(payload)

  def search(self, value, node=None):
    """Retorna True se a B-Tree contém uma chave que corresponde ao valor."""
    if node is None:
      node = self.root
    if value in node.keys:
      return True
    elif node.leaf:
      # Se estivermos em uma folha, não há mais o que verificar.
      return False
    else:
      i = 0
      while i < node.size and value > node.keys[i]:
        i += 1
      return self.search(value, node.children[i])

  def print_order(self):
    """Imprima uma representação de ordem de nível."""
    this_level = [self.root]
    while this_level:
      next_level = []
      output = ""
      for node in this_level:
        if node.children:
          next_level.extend(node.children)
        output += str(node.keys) + " "
      print(output)
      this_level = next_level
