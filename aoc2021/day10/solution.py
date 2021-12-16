#!/usr/bin/env python3

from typing import List, Dict


def part_1() -> int:
    lines: List[List[str]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            lines.append(list(line))

    point_map: Dict[str, int] = {
        ')': 3,
        ']': 57,
        '}': 1197,
        '>': 25137
    }

    char_map: Dict[str, str] = {
        '{': '}',
        '(': ')',
        '[': ']',
        '<': '>'
    }

    points: int = 0
    for line in lines:
        stack: List[str] = []
        for char in line:
            if char in char_map:
                stack.append(char)
                continue
            if len(stack) == 0:
                break
            prev = stack.pop()
            if char_map[prev] != char:
                points += point_map[char]
                break

    return points

def part_2() -> int:
    lines: List[List[str]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            lines.append(list(line))

    point_map: Dict[str, int] = {
        ')': 1,
        ']': 2,
        '}': 3,
        '>': 4
    }
    mult_points: int = 5

    char_map: Dict[str, str] = {
        '{': '}',
        '(': ')',
        '[': ']',
        '<': '>'
    }

    points: List[int] = []
    for line in lines:
        stack: List[str] = []
        corrupted = False
        for char in line:
            if char in char_map:
                stack.append(char)
                continue
            if len(stack) == 0:
                break
            prev = stack.pop()
            if char_map[prev] != char:
                corrupted = True
                break
        if not corrupted:
            points.append(0)
            while stack:
                opening = stack.pop()
                closing = char_map[opening]
                points[-1] *= mult_points
                points[-1] += point_map[closing]

    points.sort()

    return points[len(points) // 2]

if __name__ == '__main__':
    print(part_1())
    print(part_2())
