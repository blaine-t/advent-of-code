#!/usr/bin/env python3

arr = []


def tabulateArray():
    sum = 0
    for row in arr:
        for val in row:
            sum += val
    return sum


def populateArray(amt):
    for i in range(amt):
        row = []
        for j in range(amt):
            row.append(0)
        arr.append(row)


def handleArray(start: str, end: str, command: str):
    startRow = int(start.split(",")[0])
    startCol = int(start.split(",")[1])
    endRow = int(end.split(",")[0])
    endCol = int(end.split(",")[1])

    for x in range(startRow, endRow + 1):
        for y in range(startCol, endCol + 1):
            arr[x][y] = arr[x][y] + handleCommand(command, arr[x][y])


def handleCommand(str, state):
    match str:
        case "turn on ":
            return 1
        case "turn off ":
            if (state > 0):
                return -1
            else:
                return 0
        case "toggle ":
            return 2


with open("input.txt", "r") as f:
    populateArray(1000)
    lines = f.read().splitlines()
    for line in lines:
        command = ""
        for char in line:
            if (not char.isnumeric()):
                command += char
            else:
                break
        start = line.split(" through ")[0].split(" ")[-1]
        end = line.split(" through ")[1]
        handleArray(start, end, command)

    print(tabulateArray())
