#!/usr/bin/env pypy
from lib import *

setDebug()
# setTest()


sum = 0
rows = 0
columns = 0
usedColumns = set()
usedRows = set()

galaxy = []

lines = readFileLines()
columns = len(lines[0])
rows = len(lines)
for i, l in enumerate(lines):
    row = []
    for j, c in enumerate(l):
        if(c == "#"):
            usedColumns.add(j)
            usedRows.add(i)
        row.append(c)
    galaxy.append(row)

lastUsed = False
for i, row in enumerate(galaxy):
    if(i not in usedRows and not lastUsed):
        for data in usedRows:
            data += 1
        newRow = []
        for col in row:
            newRow.append(".")
        galaxy.insert(i, newRow)
        lastUsed = True
    else:
        lastUsed = False

lastUsed = False
for i, row in enumerate(galaxy):
    for j, col in enumerate(row):
        if(j not in usedColumns and not lastUsed):
            for data in usedColumns:
                data += 1
            for innerRow in galaxy:
                innerRow.insert(j-1, ".")
            lastUsed = True
        else:
            lastUsed = False
    galaxy[i] = galaxy[i][:-1]
    
print(galaxy)