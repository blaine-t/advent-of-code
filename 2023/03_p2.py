arr = []

starLocations = []

numData = []

validNums = 0

with open("input", "r") as f:
    for line in f:
        arr.append(list(line))

for i, line in enumerate(arr):
    for j, char in enumerate(line):
        if char == "*":
            starLocations.append([i, j, None, None])

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
    stop = False
    neighbors = []
    for i in range(-1, 2):
        for j in range(-1, 2):
            neighbors.append((sl[0] + i, sl[1] + j))
    for numDataOne in numData:
        semiStop = False
        for k in range(len(str(numDataOne[0]))):
            for neighbor in neighbors:
                if (not stop and not semiStop and (numDataOne[1][0], numDataOne[1][1] + k) == neighbor):
                    if (sl[2] == None):
                        semiStop = True
                        sl[2] = numDataOne[0]
                    elif (sl[3] == None):
                        semiStop = True
                        sl[3] = numDataOne[0]
                    else:
                        stop = True
    if (not stop and sl[2] != None and sl[3] != None):
        validNums += (sl[2] * sl[3])
print(validNums)
