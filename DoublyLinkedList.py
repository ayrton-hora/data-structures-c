class Node:
  def __init__(self, data):
    self.data = data
    self.next = None
    self.prev = None

class DoublyLinkedList:
  def __init__(self):
    self.head = None
  
  def isEmpty(self):
    if (self.head == None): return True
    else: return False

  def lenghtDLL(self):
    ref = self.head
    length = 0
    while(ref != None):
      length += 1
      ref = ref.next
    return length

  def push(self, data):
    new_node = Node(data)
    new_node.next = self.head

    if (self.head != None):
      self.head.prev = new_node
    self.head = new_node

  def append(self, data):
    new_node = Node(data)
    new_node.next = None

    if (self.head == None):
      new_node.prev = None
      self.head = new_node
      return
      
    ref = self.head
    while (ref.next != None):
      ref = ref.next 
      
    ref.next = new_node
    new_node.prev = ref

  def insertAfter(self, prev, data):
    if (prev == None):
      print("The previous node must be not empty")
      return
    
    new_node = Node(data)
    new_node.next = prev.next 
    prev.next = new_node
    new_node.prev = prev

    if (new_node != None):
      new_node.next.prev = new_node

  def delete(self, rem_node):
    ref = self.head

    if (ref == None) or (rem_node == None): return

    if (ref.data == rem_node):
      self.head = rem_node.next

    if (rem_node.next != None):
      rem_node.prev.next = rem_node.next
    
    rem_node = None

  def printDLL(self):
    ref = self.head
    while(ref != None):
      print(ref.data)
      ref = ref.next

if __name__ == '__main__':
  dl1 = DoublyLinkedList()

  dl1.append(1)
  dl1.append(2)
  dl1.append(3)

  dl1.push(0)

  print("Doubly Linked List: ")
  dl1.printDLL()