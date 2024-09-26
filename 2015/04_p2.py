#!/usr/bin/env python3

import hashlib

sum = -1

input = "yzbqklnj"
hash = "111111"

while (hash[0:6] != "000000"):
    sum += 1
    hash = hashlib.md5((input + str(sum)).encode()).hexdigest()

print(sum)
