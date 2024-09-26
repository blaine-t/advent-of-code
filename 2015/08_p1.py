#!/usr/bin/env python3

chars = 0
codeChars = 0

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        skip = 0
        escaped = False
        for i, char in enumerate(line):
            chars += 1
            if (skip > 0):
                skip -= 1
            elif (char == "\\"):
                if escaped:
                    codeChars += 1
                escaped = not escaped
            elif (char == "\"" and escaped):
                codeChars += 1
                escaped = False
            elif (char == "x" and escaped):
                skip = 1
                escaped = False
            elif (i == 0 or i == len(line) - 1):
                codeChars = codeChars
            else:
                codeChars += 1


print("======")
print(chars)
print(codeChars)
print(chars - codeChars)
