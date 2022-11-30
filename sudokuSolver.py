# Get the index from the row, column, and digit
def indexFromChoice(row, column, digit):
    return 81 * row + 9 * column * digit


# Get the row, column, and digit from the index
def choiceFromIndex(i):
    return i // 81, (i // 9) % 9, i % 9


def cellConstraint(row, column):
    return [indexFromChoice(row, column, digit) for digit in range(9)]


def rowConstraint(row, digit):
    return [indexFromChoice(row, column, digit) for column in range(9)]


def columnConstraint(column, digit):
    return [indexFromChoice(row, column, digit) for row in range(9)]


def generateConstraints():
    constraints = []
    for row in range(9):
        for column in range(9):
            constraints.append(cellConstraint(row, column))
    for row in range(9):
        for digit in range(9):
            constraints.append(rowConstraint(row, digit))
    for column in range(9):
        for digit in range(9):
            constraints.append(columnConstraint(column, digit))
    return constraints


def solve():
    permutations = 9 * 9 * 9
    constraints = generateConstraints()
    relation = [len(constraints) * [0] for i in range(permutations)]
    for i, constraint in enumerate(constraints):
        for c in constraint:
            relation[c][i] = 1


if __name__ == '__main__':
    solve()


def sudokuGenerator():
    # Create a list of 81 numbers from 1 to 9
    numbers = list(range(1, 10))
    # Create a list of 81 empty spaces
    spaces = list(range(81))
    # Shuffle the numbers
    random.shuffle(numbers)
    # Shuffle the spaces
    random.shuffle(spaces)
    # Create a list of 81 empty spaces
    sudoku = list(range(81))
    # Fill the spaces with the numbers
    for i in range(81):
        sudoku[spaces[i]] = numbers[i]
    # Return the sudoku
    return sudoku
