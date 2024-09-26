#!/usr/bin/env pypy3
from lib import *

startPos = (0, 0)
knots = []
ropePositions = set()


def moveDirection(direction: str, pos: tuple, inverse=1):
    match direction:
        case "U":
            pos = (pos[0], pos[1] + 1 * inverse)
        case "D":
            pos = (pos[0], pos[1] - 1 * inverse)
        case "L":
            pos = (pos[0] - 1 * inverse, pos[1])
        case "R":
            pos = (pos[0] + 1 * inverse, pos[1])
    return pos


def generateNeighbors(tup: tuple):
    arr = []
    for x in range(tup[0] - 1, tup[0] + 2):
        for y in range(tup[1] - 1, tup[1] + 2):
            arr.append((x, y))
    return arr


def checkTail(head: tuple, tail: tuple):
    neighbors = generateNeighbors(tail)
    for neighbor in neighbors:
        if (neighbor == head):
            return True
    return False


lines = readFileLines()
ropePositions.add(startPos)
previousDirection = []
previousPreviousDirection = []
for i in range(10):
    knots.append(startPos)
    previousDirection.append("")
    previousPreviousDirection.append("")
for l in lines:
    print(l)
    direction, amount = l.split()
    amount = int(amount)
    for i in range(amount):
        knots[0] = moveDirection(direction, knots[0])
        for j, knot in enumerate(knots):
            if (j + 1 != len(knots) and not checkTail(knot, knots[j+1])):
                knots[j+1] = moveDirection(previousDirection[j], knots[j+1])
                if (previousPreviousDirection[j] != "" and moveDirection(previousDirection[j], knot, -1) != knots[j+1]):
                    knots[j +
                          1] = moveDirection(previousPreviousDirection[j], knots[j+1])
                if (j + 1 == len(knots) - 1):
                    ropePositions.add(knots[j+1])
                previousPreviousDirection[j +
                                          1] = previousPreviousDirection[j]
                previousDirection[j + 1] = previousDirection[j]
        print(knots)
        # print(ropePositions)
        previousPreviousDirection[0] = previousDirection[0]
        previousDirection[0] = direction
print(len(ropePositions))

# 10487 HIGH
