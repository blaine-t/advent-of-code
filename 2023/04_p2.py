#!/usr/bin/env python3

sum = 0

wonCardIndices = []

lineLength = 0

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for i, line in enumerate(lines):
        lineLength += 1
        copies = 1
        for indices in wonCardIndices:
            if (indices == i):
                copies += 1
        count = 0
        cards = line.split(": ")[1].replace("  ", " ")
        winCards = cards.split(" | ")[0].split(" ")
        yourCards = cards.split(" | ")[1].split(" ")
        for cardNum in yourCards:
            if (cardNum in winCards):
                count += 1
                for j in range(copies):
                    wonCardIndices.append(i + count)

print(len(wonCardIndices) + lineLength)
