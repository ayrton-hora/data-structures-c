class StackNode:
  def __init__(self, data):
    self.data = data
    self.next = None

class LinkedStack:
  def __init__(self):
    self.root = None

  def lengthLS(self):
    ref = self.root
    lenght = 0
    while(ref):
      lenght += 1
      ref = ref.next
    return lenght
  
  def isEmpty(self):
    if self.root is None: return True
    else: return False

  def push(self, data):
    new_node = StackNode(data)
    new_node.next = self.root
    self.root = new_node

  def pop(self):
    if (self.isEmpty()): return

    ref = self.root
    self.root = self.root.next
    ref = None

  def peek(self):
    if self.isEmpty(): return
    return self.root.data

  def printStack(self):
    ref = self.root
    while(ref):
      print(ref.data)
      ref = ref.next
  
if __name__ == '__main__':
    s1 = LinkedStack()

    s1.push(3)
    s1.push(9)
    s1.push(27)

    s1.pop()

    s1.peek()

    print("Linked Stack: ")
    s1.printStack()
