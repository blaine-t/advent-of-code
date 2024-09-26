#!/usr/bin/env python3

import re

MAX_RED = 12
MAX_GREEN = 13
MAX_BLUE = 14

if __name__ == "__main__":
    result = 0
    with open("input", "r") as f:
        for line in f:
            id = int(re.findall(r'\d+', line.split(":")[0])[0])
            rounds = line.split(": ")[1].split("; ")
            reds = 0
            greens = 0
            blues = 0
            for round in rounds:
                cubes = round.split(", ")
                for cube in cubes:
                    if ("red" in cube):
                        curr = int(cube.split(" ")[0])
                        if (reds < curr):
                            reds = curr
                    elif ("green" in cube):
                        curr = int(cube.split(" ")[0])
                        if (greens < curr):
                            greens = curr
                    elif ("blue" in cube):
                        curr = int(cube.split(" ")[0])
                        if (blues < curr):
                            blues = curr
            result += reds * greens * blues
    print(result)
