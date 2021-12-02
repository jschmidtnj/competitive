#!/usr/bin/env python3

from typing import Optional, List

def part_1() -> int:
    count = 0
    last: Optional[int] = None
    with open("input.txt") as f:
        for line in f:
            curr = int(line)
            if last is not None and last < curr:
                count += 1
            last = curr
    return count

def part_2() -> int:
    data: List[int] = []
    with open("input.txt") as f:
        for line in f:
            curr = int(line)
            data.append(curr)
    count = 0
    last: Optional[int] = None
    for i, _ in enumerate(data):
        curr = sum(data[i:i+3])
        if last is not None and last < curr:
            count += 1
        last = curr
    return count

if __name__ == '__main__':
    print(part_1())
    print(part_2())
