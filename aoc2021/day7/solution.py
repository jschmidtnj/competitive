#!/usr/bin/env python3

from typing import List


def part_1() -> int:
    positions: List[int] = []
    with open('input.txt', 'r') as f:
        for line in f:
            positions.extend([int(s) for s in line.split(',')])

    positions.sort()
    midpoint = positions[len(positions) // 2]
    res = 0
    for pos in positions:
        res += abs(pos - midpoint)

    return res

def part_2() -> int:
    positions: List[int] = []
    with open('input.txt', 'r') as f:
        for line in f:
            positions.extend([int(s) for s in line.split(',')])

    positions.sort()
    res = float('inf')
    # do binary search to go faster
    # could be done in nlogn
    for elem in range(positions[0], positions[-1] + 1):
        curr = 0
        for pos in positions:
            dist = abs(pos - elem)
            dist = dist * (dist + 1) // 2
            curr += dist
        res = min(res, curr)

    return res

if __name__ == '__main__':
    print(part_1())
    print(part_2())
