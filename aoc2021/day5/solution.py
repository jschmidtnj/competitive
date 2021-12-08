#!/usr/bin/env python3

from typing import List, Tuple, Dict


def part_1() -> int:
    lines: List[Tuple[Tuple[int, int], Tuple[int, int]]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            start, end = line.split(' -> ')
            start_x, start_y = (int(i) for i in start.split(','))
            end_x, end_y = (int(i) for i in end.split(','))
            curr_line = (start_x, start_y), (end_x, end_y)
            lines.append(curr_line)

    points: Dict[Tuple[int, int], List[int]] = {}
    for line_idx, line in enumerate(lines):
        start, end = line
        curr_points = []
        if start[0] == end[0]:
            min_elem, max_elem = min(start[1], end[1]), max(start[1], end[1])
            curr_points = [(start[0], y) for y in range(min_elem, max_elem + 1)]
        elif start[1] == end[1]:
            min_elem, max_elem = min(start[0], end[0]), max(start[0], end[0])
            curr_points = [(x, start[1]) for x in range(min_elem, max_elem + 1)]
        else:
            continue
        for point in curr_points:
            if point not in points:
                points[point] = []
            points[point].append(line_idx)

    num_overlap = 0
    for lines in points.values():
        if len(lines) > 1:
            num_overlap += 1

    return num_overlap

def part_2() -> int:
    lines: List[Tuple[Tuple[int, int], Tuple[int, int]]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            start, end = line.split(' -> ')
            start_x, start_y = (int(i) for i in start.split(','))
            end_x, end_y = (int(i) for i in end.split(','))
            curr_line = (start_x, start_y), (end_x, end_y)
            lines.append(curr_line)

    points: Dict[Tuple[int, int], List[int]] = {}
    for line_idx, line in enumerate(lines):
        start, end = line
        curr_points = []
        if start[0] == end[0]:
            min_elem, max_elem = min(start[1], end[1]), max(start[1], end[1])
            curr_points = [(start[0], y) for y in range(min_elem, max_elem + 1)]
        elif start[1] == end[1]:
            min_elem, max_elem = min(start[0], end[0]), max(start[0], end[0])
            curr_points = [(x, start[1]) for x in range(min_elem, max_elem + 1)]
        else:
            if start[0] > end[0]:
                start, end = end, start
            go_up = start[1] > end[1]
            curr_points = [(start[0] + i, start[1] + (-i if go_up else i)) for i in range(end[0] - start[0] + 1)]

        for point in curr_points:
            if point not in points:
                points[point] = []
            points[point].append(line_idx)

    num_overlap = 0
    for lines in points.values():
        if len(lines) > 1:
            num_overlap += 1

    return num_overlap


if __name__ == '__main__':
    print(part_1())
    print(part_2())
