#!/usr/bin/env python3

from itertools import permutations

names = []
happy = []

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    prevName = ""
    currHappinessArray = []
    for line in lines:
        name = line.split(" ")[0]
        if (name not in names):
            names.append(name)
        if (prevName != "" and prevName != name):
            happy.append(currHappinessArray.copy())
            currHappinessArray = []
        numStr = ""
        for i, char in enumerate(line):
            if (char.isnumeric()):
                numStr += char
                j = 1
                while (line[i + j].isnumeric()):
                    numStr += line[i + j]
                    j += 1
                break
        num = int(numStr)
        if (len(currHappinessArray) == len(names) - 1):
            currHappinessArray.append(None)
        currHappinessArray.append(num)
        prevName = name
    currHappinessArray.append(None)
    happy.append(currHappinessArray.copy())
    currHappinessArray = []

p = permutations(names)

tableList = []

for a in p:
    aList = list(a)
    aList.insert(0, aList[-1])
    aList.append(aList[1])
    tableList.append(aList)

for i, table in enumerate(tableList):
    if (i == 0 or i == len(tableList) - 1):
        continue
    name = names.index(table[i])


print("="*80)
for i, name in enumerate(names):
    print(name)
    for hap in happy[i]:
        print(hap, end=", ")
    print()
