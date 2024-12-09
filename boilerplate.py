#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(True)
setTest(False)

res = 0
list1 = []
list2 = []
list3 = []
lines = readFileLines()
xLength = len(lines[0])
yLength = len(lines)
imap = {}
regex = '^\d+'
for i, line in enumerate(lines):
    print(i, line)


for line in lines:
    for char in line:
        if char == '#':
            res += 1

# list1.sort()
# list2.sort()
# list3.sort()

# for i, item in enumerate(list1):
#     sum +=  abs(item - list2[i])

pprint(res)
