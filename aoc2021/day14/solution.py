#!/usr/bin/env python3

from __future__ import annotations

from collections import Counter
from typing import List, Optional, Dict

class Node:
    def __init__(self, val: str, next: Optional[Node] = None) -> None:
        self.val = val
        self.next = next

def part_1() -> int:
    template: str = ''
    pair_dict: Dict[str, str] = {}
    with open('input.txt', 'r') as f:
        template = f.readline().strip()
        for line in f:
            line = line.strip()
            if not line:
                continue
            pair, val = line.split(' -> ')
            pair_dict[pair] = val

    start = Node(template[0])
    curr = start
    for val in template[1:]:
        curr.next = Node(val)
        curr = curr.next

    for _ in range(10):
        curr = start
        while curr.next:
            pair = curr.val + curr.next.val
            if pair in pair_dict:
                curr.next = Node(pair_dict[pair], curr.next)
                curr = curr.next
            curr = curr.next

    curr = start
    val: List[str] = []
    while curr:
        val.append(curr.val)
        curr = curr.next

    # print(''.join(val))

    count = Counter(val)
    most_common = count.most_common()

    return most_common[0][1] - most_common[-1][1]

def part_2() -> int:
    template: str = ''
    pair_dict: Dict[str, str] = {}
    with open('input.txt', 'r') as f:
        template = f.readline().strip()
        for line in f:
            line = line.strip()
            if not line:
                continue
            pair, val = line.split(' -> ')
            pair_dict[pair] = val

    start = Node(template[0])
    curr = start
    for val in template[1:]:
        curr.next = Node(val)
        curr = curr.next

    for i in range(40):
        print(i)
        curr = start
        while curr.next:
            pair = curr.val + curr.next.val
            if pair in pair_dict:
                curr.next = Node(pair_dict[pair], curr.next)
                curr = curr.next
            curr = curr.next

    curr = start
    val: List[str] = []
    while curr:
        val.append(curr.val)
        curr = curr.next

    # print(''.join(val))

    count = Counter(val)
    most_common = count.most_common()

    return most_common[0][1] - most_common[-1][1]

if __name__ == '__main__':
    print(part_1())
    print(part_2())
