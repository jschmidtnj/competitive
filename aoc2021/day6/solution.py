#!/usr/bin/env python3

from typing import List
import numpy as np


def part_1() -> int:
    fish: List[int] = []
    with open('input.txt', 'r') as f:
        for line in f:
            fish.extend([int(s) for s in line.split(',')])

    for _ in range(80):
        to_append = 0
        for i, f in enumerate(fish):
            if f == 0:
                fish[i] = 6
                to_append += 1
            else:
                fish[i] -= 1
        fish.extend([8] * to_append)

    return len(fish)

def part_2() -> int:
    fish = np.array(0, dtype=np.ubyte)
    with open('input.txt', 'r') as f:
        for line in f:
            fish = np.append(fish, [int(s) for s in line.split(',')])

    for curr_iter in range(256):
        print(curr_iter)
        to_append = 0
        new_fish = np.array(0, dtype=np.ubyte)
        for f in np.nditer(fish, op_flags=['readwrite']):
            if f == 0:
                new_fish = np.append(new_fish, 6)
                to_append += 1
            else:
                new_fish = np.append(new_fish, f - 1)
        new_fish = np.append(new_fish, np.full(to_append, 8, dtype=np.ubyte))
        fish = new_fish


    return len(fish)

def part_2() -> int:
    fish = np.array(0, dtype=np.ubyte)
    with open('input.txt', 'r') as f:
        for line in f:
            fish = np.append(fish, [int(s) for s in line.split(',')])

    for curr_iter in range(256):
        print(curr_iter)
        to_append = 0
        for i, f in enumerate(fish):
            if f == 0:
                fish[i] = 6
                to_append += 1
            else:
                fish[i] -= 1
        fish = np.append(fish, np.full(to_append, 8, dtype=np.ubyte))

    return len(fish)

if __name__ == '__main__':
    print(part_1())
    print(part_2())
