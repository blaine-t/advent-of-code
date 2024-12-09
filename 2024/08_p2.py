#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

sum = 0
list1 = []
list2 = []
lines = readFileLines()
xLength = len(lines[0])
yLength = len(lines)
antennaMap = {}
for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if char != '.' and char != '#':
            returnVal = antennaMap.get(char)
            if returnVal is None:
                antennaMap[char] = [(i, j)]
            else:
                returnVal.append((i, j))
                antennaMap[char] = returnVal

for frequency, antennas in antennaMap.items():
    for i, antenna in enumerate(antennas):
        otherAntennas: list[tuple] = antennas.copy()
        otherAntennas.pop(i)
        for j, otherAntenna in enumerate(otherAntennas):
            diffX = (antenna[0] - otherAntenna[0])
            diffY = (antenna[1] - otherAntenna[1])
            x = diffX + antenna[0]
            y = diffY + antenna[1]
            while x >= 0 and y >= 0 and (x < xLength) and (y < yLength):
                lineList = list(lines[x])
                lineList[y] = '#'
                lines[x] = "".join(lineList)
                x += diffX
                y += diffY


for line in lines:
    print(line)
    for char in line:
        if char != '.':
            sum += 1

pprint(sum)
