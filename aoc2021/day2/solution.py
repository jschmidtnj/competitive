#!/usr/bin/env python3

from typing import Tuple, List

def part_1() -> int:
    data: List[Tuple[str, int]] = []
    with open("input.txt") as f:
        for line in f:
            elems = line.split()
            data.append((elems[0], int(elems[1])))

    position, depth = 0, 0
    for (direction, dist) in data:
        if direction == 'forward':
            position += dist
        elif direction == 'down':
            depth += dist
        else:
            depth -= dist

    return position * depth

def part_2() -> int:
    data: List[Tuple[str, int]] = []
    with open("input.txt") as f:
        for line in f:
            elems = line.split()
            data.append((elems[0], int(elems[1])))

    position, depth = 0, 0
    aim = 0
    for (direction, dist) in data:
        if direction == 'forward':
            position += dist
            depth += (aim * dist)
        elif direction == 'down':
            aim += dist
        else:
            aim -= dist

    return position * depth

if __name__ == '__main__':
    print(part_1())
    print(part_2())
