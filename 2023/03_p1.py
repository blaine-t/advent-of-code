arr = []

starLocations = []

numData = []

validNums = 0

with open("input", "r") as f:
    for line in f:
        arr.append(list(line))

for i, line in enumerate(arr):
    for j, char in enumerate(line):
        if not char.isnumeric() and char != "." and char != "\n":
            starLocations.append((i, j))

for i, line in enumerate(arr):
    currNum = ""
    jNum = 0
    for j, char in enumerate(line):
        if (char.isnumeric()):
            if (len(currNum) == 0):
                jNum = j
            currNum += char
        else:
            if (len(currNum) != 0):
                numData.append((int(currNum), (i, jNum)))
                currNum = ""

print(len(numData))
print(len(starLocations))

for sl in starLocations:
    neighbors = []
    for i in range(-1, 2):
        for j in range(-1, 2):
            neighbors.append((sl[0] + i, sl[1] + j))
    for numDataOne in numData:
        stop = False
        for k in range(len(str(numDataOne[0]))):
            for neighbor in neighbors:
                if (not stop and (numDataOne[1][0], numDataOne[1][1] + k) == neighbor):
                    validNums += numDataOne[0]
                    stop = True

print(validNums)
