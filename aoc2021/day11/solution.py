#!/usr/bin/env python3

import numpy as np
from scipy.signal import convolve2d
from typing import List, Set, Tuple


def part_1() -> int:
    octopuses: List[List[int]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            octopuses.append([int(o) for o in line])

    num_steps: int = 100

    flashes: int = 0
    for _ in range(num_steps):
        for i, row in enumerate(octopuses):
            for j, _ in enumerate(row):
                octopuses[i][j] += 1

        curr_flashes: Set[Tuple[int, int]] = set()
        changed = True
        while changed:
            changed = False
            for i, row in enumerate(octopuses):
                for j, level in enumerate(row):
                    if (i, j) in curr_flashes:
                        continue
                    if level > 9:
                        changed = True
                        curr_flashes.add((i, j))
                        octopuses[i][j] = 0
                        for k in range(-1, 2):
                            for l in range(-1, 2):
                                if k == i and l == j:
                                    continue
                                r, c = i + k, j + l
                                if r < 0 or r >= len(octopuses) or c < 0 or c >= len(row):
                                    continue
                                if (r, c) in curr_flashes:
                                    continue
                                octopuses[r][c] += 1
        flashes += len(curr_flashes)

    return flashes

def part_2() -> int:
    octopuses: List[List[int]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            octopuses.append([int(o) for o in line])

    octopuses = np.array(octopuses, dtype='int')

    c = []
    steps = 0
    while True:
        mask = np.array([[1, 1, 1], [1, 0, 1], [1, 1, 1]])
        flash = np.zeros(octopuses.shape, dtype='bool')
        octopuses += 1
        while np.any(flashing := octopuses > 9):
            flash |= flashing
            octopuses += convolve2d(flashing, mask, mode='same')
            octopuses[flash] = 0
        c += [flash.sum()]
        steps += 1

        if np.all(octopuses == 0):
            return steps

if __name__ == '__main__':
    print(part_1())
    print(part_2())
