#!/usr/bin/env pypy
from lib import *

# setDebug()
# setTest()

parts = []
starts = []
paths = []

props: list = ["x", "m", "a", "s"]

final = 0

def parsePath(p: list, s: str):
    i = props.index(s[0])
    if(s[1] == "<"):
        if(p[i] < reInt(s)):
            return True
        return False
    else:
        if(p[i] > reInt(s)):
            return True
        return False


lines = readFileLines()
for l in lines:
    if(len(l) > 0 and l[0] == "{"):
        parts.append(reInts(l))

for l in lines:
    if(len(l) > 0 and l[0] == "{"):
        break
    start = l.split("{")[0]
    starts.append(start)
    splitted = l[l.find("{") + 1 : -1].split(",")
    paths.append(splitted)

for part in parts:
    i = starts.index("in")
    broken = False
    while not broken:
        for instruction in paths[i]:
            next = None
            if(":" in instruction): 
                if(parsePath(part, instruction)):
                    next = instruction.split(":")[-1]
                else:
                    continue
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
