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
    ints = reInts(line)
    list1.append(ints[0])
    list2.append(ints[1])

list1.sort()
list2.sort()

for i, item in enumerate(list1):
    sum +=  item * list2.count(item)

pprint(sum)
