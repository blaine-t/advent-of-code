#!/usr/bin/env pypy
from lib import *

setDebug()
# setTest()

starts = []
paths = []

props: list = ["x", "m", "a", "s"]

final = 0

def parsePath(s: str) -> tuple:
    if(s[1] == "<"):
        return (1, reInt(s))
    else:
        return (reInt(s) + 1, 4001)


lines = readFileLines()
for l in lines:
    if(len(l) > 0 and l[0] == "{"):
        break
    start = l.split("{")[0]
    starts.append(start)
    splitted = l[l.find("{") + 1 : -1].split(",")
    paths.append(splitted)

i = starts.index("in")
broken = False
while not broken:
    for instruction in paths[i]:
        next = None
        if(":" in instruction):
            parsePath(instruction)
        else:
            next = instruction
        if next == "A":
            final += sum(part)
            broken = True
            break
        elif next == "R":
            broken = True
            break
        else:
            i = starts.index(next)
            break


print(final)
