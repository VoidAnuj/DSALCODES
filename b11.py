class Node:
    def __init__(self, keyword, meaning):
        self.keyword = keyword
        self.meaning = meaning
        self.left = None
        self.right = None

class DictionaryBST:
    def __init__(self):
        self.root = None

    def insert(self, keyword, meaning):
        if not self.root:
            self.root = Node(keyword, meaning)
        else:
            self._insert_recursive(self.root, keyword, meaning)

    def _insert_recursive(self, node, keyword, meaning):
        if keyword < node.keyword:
            if node.left is None:
                node.left = Node(keyword, meaning)
            else:
                self._insert_recursive(node.left, keyword, meaning)
        elif keyword > node.keyword:
            if node.right is None:
                node.right = Node(keyword, meaning)
            else:
                self._insert_recursive(node.right, keyword, meaning)
        else:
            node.meaning = meaning  # Update if keyword already exists

    def delete(self, keyword):
        self.root = self._delete_recursive(self.root, keyword)

    def _delete_recursive(self, node, keyword):
        if node is None:
            return node
        if keyword < node.keyword:
            node.left = self._delete_recursive(node.left, keyword)
        elif keyword > node.keyword:
            node.right = self._delete_recursive(node.right, keyword)
        else:
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left
            min_node = self._find_min(node.right)
            node.keyword = min_node.keyword
            node.meaning = min_node.meaning
            node.right = self._delete_recursive(node.right, min_node.keyword)
        return node

    def _find_min(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current

    def update(self, keyword, new_meaning):
        node = self._find(self.root, keyword)
        if node:
            node.meaning = new_meaning
        else:
            print("Keyword not found!")

    def _find(self, node, keyword):
        if node is None:
            return None
        if keyword < node.keyword:
            return self._find(node.left, keyword)
        elif keyword > node.keyword:
            return self._find(node.right, keyword)
        else:
            return node

    def display_ascending(self):
        self._in_order_traversal(self.root)

    def _in_order_traversal(self, node):
        if node:
            self._in_order_traversal(node.left)
            print(f"{node.keyword}: {node.meaning}")
            self._in_order_traversal(node.right)

    def display_descending(self):
        self._reverse_in_order_traversal(self.root)

    def _reverse_in_order_traversal(self, node):
        if node:
            self._reverse_in_order_traversal(node.right)
            print(f"{node.keyword}: {node.meaning}")
            self._reverse_in_order_traversal(node.left)

    def height(self):
        return self._height_recursive(self.root)

    def _height_recursive(self, node):
        if node is None:
            return 0
        left_height = self._height_recursive(node.left)
        right_height = self._height_recursive(node.right)
        return max(left_height, right_height) + 1

# Main Menu
if __name__ == "__main__":
    dictionary = DictionaryBST()

    while True:
        print("\nDictionary Operations:")
        print("1. Add Keyword")
        print("2. Delete Keyword")
        print("3. Update Keyword")
        print("4. Display Sorted Dictionary (Ascending)")
        print("5. Display Sorted Dictionary (Descending)")
        print("6. Find Maximum Comparisons (Height of Tree)")
        print("7. Exit")

        try:
            choice = int(input("Enter your choice: "))
        except ValueError:
            print("Please enter a valid number.")
            continue

        if choice == 1:
            keyword = input("Enter keyword to add: ")
            meaning = input("Enter meaning of the keyword: ")
            dictionary.insert(keyword, meaning)
            print("Keyword added successfully.")
        elif choice == 2:
            keyword = input("Enter keyword to delete: ")
            dictionary.delete(keyword)
            print(f"Keyword '{keyword}' deleted successfully.")
        elif choice == 3:
            keyword = input("Enter keyword to update: ")
            new_meaning = input("Enter new meaning: ")
            dictionary.update(keyword, new_meaning)
            print(f"Keyword '{keyword}' updated successfully.")
        elif choice == 4:
            print("\nDictionary (Ascending Order):")
            dictionary.display_ascending()
        elif choice == 5:
            print("\nDictionary (Descending Order):")
            dictionary.display_descending()
        elif choice == 6:
            print("\nMaximum Comparisons (Height of Tree):", dictionary.height())
        elif choice == 7:
            print("Exiting program...")
            break
        else:
            print("Invalid choice, please try again.")
