#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

result = 0
list1 = []
list2 = []
list3 = []
charList = ['X', 'M', 'A', 'S']
lines = readFileLines()
matrix = []*0
for line in lines:
    matrix.append(list(line))

# def helper(original, neighbors, lookingForIndex):
#     print(neighbors)
#     lookingFor = charList[lookingForIndex]
#     print(lookingFor)
#     for neighbor in neighbors:
#         x, y = neighbor
#         if x < 0 or y < 0 or x >= len(matrix) - 1 or y >= len(matrix) - 1 or original == neighbor:
#             continue
#         if matrix[x][y] == lookingFor:
#             if lookingForIndex == 3:
#                 global result
#                 print("HERE")
#                 result += 1
#             else:
#                 lookingForIndex += 1
#                 newNeighbors = []
#                 if original[0] - neighbor[0] > 0:

#                     newNeighbors = [(neighbor - 1)]
#                 helper(neighbor, newNeighbors, lookingForIndex)

for i, row in enumerate(matrix):
    for j, char in enumerate(row):
        if char == 'X':
            original = (i, j)
            neighbors = tupNearby(original, 1)
            for neighbor in neighbors:
                checkChar = 'M'
                checkCharIndex = 1
                original = (i, j)
                while checkCharIndex > 0:
                    x,y = neighbor
                    if (x >= len(matrix) or y >= len(matrix[0]) or x < 0 or y < 0):
                        break
                    neighborChar = matrix[x][y]
                    if neighborChar == checkChar:
                        differenceX = neighbor[0] - original[0]
                        differenceY = neighbor[1] - original[1]
                        original = neighbor
                        neighbor = (x + differenceX, y + differenceY)
                        x,y = neighbor
                        if checkCharIndex == 3:
                            result += 1
                            checkCharIndex = 0
                        else:
                            checkCharIndex += 1
                            checkChar = charList[checkCharIndex]
                    else:
                        checkCharIndex = 0

# list1.sort()
# list2.sort()
# list3.sort()

# for i, item in enumerate(list1):
#     sum +=  abs(item - list2[i])

pprint(result)
