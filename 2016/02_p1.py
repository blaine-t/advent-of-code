sum = 0
arr = []


def area(l, w, h):
    extraside = 0
    side1 = 2*l*w
    side2 = 2*w*h
    side3 = 2*h*l
    if (side1 <= side2 and side1 <= side3):
        extraside = int(side1/2)
    elif (side2 <= side1 and side2 <= side3):
        extraside = int(side2/2)
    else:
        extraside = int(side3/2)

    return side1 + side2 + side3 + extraside


with open("input", "r") as f:
    for line in f:
        dimensions = line.split("x")
        sum += area(int(dimensions[0]), int(dimensions[1]), int(dimensions[2]))

print(arr)
print(sum)
