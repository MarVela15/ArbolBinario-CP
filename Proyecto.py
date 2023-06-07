class Node:
    def __init__(self, element, left=None, right=None):
        self.element = element
        self.left = left
        self.right = right

def tree_add(node, element):
    if node is None:
       # print("Here")
        node = Node(element)
        return node

    if node.element > element:
        if node.left is None:
            node.left = Node(element)
        else:
            node.left = tree_add(node.left, element)
    elif node.element < element:
        if node.right is None:
            node.right = Node(element)
        else:
            node.right = tree_add(node.right, element)

    return node

root = tree_add(None, 509)
#print(type(root))
tree_add(root, 320)
tree_add(root, 654)
tree_add(root,132)
tree_add(root,708)
#print(root.element)
#print(root.left.element)
#print(root.right.element)

def tree_print(level, root):
    if root is not None:
        
        tree_print(level+1,root.right)

        print ("   "* level + str(root.element))

        tree_print(level+1,root.left)
        
tree_print(0, root)

def tree_remove(node, element):
    if node is None:
        print("Here")
        return node

   # if node.element == element
        


    return node