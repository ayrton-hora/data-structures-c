class Node:
  def __init__(self, data):
    self.data = data
    self.next = None

class LinkedList:
  def __init__(self):
    self.head = None

  def lenghtLL(self):
    ref = self.head 
    length = 0
    while (ref):
      length += 1
      ref = ref.next
    return length

  def searchIterative(self, data):
    ref = self.head
    while(ref != None):
      if (ref.data == data):
        return True
      ref = ref.next
    return False

  def searchRecursive(self, data):
    ref = self.head 
    if (ref == None): return False

    if (ref.data == data): return True

    return self.searchRecursive(data)
    
  def push(self, new_data):
    new_node = Node(new_data)
    new_node.next = self.head
    self.head = new_node

  def insertAfter(self, prevN, data):
    if prevN == None:
      print("The previous node must be not empty")
      return

    new_node = Node(data)
    new_node.next = prevN.next
    prevN.next = new_node

  def append(self, new_data):
    new_node = Node(new_data)
    if self.head is None:
      self.head = new_node
      return
    
    ref = self.head
    while (ref.next != None):
      ref = ref.next
    
    ref.next = new_node

  def deleteNode(self, data):
    ref = self.head

    if (ref != None):
      if (ref.data == data):
        self.head = ref.next
        ref = None
        return
    
    while (ref != None):
      if (ref.data == data):
        break
      prev = ref 
      ref = ref.next

    if (ref == None):
      return

    prev.next = ref.next
    ref = None

  def deleteNodePos(self, pos):
    ref = self.head
    if (ref == None): return 

    if (pos == 0):
      self.head = ref.next
      ref = None
      return

    for i in range(pos - 1):
      ref = ref.next
      if (ref == None): break

      if (ref == None): return

      if (ref.next == None): return

      next_Node = ref.next.next
      ref.next = None

  def printList(self):
    ref = self.head
    while (ref):
      print(ref.data)
      ref = ref.next

if __name__ == '__main__':

  l1 = LinkedList()
  l1.append(2)
  l1.append(4)
  l1.append(8)
  l1.append(16)

  l1.push(0)

  l1.deleteNode(16)

  print("Linked list: ")
  l1.printList()