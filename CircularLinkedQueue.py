class Node:
  def __init__(self, data):
    self.data = data 
    self.next = None

class CircularLinkedQueue:
  def __init__(self):
    self.front = None 
    self.rear = None

  def lenghtCLQ(self):
    ref = self.front
    lenght = 0
    while(ref != self.rear):
      lenght += 1
      ref = ref.next
    lenght += 1
    return lenght

  def append(self, data):
    new_node = Node(data)
    
    if (self.front == None):
      self.front = new_node
    else:
      self.rear.next = new_node
    
    self.rear = new_node
    self.rear.next = self.front

  def remove(self):
    ref = None
    if (self.front == None):
      print("Queue is empty")
      return
    
    if (self.front == self.rear):
      self.front = None
      self.rear = None
    else:
      ref = self.front
      self.front = self.front.next
      self.rear.next = self.front
  
  def printCLQ(self):
    ref = self.front 
    while(ref != self.rear):
      print(ref.data)
      ref = ref.next
    print(self.rear.data)

if __name__ == '__main__':
  cq1 = CircularLinkedQueue()

  cq1.append(2)
  cq1.append(4)
  cq1.append(8)
  cq1.append(16)

  cq1.remove()

  print("Circular Linked Queue: ")
  cq1.printCLQ()
