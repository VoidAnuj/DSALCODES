# Code by Anuj Gholve

class Set:
    def __init__(self):
        self.elements = []

    def add(self, new_element):
        if new_element not in self.elements:
            self.elements.append(new_element)

    def remove(self, element):
        if element in self.elements:
            self.elements.remove(element)

    def contains(self, element):
        return element in self.elements

    def size(self):
        return len(self.elements)

    def intersection(self, other):
        result = Set()
        for elem in self.elements:
            if elem in other.elements:
                result.add(elem)
        return result

    def union(self, other):
        result = Set()
        result.elements = self.elements.copy()
        for elem in other.elements:
            if elem not in result.elements:
                result.add(elem)
        return result

    def difference(self, other):
        result = Set()
        for elem in self.elements:
            if elem not in other.elements:
                result.add(elem)
        return result

    def subset(self, other):
        for elem in self.elements:
            if elem not in other.elements:
                return False
        return True

    def display(self):
        print(" ".join(map(str, self.elements)))


def set_operations_menu(set1, set2):
    while True:
        print("\nSelect an operation to perform:")
        print("1. Add element to Set 1")
        print("2. Add element to Set 2")
        print("3. Remove element from Set 1")
        print("4. Remove element from Set 2")
        print("5. Display Set 1")
        print("6. Display Set 2")
        print("7. Union of Set 1 and Set 2")
        print("8. Intersection of Set 1 and Set 2")
        print("9. Difference of Set 1 and Set 2")
        print("10. Check if Set 1 is a subset of Set 2")
        print("11. Exit")
        
        choice = int(input("Enter your choice: "))

        if choice == 1:
            element = int(input("Enter element to add to Set 1: "))
            set1.add(element)
        elif choice == 2:
            element = int(input("Enter element to add to Set 2: "))
            set2.add(element)
        elif choice == 3:
            element = int(input("Enter element to remove from Set 1: "))
            set1.remove(element)
        elif choice == 4:
            element = int(input("Enter element to remove from Set 2: "))
            set2.remove(element)
        elif choice == 5:
            print("Set 1: ", end="")
            set1.display()
        elif choice == 6:
            print("Set 2: ", end="")
            set2.display()
        elif choice == 7:
            union_set = set1.union(set2)
            print("Union of Set 1 and Set 2: ", end="")
            union_set.display()
        elif choice == 8:
            intersection_set = set1.intersection(set2)
            print("Intersection of Set 1 and Set 2: ", end="")
            intersection_set.display()
        elif choice == 9:
            diff_set = set1.difference(set2)
            print("Difference (Set 1 - Set 2): ", end="")
            diff_set.display()
        elif choice == 10:
            if set1.subset(set2):
                print("Set 1 is a subset of Set 2.")
            else:
                print("Set 1 is not a subset of Set 2.")
        elif choice == 11:
            print("Exiting program...")
            break
        else:
            print("Invalid choice, please try again.")


if __name__ == "__main__":
    set1 = Set()
    set2 = Set()
    set_operations_menu(set1, set2)
