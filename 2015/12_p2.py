#!/usr/bin/env python3

import json

data = None

# TODO: INCOMPLETE

def recurseData():
    while(type(data) == type(list)):
        

with open("input.txt", "r") as f:
    data = json.load(f)


print(len(data))
print(type(data))
for inside in data:
    print(type(inside))
    print(inside)

# print(arr)
print("="*80)
# print("Sum: " + str(sum))
# print("Additional Sum: " + str(sum2))
