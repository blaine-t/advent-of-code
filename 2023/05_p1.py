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


DEBUG = True

arr = []
cnt = 0
tot = 0

seeds = []
seedToSoil = []
soilToFertilizer = []
fertilizerToWater = []
waterToLight = []
lightToTemperature = []
temperatureToHumidity = []
humidityToLocation = []

def parseMap(s: str, map: list):
    nums = reInts(s)
    map.append(((nums[1], nums[1] + nums[2]), (nums[0], nums[0] + nums[2])))

if (len(argv) < 2):
    if DEBUG:
        argv.append("e")
    else:
        argv.append("i")

with open(argv[1], "r") as f:
    lines = f.read().splitlines()
    currentMap = None
    for i, l in enumerate(lines):
        if(i == 0):
            seeds = reInts(l)
        elif(i == 1):
            continue
        else:
            match l:
                case "seed-to-soil map:":
                    currentMap = seedToSoil
                case "soil-to-fertilizer map:":
                    currentMap = soilToFertilizer
                case "fertilizer-to-water map:":
                    currentMap = fertilizerToWater
                case "water-to-light map:":
                    currentMap = waterToLight
                case "light-to-temperature map:":
                    currentMap = lightToTemperature
                case "temperature-to-humidity map:":
                    currentMap = temperatureToHumidity
                case "humidity-to-location map:":
                    currentMap = humidityToLocation
            if(len(l) > 0 and l[0].isnumeric()):
                parseMap(l, currentMap)

locations = []

end = 0
for seed in seeds:
    end = seed
    for s in seedToSoil:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    for s in soilToFertilizer:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    for s in fertilizerToWater:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    for s in waterToLight:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    for s in lightToTemperature:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    for s in temperatureToHumidity:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    for s in humidityToLocation:
        if(end > s[0][0] and end < s[0][1]):
            end = s[1][0] + (end - s[0][0])
            break
    locations.append((seed, end))

minLocation = locations[0]
for location in locations:
    if(location[1] < minLocation[1]):
        minLocation = location

print("="*80)
if DEBUG:
    print("Array: " + str(seedToSoil))
    print("="*80)
print("Count: " + str(cnt))
print("Total: " + str(tot))
print(minLocation[1])