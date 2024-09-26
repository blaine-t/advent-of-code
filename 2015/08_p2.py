#!/usr/bin/env python3

chars = 0
encChars = 0
arr = []

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        # Quotes on each side
        encChars += 2
        for char in line:
            chars += 1
            if (char == "\""):
                encChars += 2
            elif (char == "\\"):
                encChars += 2
            else:
                encChars += 1


print(encChars)
print(chars)
print(encChars - chars)
