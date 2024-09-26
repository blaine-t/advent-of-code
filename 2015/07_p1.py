#!/usr/bin/env python3

class Wire():
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def setValue(self, value):
        self.value = value

    def __str__(self):
        return self.name + ": " + str(self.value)


class Gate():
    def __init__(self, operator: str, w1: Wire, w2: Wire, w3: Wire):
        self.operator = operator
        self.w1 = w1
        self.w2 = w2
        self.w3 = w3

    def wiresDeclared(self):
        if (self.operator == "ASSIGN" or self.operator == "NOT"):
            return (self.w1.value != None)
        elif (self.operator == "AND" or self.operator == "OR" or self.operator == "LSHIFT" or self.operator == "RSHIFT"):
            return (self.w1.value != None and self.w2.value != None)

    def calcGate(self):
        match self.operator:
            case "ASSIGN":
                self.w2.setValue(self.w1.value)
            case "NOT":
                w1Bin = decToBin(self.w1.value)
                w2Bin = ""
                for char in w1Bin:
                    if (char == "0"):
                        w2Bin += "1"
                    else:
                        w2Bin += "0"
                self.w2.setValue(binToDec(w2Bin))
            case "AND":
                self.w3.setValue(self.w1.value & self.w2.value)
            case "OR":
                self.w3.setValue(self.w1.value | self.w2.value)
            case "LSHIFT":
                self.w3.setValue(self.w1.value << self.w2.value)
            case "RSHIFT":
                self.w3.setValue(self.w1.value >> self.w2.value)
            case _:
                return False
        return True


def decToBin(int):
    return '{0:016b}'.format(int)


def binToDec(bin):
    return int(bin, 2)


def createWire(name, value):
    for wire in wires:
        if (wire.name == name):
            return wire
    wire = Wire(name, value)
    wires.append(wire)
    return wire


wires: list[Wire] = []
gates: list[Gate] = []


def garbageCollectGates():
    passes = 1
    while (passes > 0):
        passes = 0
        for gate in gates:
            if gate.wiresDeclared():
                if gate.calcGate():
                    passes += 1
                    gates.remove(gate)


with open("input.txt", "r") as f:
    lines = f.read().splitlines()
    for line in lines:
        if ("AND" in line):
            w1Str = line.split(" ")[0]
            w1Val = None
            if (line[0].isnumeric()):
                w1Val = int(w1Str)
            w1 = createWire(w1Str, w1Val)
            w2 = createWire(line.split(" AND ")[1].split(" ")[0], None)
            w3 = createWire(line.split(" ")[-1], None)
            gates.append(Gate("AND", w1, w2, w3))
        elif ("OR" in line):
            w1 = createWire(line.split(" ")[0], None)
            w2 = createWire(line.split(" OR ")[1].split(" ")[0], None)
            w3 = createWire(line.split(" ")[-1], None)
            gates.append(Gate("OR", w1, w2, w3))
        elif ("LSHIFT" in line):
            w2str = line.split(" LSHIFT ")[1].split(" ")[0]
            w1 = createWire(line.split(" ")[0], None)
            w2 = createWire(w2str, int(w2str))
            w3 = createWire(line.split(" ")[-1], None)
            gates.append(Gate("LSHIFT", w1, w2, w3))
        elif ("RSHIFT" in line):
            w2str = line.split(" RSHIFT ")[1].split(" ")[0]
            w1 = createWire(line.split(" ")[0], None)
            w2 = createWire(w2str, int(w2str))
            w3 = createWire(line.split(" ")[-1], None)
            gates.append(Gate("RSHIFT", w1, w2, w3))
        elif ("NOT" in line):
            w1 = createWire(line.split(" ")[1], None)
            w2 = createWire(line.split(" ")[-1], None)
            gates.append(Gate("NOT", w1, w2, None))
        else:
            w1Str = line.split(" ")[0]
            w1Val = None
            if (line[0].isnumeric()):
                w1Val = int(w1Str)
            w1 = createWire(w1Str, w1Val)
            w2 = createWire(line.split(" ")[-1], None)
            gates.append(Gate("ASSIGN", w1, w2, None))

        garbageCollectGates()
    for wire in wires:
        print(wire)
    for wire in wires:
        if (wire.name == "a"):
            print(wire)
