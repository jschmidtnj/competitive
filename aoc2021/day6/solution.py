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
    data: List[int] = []
    with open('input.txt') as f:
        data = list(map(int, f.read().split(',')))

    ages = [0] * 10
    for i in data:
        ages[i] += 1

    for _ in range(256):
        curr = ages[0]
        for i in range(1, 9):
            ages[i - 1] = ages[i]
        ages[8] = curr
        ages[6] += curr

    return sum(ages)

if __name__ == '__main__':
    print(part_1())
    print(part_2())
