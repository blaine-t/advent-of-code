#!/usr/bin/env pypy
from sys import argv
import math
import re

from lib import *

DEBUG = False

ranks = ["2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"]


def handType(hand: str):
    highestSet = 0
    secondHighestSet = 0
    for card in hand:
        count = hand.count(card)
        hand = hand.replace(card, "")
        if (count >= highestSet):
            secondHighestSet = highestSet
            highestSet = count
        elif (count > secondHighestSet):
            secondHighestSet = count
    if (highestSet == 5):
        return 6
    elif (highestSet == 4):
        return 5
    elif (highestSet == 3 and secondHighestSet == 2):
        return 4
    elif (highestSet == 3):
        return 3
    elif (highestSet == 2 and secondHighestSet == 2):
        return 2
    elif (highestSet == 2):
        return 1
    else:
        return 0


def compareHands(hand1: tuple, hand2: tuple):
    if (hand1[0] > hand2[0]):
        return hand1
    elif (hand2[0] > hand1[0]):
        return hand2
    for i in range(len(hand1[1])):
        hand1Index = ranks.index(hand1[1][i])
        hand2Index = ranks.index(hand2[1][i])
        if hand1Index > hand2Index:
            return hand1
        elif hand2Index > hand1Index:
            return hand2


def part1() -> str:
    with readFile() as f:
        hands = []
        for l in f.read().splitlines():
            hand = l.split()[0]
            bid = int(l.split()[1])
            hands.append((handType(hand), hand, bid))

    for i in range(len(hands) - 1):
        for j in range(1, len(hands)):
            if (hands[j - 1] == compareHands(hands[j], hands[j - 1])):
                temp = hands[j]
                hands[j] = hands[j - 1]
                hands[j - 1] = temp

    print(compareHands(hands[784], hands[785]))
    sum = 0
    for i in range(1, len(hands) + 1):
        addition = hands[i-1][2] * (i)
        # print(
        #     f'Rank: {i}, Hand: {hands[i-1][1]}, Type: {hands[i-1][0]}')
        sum += addition

    return sum


def part2() -> str:
    with readFile() as f:
        for l in f.read().splitlines():
            print('='*80)
            return l


print(f'Part 1: {part1()}')
print('='*40)
# print(f'Part 2: {part2()}')

# 251430867
# 251572857
# 250996892
# 250944014
# 250946742
