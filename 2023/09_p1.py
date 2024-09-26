#!/usr/bin/env pypy
from lib import *

setDebug()
# setTest()


sum = 0

lines = readFileLines()
for l in lines:
    arrs: list[list[int]] = []
    arr = reInts(l, True)
    arrs.append(arr)
    while not checkAll(arr, 0):
        newArr = []
        for i in range(len(arr) - 1):
            newArr.append(arr[i+1] - arr[i])
        arrs.append(newArr)
        arr = newArr
    for i in range(len(arrs) - 1, -1, -1):
        if (i == len(arrs) - 1):
            arrs[i].append(arrs[i][-1])
        else:
            arrs[i].append(arrs[i+1][-1] + arrs[i][-1])
    sum += arrs[0][-1]
print(sum)
