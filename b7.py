class Node:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

class ExpressionTree:
    def __init__(self, prefix_expression):
        self.root = self.construct_tree(prefix_expression)

    def construct_tree(self, prefix_expression):
        stack = []
        for char in reversed(prefix_expression):
            if char.isalnum():
                stack.append(Node(char))
            else:
                node = Node(char)
                node.left = stack.pop()
                node.right = stack.pop()
                stack.append(node)
        return stack[-1] if stack else None

    def postorder_traversal(self):
        if not self.root:
            print("Tree is empty.")
            return

        stack1 = [self.root]
        stack2 = []

        while stack1:
            node = stack1.pop()
            stack2.append(node)
            if node.left:
                stack1.append(node.left)
            if node.right:
                stack1.append(node.right)

        while stack2:
            node = stack2.pop()
            print(node.value, end=" ")

    def delete_tree(self):
        self.root = None
        print("Tree has been deleted.")

if __name__ == "__main__":
    prefix_expr = input("Enter the prefix expression: ")
    tree = ExpressionTree(prefix_expr)
    print("\nPostorder Traversal (Non-Recursive):")
    tree.postorder_traversal()
    print()
    tree.delete_tree()
