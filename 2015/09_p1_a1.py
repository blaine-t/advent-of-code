#!/usr/bin/env python3

import math

shortestRoute = 0
arr = []


class Route():
    def __init__(self, source: str, destination: str, distance: int):
        self.source = source
        self.destination = destination
        self.distance = distance

    def __str__(self) -> str:
        return (self.source + " to " + self.destination + " = " + str(self.distance))


def findRoute(location, recurses):
    if (recurses < len(locations)):
        recurses += 1
        validRoutes = []
        for route in remainingRoutes:
            if (route.source == location):
                remainingRoutes.remove(route)
                validRoutes.append(route)
            return route.distance + findRoute(route.destination, recurses)
        return math.nan
    return route.distance


routes: list[Route] = []
remainingRoutes: list[Route]
locations: list[str] = []

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        words = line.split(" ")
        source = words[0]
        destination = words[2]
        if (source not in locations):
            locations.append(source)
        if (destination not in locations):
            locations.append(destination)
        routes.append(Route(source, destination, int(words[-1])))

for i, source in enumerate(locations):
    intermediateLocations = locations[i+1:] + locations[0:i]
    for j, intermediate in enumerate(intermediateLocations):
        for destination in intermediateLocations[j+1:] + intermediateLocations[0:j]:
            print(source + " " + intermediate + " " + destination)


for route in routes:
    print(route)
for location in locations:
    print(location)
print("="*80)
print(shortestRoute)
