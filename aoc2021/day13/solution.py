#!/usr/bin/env python3

from typing import List


def part_1() -> int:
    lines: List[List[str]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            lines.append(list(line))

    return 0

if __name__ == '__main__':
    print(part_1())
