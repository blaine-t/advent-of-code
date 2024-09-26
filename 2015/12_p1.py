#!/usr/bin/env python3

# sum = 0
# sum2 = 0
# arr = []

with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    openSquares = 0
    openCurlies = 0
    currNumber = ""
    numbers = []
    for line in lines:
        for i, char in enumerate(line):
            if (char == "{"):
                openCurlies += 1
            elif (char == "["):
                openSquares += 1
            elif (char == "}"):
                openCurlies -= 1
            elif (char == "]"):
                openSquares -= 1

            if (char.isnumeric() or char == "-"):
                currNumber += char
            else:
                if (len(currNumber) > 0):
                    numbers.append(int(currNumber))
                    currNumber = ""
    print(sum(numbers))


# print(arr)
print("="*80)
# print("Sum: " + str(sum))
# print("Additional Sum: " + str(sum2))
