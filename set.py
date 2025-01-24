class SetOperations:
    def __init__(self):
        self.set_a = set()
        self.set_b = set()

    def insert(self):
        n = int(input("How many elements do you want to add in Set A?\n"))
        print("Enter elements for Set A:")
        self.set_a = set(int(input()) for _ in range(n))

        m = int(input("How many elements do you want to add in Set B?\n"))
        print("Enter elements for Set B:")
        self.set_b = set(int(input()) for _ in range(m))

    def add(self):
        choice = input("In which set do you want to add an element (A/B)?\n").strip().lower()
        element = int(input("Enter the element to add: "))

        if choice == 'a':
            self.set_a.add(element)
            print("Element added to Set A.")
        elif choice == 'b':
            self.set_b.add(element)
            print("Element added to Set B.")
        else:
            print("Invalid choice.")

    def delete(self):
        element = int(input("Enter the element to delete: "))
       
        if element in self.set_a:
            self.set_a.remove(element)
            print("Element removed from Set A.")
        if element in self.set_b:
            self.set_b.remove(element)
            print("Element removed from Set B.")
        if element not in self.set_a and element not in self.set_b:
            print("Element not found in either set.")

    def search(self):
        element = int(input("Enter the element to search: "))
       
        if element in self.set_a or element in self.set_b:
            print("The element is present in the set.")
        else:
            print("The element is not present in either set.")

    def display(self):
        print("Set A:", self.set_a)
        print("Set B:", self.set_b)

    def union(self):
        union_set = self.set_a | self.set_b
        print("Union of Set A and Set B:", union_set)

    def intersection(self):
        intersection_set = self.set_a & self.set_b
        if intersection_set:
            print("Intersection of Set A and Set B:", intersection_set)
        else:
            print("No common elements between Set A and Set B.")

    def difference(self):
        difference_set = self.set_a - self.set_b
        if difference_set:
            print("Difference (A - B):", difference_set)
        else:
            print("No difference between Set A and Set B.")


def main():
    s = SetOperations()
   
    while True:
        print("\n-----------------------------")
        print("Set Theory Operations")
        print("-----------------------------")
        print("1. Add Element")
        print("2. Delete Element")
        print("3. Search Element")
        print("4. Display Sets")
        print("5. Union")
        print("6. Intersection")
        print("7. Difference")
        print("8. Exit")

        choice = int(input("Enter your choice: "))

        if choice == 1:
            s.add()
        elif choice == 2:
            s.delete()
        elif choice == 3:
            s.search()
        elif choice == 4:
            s.display()
        elif choice == 5:
            s.union()
        elif choice == 6:
            s.intersection()
        elif choice == 7:
            s.difference()
        elif choice == 8:
            print("Exiting...")
            break
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    main()

