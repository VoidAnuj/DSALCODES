class HashTableChaining:
    def __init__(self, table_size=10):
        self.table_size = table_size
        self.table = [[] for _ in range(self.table_size)]

    def hash_function(self, key):
        hash_value = sum(ord(c) for c in key) % self.table_size
        return hash_value

    def insert(self, name, phone):
        index = self.hash_function(name)
        self.table[index].append((name, phone))

    def search(self, name):
        index = self.hash_function(name)
        comparisons = 0
        for entry in self.table[index]:
            comparisons += 1
            if entry[0] == name:
                return entry[1], comparisons
        return "Not found", comparisons


class HashTableLinearProbing:
    def __init__(self, table_size=10):
        self.table_size = table_size
        self.table = [("", "")] * self.table_size

    def hash_function(self, key):
        hash_value = sum(ord(c) for c in key) % self.table_size
        return hash_value

    def insert(self, name, phone):
        index = self.hash_function(name)
        original_index = index
        while self.table[index][0] != "" and self.table[index][0] != name:
            index = (index + 1) % self.table_size
            if index == original_index:
                print("Hash table is full!")
                return
        self.table[index] = (name, phone)

    def search(self, name):
        index = self.hash_function(name)
        original_index = index
        comparisons = 0
        while self.table[index][0] != "" and self.table[index][0] != name:
            comparisons += 1
            index = (index + 1) % self.table_size
            if index == original_index:
                return "Not found", comparisons
        comparisons += 1
        return self.table[index][1], comparisons


def interact_with_user():
    choice = 0
    hash_table_chaining = None
    hash_table_linear_probing = None

    while True:
        print("Choose collision resolution method: ")
        print("1. Chaining")
        print("2. Linear Probing")
        print("3. Exit")
        choice = int(input("Enter your choice: "))

        if choice == 1:
            hash_table_chaining = HashTableChaining()
        elif choice == 2:
            hash_table_linear_probing = HashTableLinearProbing()
        elif choice == 3:
            print("\nExiting...")
            return
        else:
            print("Invalid choice! Please try again.")
            continue

        insert_choice = 0
        while True:
            name = input("Enter client name: ")
            phone = input(f"Enter phone number for {name}: ")

            if choice == 1:
                hash_table_chaining.insert(name, phone)
            else:
                hash_table_linear_probing.insert(name, phone)

            insert_choice = int(input("Do you want to add another client? (1 for Yes, 0 for No): "))
            if insert_choice == 0:
                break

        search_name = input("Enter the name of the client you want to search: ")
        if choice == 1:
            result, comparisons = hash_table_chaining.search(search_name)
        else:
            result, comparisons = hash_table_linear_probing.search(search_name)

        if result != "Not found":
            print(f"Phone number for {search_name}: {result}")
        else:
            print(f"{search_name} not found!")

        print(f"Number of comparisons: {comparisons}")

        if choice == 1:
            del hash_table_chaining
        else:
            del hash_table_linear_probing


if __name__ == "__main__":
    interact_with_user()
