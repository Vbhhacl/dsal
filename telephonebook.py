class TelephoneBook:
    def __init__(self, name, tel_no):
        self.name = name
        self.tel_no = tel_no

# ------------------ INSERTION: QUADRATIC PROBING ------------------
def Insertion_QuadProbing():
    hashtable = [None for i in range(10)]
    num_records = int(input("\nEnter number of records: "))
    for _ in range(num_records):
        n = input("Enter name: ")
        t = int(input("Enter telephone no.: "))
        index = t % 10
        j = 1
        orig_index = index
        while hashtable[index] is not None:
            index = (orig_index + j * j) % 10
            j += 1
            if j >= 10:
                print("Hash table full! Could not insert:", n)
                break
        else:
            hashtable[index] = TelephoneBook(n, t)
    return hashtable

# ------------------ INSERTION: DOUBLE HASHING ------------------
def Insertion_DoubleHashing():
    hashtable = [None for i in range(10)]
    num_records = int(input("\nEnter number of records: "))
    for _ in range(num_records):
        n = input("Enter name: ")
        t = int(input("Enter telephone no.: "))
        h1 = t % 9
        h2 = 7 - (t % 7)
        index = (h1 + h2) % 10
        j = 1
        while hashtable[index] is not None:
            index = (h1 + j * h2) % 10
            j += 1
            if j >= 10:
                print("Hash table full! Could not insert:", n)
                break
        else:
            hashtable[index] = TelephoneBook(n, t)
    return hashtable

# ------------------ DISPLAY FUNCTION ------------------
def Display_Table(hash_table, method_name):
    print(f"\n----- Hash Table ({method_name}) -----")
    print("Index\tName\tTelephone No.")
    print("--------------------------------------")
    for i in range(len(hash_table)):
        obj = hash_table[i]
        if obj is None:
            print(f"{i}\t-\t-")
        else:
            print(f"{i}\t{obj.name}\t{obj.tel_no}")
    print("--------------------------------------")

# ------------------ SEARCH FUNCTION ------------------
def Search(hash1, hash2):
    n = input("Enter name to search: ")
    f1 = f2 = False

    print("\nSearching in Quadratic Probing Table...")
    for i in range(len(hash1)):
        obj = hash1[i]
        if obj is not None and obj.name == n:
            print("Found!")
            print(f"Index: {i}, Name: {obj.name}, Tel: {obj.tel_no}")
            f1 = True

    print("\nSearching in Double Hashing Table...")
    for i in range(len(hash2)):
        obj = hash2[i]
        if obj is not None and obj.name == n:
            print("Found!")
            print(f"Index: {i}, Name: {obj.name}, Tel: {obj.tel_no}")
            f2 = True

    if not f1 and not f2:
        print("\nNot found in either table.")

# ------------------ MAIN FUNCTION ------------------
def main():
    hash1 = [None for i in range(10)]
    hash2 = [None for i in range(10)]
    while True:
        print("\n========== Menu ==========")
        print("1. Insert Values")
        print("2. Display Tables")
        print("3. Search by Name")
        print("4. Exit")
        print("==========================")
        ch = int(input("Enter choice: "))
        if ch == 1:
            print("\nChoose Collision Handling Method:")
            print("1. Quadratic Probing")
            print("2. Double Hashing")
            c = int(input("Enter choice: "))
            if c == 1:
                hash1 = Insertion_QuadProbing()
            elif c == 2:
                hash2 = Insertion_DoubleHashing()
        elif ch == 2:
            print("\n1. Display Quadratic Probing Table")
            print("2. Display Double Hashing Table")
            c1 = int(input("Enter choice: "))
            if c1 == 1:
                Display_Table(hash1, "Quadratic Probing")
            elif c1 == 2:
                Display_Table(hash2, "Double Hashing")
        elif ch == 3:
            Search(hash1, hash2)
        elif ch == 4:
            print("Exiting program.")
            break
        else:
            print("Invalid choice. Try again.")

main()
