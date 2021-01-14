class Node:
  def __init__(self, data, priority):
    self.data = data
    self.priotity = priority
    self.next = None 

class PriorityLinkedQueue:
  def __init__(self):
    self.front = None

  def isEmpty(self):
    if (self.front == None): return True
    else: return False

  def push(self, data, priority):
    new_node = Node(data, priority)

    if (self.isEmpty() == True):
      self.front = new_node
    else:

      if (self.front.priotity < priority):
        new_node.next = self.front
        self.front = new_node
      else:
        ref = self.front
        while(ref != None):
          if (ref.priotity >= priority and ref.next == None):
            break
          ref = ref.next
        new_node.next = ref.next
        ref.next = new_node

  def pop(self):
    if (self.isEmpty() == True): return
    else:
      ref = self.front
      self.front = self.front.next
      ref = None
      return

  def printPLQ(self):
    if (self.isEmpty() == True):
      print("Queue is empty")
    else:
      ref = self.front
      while(ref != None):
        print(ref.data, ref.priotity)
        ref = ref.next
      
if __name__ == '__main__':
  q1 = PriorityLinkedQueue()

  q1.push(2, 1)
  q1.push(4, 1)
  q1.push(8, 1)
  q1.push(16, 1)
  q1.push(0, 2)

  print("Priority Linked Queue:")
  q1.printPLQ()
