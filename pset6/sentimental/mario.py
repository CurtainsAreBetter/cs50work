from cs50 import get_int
n = get_int("Height: ")
while n not in range(1, 9):
    n = int(input("Height: "))
# Prints out the pyramid
for i in range(1, n+1):
    print(" "*(n-i) + "#"*i + "  " + "#"*i)
