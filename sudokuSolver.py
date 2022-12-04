def possible(y, x, n):
    for i in range(0,9):
        if sudokugrid[y][i] == n:
            return False
        if sudokugrid[i][x] == n:
            return False
    x0 = (x//3)*3
    y0 = (y//3)*3
    for i in range(0,3):
        for j in range(0,3):
            if sudokugrid[y0+i][x0+j] == n:
                return False
    return True

def solve():
    for y in range(9):
        for x in range(9):
            if sudokugrid[y][x] == 0:
                for n in range(1,10):
                    if possible(y, x, n):
                        sudokugrid[y][x] = n
                        solve()
                        sudokugrid[y][x] = 0
                return
    printBoard()
    input("More?")

def printBoard():
    for i in range(9):
        print(sudokugrid[i])

sudokugrid = []
file = open("test.txt", "r")
for line in file:
    sudokugrid.append([int(x) for x in line.split()])
solve()