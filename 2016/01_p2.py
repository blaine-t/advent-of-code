#!/usr/bin/env python3

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        for char in line:
            print(char)

print("="*80)
