class Node:
  def __init__(self, data):
    self.data = data
    self.next = None

class LinkedQueue:
  def __init__(self):
    self.front = None
    self.rear = None

  def isEmpty(self):
    if (self.front == None): return True
    else: return False

  def lenghtLQ(self):
    ref = self.front
    lenght = 0
    while(ref != None):
      lenght += 1
      ref = ref.next
    return lenght

  def append(self, data):
    new_node = Node(data)
    if (self.rear == None):
      self.front = new_node
      self.rear = new_node
    else:
      self.rear.next = new_node
      self.rear = new_node

  def remove(self):
    if (self.isEmpty()): return
    ref = self.front
    self.front = ref.next

    if (self.front == None): self.rear = None

  def printLQ(self):
    ref = self.front
    while(ref != None):
      print(ref.data)
      ref = ref.next

if __name__ == '__main__':
  q1 = LinkedQueue()

  q1.append(5)
  q1.append(10)
  q1.append(15)

  q1.remove()

  print("Linked Queue: ")
  q1.printLQ()
