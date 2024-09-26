#!/usr/bin/env python3
from sys import argv

import re

defaultSign = False

intRegex = '\d+'
intRegexSigned = '-?\d+'

floatRegex = '\d+\.?\d*'
floatRegexSigned = '-?\d+\.?\d*'


def reInt(string: str, signed=defaultSign) -> int:
    result = re.search(intRegexSigned if signed else intRegex, string)
    return int(result.group(0)) if result else None


def reInts(string: str, signed=defaultSign) -> list[int]:
    return list(map(int, re.findall(intRegexSigned if signed else intRegex, string)))


def reInts2d(string: str, signed=defaultSign) -> list[list[int]]:
    arr = []
    for line in string.splitlines():
        arr.append(reInts(line, signed))
    return arr


def reFloat(string: str, signed=defaultSign) -> float:
    result = re.search(floatRegexSigned if signed else floatRegex, string)
    return float(result.group(0)) if result else None


def reFloats(string: str, signed=defaultSign) -> list[float]:
    return list(map(float, re.findall(floatRegexSigned if signed else floatRegex, string)))


def reFloats2d(string: str, signed=defaultSign) -> list[list[float]]:
    arr = []
    for line in string.splitlines():
        arr.append(reFloats(line, signed))
    return arr


def len2d(arr: list):
    returnNum = 0
    for inner in arr:
        returnNum += len(inner)
    return returnNum


def sum2d(arr: list):
    returnNum = 0
    for inner in arr:
        returnNum += sum(inner)
    return returnNum


DEBUG = False

arr = []
cnt = 0
tot = 0

if (len(argv) < 2):
    if DEBUG:
        argv.append("e")
    else:
        argv.append("i")

with open(argv[1], "r") as f:
    print(reInts2d(f.read()))


print("="*80)
if DEBUG:
    print("Array: " + str(arr))
    print("="*80)
print("Count: " + str(cnt))
print("Total: " + str(tot))
