n = int(input("enter number of elements to be added in set :"))
S1 = set()
for i in range(n):
    e = int(input("enter the elements :"))
    S1.add(e)
print(S1)

n = int(input("enter number of elements to be added in set :"))
S2 = set()
for i in range(n):
    e = int(input("enter the elements :"))
    S2.add(e)
print(S2)


def mainmenu():
    print("menu :")
    print("1.insertion of element in a set ")
    print("2. remove the element from a set")
    print("3.display the element of the set")
    print("4.size of a set")
    print("5.intersection of sets")
    print("6.union of sets")
    print("7.difference of the sets")
    print("8.subset")

    ch = int(input("enter your choice"))

    if ch == 1:
        a = input("enter in which set you want to insert the element :")
        if a == S1:
            S1.add("enter the element")
        else:
            S2.add("enter the element")
    mainmenu()

    elif ch == 2:
    a = input("enter in which set you want to insert the element :")
    if a == S1:
        S1.remove("enter the element")
    else:
        S2.remove("enter the element")


mainmenu()

elif ch == 3:
print("S1 =", S1)
print("S2 =", S2)
mainmenu()

elif ch == 4:
print(len(S1))
print(len(S2))
mainmenu()

elif ch == 5:
print("intersection is :", S1 & S2)
mainmenu()

elif ch == 6:
print("union is :", S1 | S2)
mainmenu()

elif ch == 7:
print("difference is :", S1 - S2)
mainmenu()

elif ch == 8:
print("subset", S1.issubset(S2))
mainmenu()
