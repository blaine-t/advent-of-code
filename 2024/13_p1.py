#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

totalTokens = 0
list1 = []
list2 = []
list3 = []
lines = readFileLines()
xLength = len(lines[0])
yLength = len(lines)
imap = {}
buttonAs = []
buttonBs = []
prizes = []
regex = '^\d+'

def pythagorean(x, y):
    return math.sqrt(x**2 + y**2)

for i, line in enumerate(lines):
    mod = i % 4
    if (mod == 0):
        x, y = reInts(line)
        buttonAs.append((x, y))
    elif (mod == 1):
        x, y = reInts(line)
        buttonBs.append((x, y))
    elif (mod == 2):
        x, y = reInts(line)
        prizes.append((x, y))
    elif (mod == 3):
        continue

for i, prize in enumerate(prizes):
    tokens = 0
    x = 0
    y = 0
    initialPresses = 0
    totalAPresses = 0
    totalBPresses = 0
    bestTokens = 100000000
    buttonA = buttonAs[i]
    buttonB = buttonBs[i]
    buttonAx, buttonAy = buttonA
    buttonBx, buttonBy = buttonB
    prizeX, prizeY = prize
    buttonAdist = pythagorean(buttonAx, buttonAy) / 3
    buttonBdist = pythagorean(buttonBx, buttonBy)
    if (buttonAdist > buttonBdist):
        while(x < prizeX and y < prizeY) and totalAPresses < 100:
            x += buttonAx
            y += buttonAy
            tokens += 3
            initialPresses += 1
            totalAPresses += 1
        if (x == prizeX and y == prizeY and totalAPresses <= 100 and totalBPresses <= 100):
            break
        while (initialPresses > 0 and totalBPresses < 100):
            while (x > prizeX and y > prizeY):
                x -= buttonAx
                y -= buttonAy
                tokens -= 3
                initialPresses -= 1
                totalAPresses -= 1
            if (x == prizeX and y == prizeY):
                if (tokens < bestTokens):
                    bestTokens = tokens
            x += buttonBx
            y += buttonBy
            tokens += 1
            totalBPresses += 1
    else:
        while(x < prizeX and y < prizeY)  and totalBPresses < 100:
            x += buttonBx
            y += buttonBy
            tokens += 1
            initialPresses += 1
            totalBPresses += 1
        if (x == prizeX and y == prizeY):
            if (tokens < bestTokens):
                    bestTokens = tokens
        while (initialPresses > 0 and totalAPresses < 100):
            while (x > prizeX and y > prizeY):
                x -= buttonBx
                y -= buttonBy
                tokens -= 1
                initialPresses -= 1
                totalBPresses -= 1
            if (x == prizeX and y == prizeY):
                if (tokens < bestTokens):
                    bestTokens = tokens
            x += buttonAx
            y += buttonAy
            tokens += 3
            totalAPresses += 1
    if (x == prizeX and y == prizeY and totalAPresses <= 100 and totalBPresses <= 100):
        totalTokens += tokens
    elif (bestTokens != 100000000):
        totalTokens += bestTokens


pprint(totalTokens)

# 32719
# 33048
# 35574