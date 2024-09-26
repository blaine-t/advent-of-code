#!/usr/bin/env python3

import math

sum = 0

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        count = 0
        cards = line.split(": ")[1].replace("  ", " ")
        winCards = cards.split(" | ")[0].split(" ")
        yourCards = cards.split(" | ")[1].split(" ")
        for card in yourCards:
            if (card in winCards):
                count += 1
        if (count > 0):
            sum += math.pow(2, count - 1)

print(sum)
