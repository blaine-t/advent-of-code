#!/usr/bin/env python3
from sys import argv
import lib

DEBUG = False
filename = None

if (len(argv) < 2):
    if DEBUG:
        filename = 'e.txt'
    else:
        filename = 'i.txt'
else:
    if ('.txt' not in argv[1]):
        filename = argv[1] + '.txt'
    else:
        filename = argv[1]


def part1() -> str:
    with open(filename, 'r') as f:
        flight = 0
        for l in f:
            for c in l:
                if (c == '('):
                    flight += 1
                elif (c == ')'):
                    flight -= 1
        return flight


def part2() -> str:
    with open("i.txt", "r") as f:
        flight = 0
        for line in f:
            for i, char in enumerate(line):
                if (char == "("):
                    flight += 1
                elif (char == ")"):
                    flight -= 1
                if flight == -1:
                    return (i + 1)


print(f'Part 1: {part1()}')
print(f'Part 2: {part2()}')
