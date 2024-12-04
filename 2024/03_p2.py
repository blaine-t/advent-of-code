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
enabled = True
for line in readFileLines():
    dos = line.split('do()')
    if not enabled:
        dos.pop(0)
    for do in dos:
        splitted = do.split("don't()")
        use = splitted[0]
        if len(splitted) > 1:
            enabled = False
        else:
            enabled = True
        result = re.findall(regex, use)
        for mul in result:
            nums = reInts(mul)
            sum += nums[0] * nums[1]

pprint(sum)

# TOO HIGH
# 93733733