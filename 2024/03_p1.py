#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

sum = 0
regex = 'mul\(\d+,\d+\)'
for line in readFileLines():
    result = re.findall(regex, line)
    for mul in result:
        nums = reInts(mul)
        sum += nums[0] * nums[1]

pprint(sum)
