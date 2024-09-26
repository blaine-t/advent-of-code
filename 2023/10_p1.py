#!/usr/bin/env pypy
from lib import *

setDebug()
# setTest()

startLoc = ()
sum = 0


def connects(direction: int, char: str):
    if (direction == 0):
        if (char == "-" or char == "L" or char == "F"):
            return True
    elif (direction == 1):
        if (char == "|" or char == "7" or char == "F"):
            return True
    elif (direction == 2):
        if (char == "|" or char == "L" or char == "J"):
            return True
    elif (direction == 3):
        if (char == "-" or char == "J" or char == "7"):
            return True
    return False


def tupNearby(tup: tuple, depth=1) -> list[tuple]:
    arr = []
    for x in range(tup[0] - depth, tup[0] + depth + 1):
        for y in range(tup[1] - depth, tup[1] + depth + 1):
            if (not (x != tup[0] and y != tup[1]) and not (x == tup[0] and y == tup[1])):
                arr.append((x, y))
    return arr


playMap = []


lines = readFileLines()
for l in lines:
    inner = []
    for c in l:
        inner.append(c)
    playMap.append(inner)

print(playMap)


for row, l in enumerate(lines):
    for col, c in enumerate(l):
        if (c == "S"):
            startLoc = (row, col)
            for direction, pipe in enumerate(tupNearby(startLoc)):
                if (connects(direction, playMap[pipe[1]][pipe[0]])):
                    print(pipe)
