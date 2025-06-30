"""
THIS CODE HAS BEEN TESTED AND IS FULLY OPERATIONAL.

Problem Statement: To create ADT that implement the "set" concept.
a. Add (newElement) -> Place a value into the set
b. Remove (element) -> Remove the value
c. Contains (element) -> Return true if element is in collection
d. Size () -> Return number of values in collection
Iterator () -> Return an iterator used to loop over collection
e. Intersection of two sets
f. Union of two sets
g. Difference between two sets
h. Subset 

Code from DataStructuresAndAlgorithms (SPPU - Second Year - Computer Engineering - Content) repository on KSKA Git: https://git.kska.io/sppu-se-comp-content/DataStructuresAndAlgorithms/
"""

# BEGINNING OF CODE
SetA = [] 
SetB = []

def insert():
	n1 = int(input("Number of elements in SET A:\t"))
	for i in range(n1):
		nm = int(input(f"Element {i+1} in SET A:\t"))
		SetA.append(nm)
		
	n1 = int(input("Number of elements in SET B:\t"))
	for i in range(n1):
		nm = int(input(f"Element {i+1} in SET B:\t"))
		SetB.append(nm)
		
def display():
	print("SET A:\t",SetA)
	print("SET B:\t",SetB)
	
	
def union():
	res=[]
	for i in SetA:
		res.append(i)
	for i in SetB:
		if i not in res:
			res.append(i)
	
	print("Union:\t",res)

def intersection():
	res =[]
	for i in SetA:
		if i in SetB:
			res.append(i)
			
	print("Intersection:\t",res)

def difference():
	res =[]
										
	for i in SetA:
		if i not in SetB:
			res.append(i)
			
	for i in SetB:
		if i not in SetA:
			res.append(i)
	print("Difference:\t",res)
	
	
def find():
	t = int(input("1. SET A\n2. SET B\nChoose an option (1/2):\t"))
	s=False
	s = int(input("Element to search:\t"))
	if t==1:
		for i in range(len(SetA)):
			if s == SetA[i]:
				s = True
		if s == True:
			print("Element exists.")
		else:
			print("Element does not exist.")
	elif t==2:
		for i in range(len(SetB)):
			if s == SetB[i]:
				s = True
		if s == True:
			print("Element exists.")
		else:
			print("Element does not exist.")

def remove():
	t = int(input("1. SET A\n2. SET B\nChoose an option (1/2):\t"))
	s=False
	s1 = int(input("Element to be deleted:\t"))
	if t==1:
		for i in range(len(SetA)):
			if s1 == SetA[i]:
				s = True
		if s == True:
			print("Element exists.")
			SetA.remove(s1)
			print("After deletion:\t",SetA)
		else:
			print("Element does not exist in SET A.")
	elif t==2:
		for i in range(len(SetB)):
			if s1 == SetB[i]:
				s = True
		if s == True:
			print("Element exists.")
			SetB.remove(s1)
			print("After deletion:\t",SetB)
		else:
			print("Element does not exist in SET B.")
		
def size():
	ct=0
	for i in SetA:
		ct+=1  
	print("Size of SET A:\t",ct)
	ct=0
	for i in SetB:
		ct+=1
	print("Size of SET B:\t",ct)
							 
def subset():
	set5 = []
	flag=False
	for i in SetA:
		if i in SetB:
			set5.append(i)
			flag=True
		
	if flag==True:
		print("Subset",set5)
		print("SET B is a subset of SET A.")
	else:
		print("SET B is NOT Subset of SET A.")
	
while True:
	print("--- SET OPERATIONS ---")
	print("1 -> Insert")
	print("2 -> Display")
	print("3 -> Union ")
	print("4 -> Intersection")
	print("5 -> Difference")
	print("6 -> Size of Sets")
	print("7 -> Find")
	print("8 -> Delete an Element")
	print("9 -> Subset")
	print("0 -> Exit")
	
	ch = int(input("Choose an option (0-9):\t"))
	
	if ch==1:
		insert()
	elif ch==2:
		display()
	elif ch==3:
		union()
	elif ch==4:
		intersection()
	elif ch==5:
		difference()
	elif ch==6:
		size()
	elif ch==7:
		find()
	elif ch==8:
		remove()
	elif ch==9:
		subset()
	elif ch==0:
		print("\n## END OF CODE\n")
		break
	else:
		print("Please choose a valid option (0-9).")
# END OF CODE
