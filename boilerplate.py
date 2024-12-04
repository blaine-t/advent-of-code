#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(True)
setTest(False)

result = 0
list1 = []
list2 = []
list3 = []
regex = '^\d+'
for line in readFileLines():
    regResList = re.findall(regex, line)
    ints = reInts(line)

# list1.sort()
# list2.sort()
# list3.sort()

# for i, item in enumerate(list1):
#     sum +=  abs(item - list2[i])

pprint(result)
