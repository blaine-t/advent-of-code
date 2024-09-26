rib = 0


def ribbon(l, w, h):
    return ((l + l + w + w) + (l*w*h))


with open("input", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        dimensions = line.split("x")
        dimensions[0] = int(dimensions[0])
        dimensions[1] = int(dimensions[1])
        dimensions[2] = int(dimensions[2])
        dimensions.sort()
        rib += ribbon(int(dimensions[0]),
                      int(dimensions[1]), int(dimensions[2]))

print(rib)
