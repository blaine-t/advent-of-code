#!/usr/bin/env python3

sum = 0
sum2 = 0
arr = []


def vowelCount(str):
    count = 0
    for char in str:
        if (char == "a" or char == "e" or char == "i" or char == "o" or char == "u"):
            count += 1
    return count


def doubleCheck(str):
    prevChar = ""
    for char in str:
        if prevChar == char:
            return True
        prevChar = char
    return False


def badStrings(str):
    if ("ab" in str or "cd" in str or "pq" in str or "xy" in str):
        return False
    return True


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        if (vowelCount(line) >= 3 and doubleCheck(line) and badStrings(line)):
            sum += 1

print(sum)
