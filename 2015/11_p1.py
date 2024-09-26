#!/usr/bin/env python3

password = "hxbxwazz"


def iteratePassword():
    global password
    newPassword = ""
    changed = False
    nextChange = False
    for char in password[::-1]:
        if (nextChange and not changed and char != "z"):
            char = chr(ord(char) + 1)
            changed = True
        elif (nextChange and not changed and char == "z"):
            char = "a"
        elif (not changed and char != "z"):
            char = chr(ord(char) + 1)
            changed = True
        elif (not nextChange and not changed and char == "z"):
            char = "a"
            nextChange = True
        newPassword += char
    password = newPassword[::-1]


def checkStraight():
    global password
    prev2Char = "1"
    prevChar = "1"
    for char in password:
        if (char == chr(ord(prevChar) + 1) and char == chr(ord(prev2Char) + 2)):
            return True
        prev2Char = prevChar
        prevChar = char
    return False


def goodLetters():
    global password
    for char in password:
        if (char == "i" or char == "o" or char == "l"):
            return False
    return True


def twoOverlapPairs():
    global password
    count = 0
    prevChar = ""
    for char in password:
        if (char == prevChar):
            count += 1
            char = ""
        prevChar = char
    return count >= 2


iteratePassword()
print(password)

while (not checkStraight() or not goodLetters() or not twoOverlapPairs()):
    iteratePassword()

print("="*80)
print(password)
