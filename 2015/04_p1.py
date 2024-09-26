#!/usr/bin/env python3

import hashlib

sum = -1

input = "pqrstuv"
hash = "11111"

while (hash[0:5] != "00000"):
    sum += 1
    hash = hashlib.md5((input + str(sum)).encode()).hexdigest()

print(sum)
