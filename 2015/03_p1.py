#!/usr/bin/env python3

deliveries = 0
houses = []


def delivered(address):
    print(address)
    valid = 1
    for house in houses:
        if (address == house):
            valid = 0
            break
    if valid == 1:
        houses.append(address)
    return valid


with open("input", "r") as f:
    lines = f.read().splitlines()
    location = (0, 0)
    deliveries += delivered(location)
    for line in lines:
        for char in line:
            match char:
                case "^":
                    location = (location[0] + 1, location[1])
                    deliveries += delivered(location)
                case ">":
                    location = (location[0], location[1] + 1)
                    deliveries += delivered(location)
                case "v":
                    location = (location[0] - 1, location[1])
                    deliveries += delivered(location)
                case "<":
                    location = (location[0], location[1] - 1)
                    deliveries += delivered(location)

print(deliveries)
