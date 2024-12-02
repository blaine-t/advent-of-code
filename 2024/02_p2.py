#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

sum = 0
list1 = []
list2 = []
for line in readFileLines():
    nums = reInts(line)
    oldNum = -1
    increasing = None
    safe = True
    ultimateSafe = False
    for i, num in enumerate(nums):
        if oldNum == -1:
            oldNum = num
            continue
        if increasing == None:
            if oldNum < num:
                increasing = True
            else:
                increasing = False
        difference = num - oldNum
        if increasing:
            if difference >= 1 and difference <= 3:
                oldNum = num
                continue
            else:
                safe = False
                break
        else:
            difference *= -1
            if difference >= 1 and difference <= 3:
                oldNum = num
                continue
            else:
                safe = False
                break
    if safe:
        ultimateSafe = True
        sum += 1
    else:
        originalNums = nums.copy()
        for index in range(len(originalNums)):
            nums = originalNums.copy()
            nums.pop(index)
            oldNum = -1
            increasing = None
            safe = True
            for i, num in enumerate(nums):
                if oldNum == -1:
                    oldNum = num
                    continue
                if increasing == None:
                    if oldNum < num:
                        increasing = True
                    else:
                        increasing = False
                difference = num - oldNum
                if increasing:
                    if difference >= 1 and difference <= 3:
                        oldNum = num
                        continue
                    else:
                        safe = False
                        break
                else:
                    difference *= -1
                    if difference >= 1 and difference <= 3:
                        oldNum = num
                        continue
                    else:
                        safe = False
                        break
            if safe:
                ultimateSafe = True
                sum += 1
                break
        


pprint(sum)
