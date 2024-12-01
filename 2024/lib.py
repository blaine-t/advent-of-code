import math
import re
from pprint import pprint
from sys import argv

DEBUG = False
TEST = False

defaultSign = False

intRegex = '\d+'
intRegexSigned = '-?\d+'

floatRegex = '\d+\.?\d*'
floatRegexSigned = '-?\d+\.?\d*'


def setDebug(debug=True):
    global DEBUG
    DEBUG = debug


def setTest(test=True):
    global TEST
    TEST = test


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


def tupNearby(tup: tuple, depth=1) -> list[tuple]:
    arr = []
    for x in range(tup[0] - depth, tup[0] + depth + 1):
        for y in range(tup[1] - depth, tup[1] + depth + 1):
            arr.append((x, y))
    return arr


def moveTupDir(direction: str, pos: tuple, inverse=1) -> tuple:
    match direction[0].upper():
        case "U":
            pos = (pos[0], pos[1] + 1 * inverse)
        case "D":
            pos = (pos[0], pos[1] - 1 * inverse)
        case "L":
            pos = (pos[0] - 1 * inverse, pos[1])
        case "R":
            pos = (pos[0] + 1 * inverse, pos[1])
    return pos


def readFile() -> str:
    filename = None

    if (len(argv) < 2):
        if TEST:
            filename = 't.txt'
        elif DEBUG:
            filename = 'e.txt'
        else:
            filename = 'i.txt'
    else:
        if ('.txt' not in argv[1]):
            filename = argv[1] + '.txt'
        else:
            filename = argv[1]
    return open(filename, 'r').read()


def readFileLines() -> list[str]:
    return readFile().splitlines()


def readFileChunk() -> list[list[str]]:
    arr = []
    inner = []
    lines = readFileLines()
    for line in lines:
        if (line == ''):
            if (len(inner) != 0):
                arr.append(inner)
                inner = []
        else:
            inner.append(line)
    if (len(inner) != 0):
        arr.append(inner)
    return arr


def checkAll(arr, check):
    for i in arr:
        if (i != check):
            return False
    return True
