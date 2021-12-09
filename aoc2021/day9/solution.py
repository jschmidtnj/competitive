#!/usr/bin/env python3

from typing import List, Tuple, Set


def part_1() -> int:
    heights: List[List[int]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            curr_heights: List[int] = []
            for h in line:
                curr_heights.append(int(h))
            heights.append(curr_heights)

    res = 0
    for i, row in enumerate(heights):
        for j, h in enumerate(row):
            if (j == 0 or h < row[j - 1]) and \
                (j == len(row) - 1 or h < row[j + 1]) and \
                (i == 0 or h < heights[i - 1][j]) and \
                (i == len(heights) - 1 or h < heights[i + 1][j]):
                res += (h + 1)
    return res

def get_basin(row: int, col: int, heights: List[List[int]]) -> Set[Tuple[int,int]]:
    res: Set[Tuple[int, int]] = set()

    queue = [(row, col)]
    while queue:
        i, j = queue.pop()
        if heights[i][j] != 9:
            res.add((i, j))
            neighbors = [(i - 1, j), (i + 1, j), (i, j - 1), (i, j + 1)]

            for elem in neighbors:
                if elem not in res and 0 <= elem[0] < len(heights) \
                    and 0 <= elem[1] < len(heights[i]):
                    queue.append(elem)

    return res

def part_2() -> int:
    heights: List[List[int]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            curr_heights: List[int] = []
            for h in line:
                curr_heights.append(int(h))
            heights.append(curr_heights)

    basins: List[int] = []
    coords_in_basin = set()
    for i, row in enumerate(heights):
        for j, _ in enumerate(row):
            if (i, j) not in coords_in_basin:
                basin = get_basin(i, j, heights)
                basins.append(len(basin))
                coords_in_basin.update(basin)

    res: int = 1
    for num in sorted(basins)[-3:]:
        res *= num

    return res


if __name__ == '__main__':
    print(part_1())
    print(part_2())
