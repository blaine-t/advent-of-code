#!/usr/bin/env python3

sum = 0
sum2 = 0
arr = []

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        for char in line:
            print(char)

print(arr)
print("="*80)
print("Sum: " + str(sum))
print("Additional Sum: " + str(sum2))
