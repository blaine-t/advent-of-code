#!/usr/bin/env python3

if __name__ == "__main__":
    with open("input", "r") as f:
        sum = 0
        for line in f:
            firstNum = "-0"
            lastNum = "0"
            for char in line:
                if (char.isnumeric()):
                    if (firstNum == "-0"):
                        firstNum = char
                    lastNum = char
            num = firstNum + lastNum
            sum += int(num)
        print(sum)
