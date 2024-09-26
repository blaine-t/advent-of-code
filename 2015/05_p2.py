#!/usr/bin/env python3

sum = 0
sum2 = 0
arr = []


def doubleSeperate(str):
    prevprevChar = ""
    prevChar = ""
    for char in str:
        if (prevprevChar == char):
            return True
        prevprevChar = prevChar
        prevChar = char
    return False


def doubleCheck(str):
    prevprevChar = ""
    prevChar = " "
    prevChars = []
    for char in str:
        if prevChar + char in prevChars and prevChar != prevprevChar:
            return True
        else:
            prevChars.append(prevChar + char)
        prevprevChar = prevChar
        prevChar = char
    return False


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        if (doubleSeperate(line) and doubleCheck(line)):
            sum += 1

print(sum)
