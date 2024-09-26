#!/usr/bin/env pypy3
from lib import *

# setDebug()
# setTest()

startPos = (0, 0)
headPos = startPos
tailPos = startPos
ropePositions = set()


def checkTail():
    global headPos
    global tailPos
    neighbors = tupNearby(tailPos)
    for neighbor in neighbors:
        if (neighbor == headPos):
            return True
    return False


lines = readFileLines()
ropePositions.add(tailPos)
for l in lines:
    direction, amount = l.split()
    amount = int(amount)
    for i in range(amount):
        headPos = moveTupDir(direction, headPos)
        if (not checkTail()):
            tailPos = headPos
            tailPos = moveTupDir(direction, tailPos, -1)
            ropePositions.add(tailPos)

print(len(ropePositions))
