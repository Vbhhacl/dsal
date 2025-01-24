n=int(input("Enter number of Elements in set A :"))
setA = set()
for i in range(n):
 e = int(input("Enter Number to Add :"))
 setA.add(e)
 print(setA)
 
s=int(input("Enter number of Elements in set B :"))
setB = set()
 for i in range(s):
 f = int(input("Enter Number to Add :"))
 setB.add(f)
 print(setB)
 
e = int(input("Enter Number to Add :"))
setA.add(e)
print(setA) 
 
e = int(input("Enter Number to Remove :"))
setA.remove(e)
print(setA)


e = int(input("Enter Number to Search :"))								
if e in setA:
 print("Element in Set :")
else:
 print("Element not in Set :")

f = int(input("Enter Number to Search :"))
if f in setB:
 print("Element in Set")
else:
 print("Element not in Set")   
 
print(len(setA))

setC = setA.union(setB)
print(setC)

setC = setA.intersection(setB)
print(setC)

setC = setA.difference(setB)
print(setC)

print(setA.issubset(setB))
