#!/usr/bin/env pypy3
from lib import *
import math
import re
from pprint import pprint
from sys import argv

setDebug(False)
setTest(False)

res = 0
# line = readFileLines()[0]
line = readFileLines()[0]
imap = {}
id_count = 0
diskMap = []
print(line)
for j, char in enumerate(line):
    if j % 2 == 0:
        for k in range(int(char)):
            diskMap.append(id_count)
        id_count += 1
    else:
        for k in range(int(char)):
            diskMap.append(-1)

print(diskMap)

lastIndex = len(diskMap) - 1
# for i, char in enumerate(diskMap):
#     if char == -1:
#         blank_length = 1
#         while i + blank_length < len(diskMap) - 1 and diskMap[i + blank_length] == -1:
#             blank_length += 1
#         for j in range(lastIndex, i, -1):
#             if diskMap[j] != -1:
#                 if j != len(diskMap) - 1 and diskMap[j] == diskMap[j + 1]:
#                     continue
#                 id_length = 1
#                 while j - id_length >= 0 and diskMap[j - id_length] == diskMap[j]:
#                     id_length += 1
#                 if (id_length <= blank_length):
#                     print("KMS", i, id_length)
#                     for k in range(id_length):
#                         diskMap[i + k] = diskMap[j - k]
#                         diskMap[j - k] = -1
#                     break
#                 print(i, id_length)
for i, id in enumerate(reversed(diskMap)):
    if id != -1:
        if i > 0:
            if diskMap[len(diskMap) - i] == id:
                continue
        id_count = 1
        while diskMap[len(diskMap) - i - id_count - 1] == id:
            id_count += 1
        for j, blank in enumerate(diskMap):
            if j >= len(diskMap) - i - 1:
                break
            if blank == -1:
                blank_count = 1
                while j + blank_count < len(diskMap) and diskMap[j + blank_count] == blank:
                    blank_count += 1
                if blank_count >= id_count:
                    for k in range(id_count):
                        diskMap[j + k] = diskMap[len(diskMap) - i - k - 1]
                        diskMap[len(diskMap) - i - k - 1] = -1
                    break

for i, char in enumerate(diskMap):
    if char != -1:
        res += i * char

print(diskMap)
pprint(res)

# 9643704483628
# 7673388650686