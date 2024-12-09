#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

res = 0
lines = readFileLines()
line = lines[0]
imap = {}
id_count = 0
diskMap = []
for i, line in enumerate(lines):
    for j, char in enumerate(line):
        if j % 2 == 0:
            for k in range(int(char)):
                diskMap.append(id_count)
            id_count += 1
        else:
            for k in range(int(char)):
                diskMap.append(-1)

lastIndex = len(diskMap) - 1
for i, char in enumerate(diskMap):
    if char == -1:
        for j in range(lastIndex, i, -1):
            if diskMap[j] != -1:
                diskMap[i] = diskMap[j]
                diskMap[j] = -1
                lastIndex = j
                break

for i, char in enumerate(diskMap):
    if char != -1:
        res += i * char

pprint(res)

# 90950452031
# 5676434152
# 2248308792
# 6430446922192