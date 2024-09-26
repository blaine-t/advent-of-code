#!/usr/bin/env python3

currNum = ""

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        prevNum = ""
        count = 0
        for char in line:
            if (prevNum != char and prevNum != ""):
                currNum += str(count) + prevNum
                count = 0
            prevNum = char
            count += 1
        currNum += str(count) + char

for i in range(1, 40):
    print(i)
    storedCurrNum = str(currNum)
    currNum = ""
    prevNum = ""
    count = 0
    for char in storedCurrNum:
        if (prevNum != char and prevNum != ""):
            currNum += str(count) + prevNum
            count = 0
        prevNum = char
        count += 1
    currNum += str(count) + char

print("="*80)
print(len(currNum))
