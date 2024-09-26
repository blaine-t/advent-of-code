#!/usr/bin/env python3
from lib import *

DEBUG = False


def part1() -> str:
    with readFile() as f:
        flight = 0
        for l in f:
            for c in l:
                if (c == '('):
                    flight += 1
                elif (c == ')'):
                    flight -= 1
        return flight


def part2() -> str:
    with readFile() as f:
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
