#!/usr/bin/env python3

from typing import List


def part_1() -> int:
    positions: List[int] = []
    with open('input.txt', 'r') as f:
        for line in f:
            positions.extend([int(s) for s in line.split(',')])

    print(positions)

    return 0

if __name__ == '__main__':
    print(part_1())
