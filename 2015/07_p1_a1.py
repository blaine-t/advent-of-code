#!/usr/bin/env python3

class Wire:
    def __init__(self, name, value):
        self.name = name
        self.value = value
        self.parent = None

    def setValue(self, value):
        self.value = value

    def setParent(self, parent):
        self.parent = parent

    def getWire(name):
        for wire in wires:
            if (wire.name == name):
                return wire
        return createOrSetWire(name, 0)

    def __str__(self):
        return self.name + ": " + str(self.value)


wires: list[Wire] = []


def decToBin(int):
    return '{0:016b}'.format(int)


def binToDec(bin):
    return int(bin, 2)


def createOrSetWire(name, value):
    exists = False
    for wire in wires:
        if (wire.name == name):
            wire.setValue(value)
            exists = True
            return wire
    if (not exists):
        wire = Wire(name, value)
        wires.append(wire)
        return wire


def getWires(operator):
    w1str = line.split(operator)[0]
    w2str = line.split(operator)[1].split(" -")[0]
    w3str = line.split(" ")[-1]
    w1 = Wire.getWire(w1str)
    w2 = Wire.getWire(w2str)
    w3 = Wire.getWire(w3str)
    return (w1, w2, w3)


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        # AND
        if ("AND" in line):
            w1bin = ""
            if (line[0].isnumeric()):
                w1bin = decToBin(int(line[0]))
            w1, w2, w3 = getWires(" AND ")
            if (not line[0].isnumeric()):
                w1bin = decToBin(w1.value)
            w2bin = decToBin(w2.value)
            newStr = line.split(" ")[-1]
            newBin = '{0:016b}'.format(0)
            for i, bit in enumerate(w1bin):
                if (bit == w2bin[i]):
                    newBin = newBin[0:i] + bit + newBin[i+1:]
            createOrSetWire(newStr, binToDec(newBin))
        # OR
        elif ("OR" in line):
            w1, w2, w3 = getWires(" OR ")
            w1bin = decToBin(w1.value)
            w2bin = decToBin(w2.value)
            newStr = line.split(" ")[-1]
            newBin = '{0:016b}'.format(0)
            for i, bit in enumerate(w1bin):
                if (w1bin[i] == "1" or w2bin[i] == "1"):
                    newBin = newBin[0:i] + "1" + newBin[i+1:]
            createOrSetWire(newStr, binToDec(newBin))
        # NOT
        elif ("NOT" in line):
            w1 = Wire.getWire(line.split("NOT ")[1].split(" -")[0])
            w1bin = decToBin(w1.value)
            newStr = line.split(" ")[-1]
            newBin = ""
            for i, bit in enumerate(w1bin):
                newBit = "1"
                if bit == "1":
                    newBit = "0"
                newBin += newBit
            createOrSetWire(newStr, binToDec(newBin))
        # LSHIFT
        elif ("LSHIFT" in line):
            w1 = Wire.getWire(line.split(" ")[0])
            w2 = createOrSetWire(line.split(" ")[-1], 0)
            w1bin = decToBin(w1.value)
            for i in range(int(line.split("LSHIFT")[1].split(" -")[0])):
                w1bin = w1bin[1:] + "0"
            w2.setValue(binToDec(w1bin))
        # RSHIFT
        elif ("RSHIFT" in line):
            w1 = Wire.getWire(line.split(" ")[0])
            w2 = createOrSetWire(line.split(" ")[-1], 0)
            w1bin = decToBin(w1.value)
            for i in range(int(line.split("RSHIFT")[1].split(" -")[0])):
                w1bin = "0" + w1bin[0:-1]
            w2.setValue(binToDec(w1bin))
        # Signal
        elif (line[0].isnumeric()):
            name = line.split("> ")[1]
            value = int(line.split(" ")[0])
            createOrSetWire(name, value)
        # Assign
        else:
            w1 = Wire.getWire(line.split(" ")[0])
            w2 = Wire.getWire(line.split(" ")[-1])
            w2.setValue(w1.value)

for wire in wires:
    print(wire)
for wire in wires:
    if (wire.name == "a"):
        print(wire)
