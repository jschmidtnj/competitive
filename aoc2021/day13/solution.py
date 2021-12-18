#!/usr/bin/env python3

import matplotlib.pyplot as plt
from typing import List, Tuple, Set


def part_1() -> int:
    dots: Set[Tuple[int, int]] = set()
    folds: List[Tuple[str, int]] = []
    fold_separator = 'fold along '
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if line.startswith(fold_separator):
                line = line.split(fold_separator)[1].strip()
                direction, val = line.split('=')
                val = int(val)
                folds.append((direction, val))
            else:
                dots.add(tuple(int(i) for i in line.split(',')))

    for direction, fold in folds[0:1]:
        for dot in list(dots):
            if direction == 'y':
                if dot[1] == fold:
                    dots.remove(dot)
                elif dot[1] > fold:
                    new_dot = (dot[0], 2 * fold - dot[1])
                    if new_dot not in dots:
                        dots.add(new_dot)
                    dots.remove(dot)
            else:
                if dot[0] == fold:
                    dots.remove(dot)
                elif dot[0] > fold:
                    new_dot = (2 * fold - dot[0], dot[1])
                    if new_dot not in dots:
                        dots.add(new_dot)
                    dots.remove(dot)

    return len(dots)

def part_2() -> int:
    dots: Set[Tuple[int, int]] = set()
    folds: List[Tuple[str, int]] = []
    fold_separator = 'fold along '
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if line.startswith(fold_separator):
                line = line.split(fold_separator)[1].strip()
                direction, val = line.split('=')
                val = int(val)
                folds.append((direction, val))
            else:
                dots.add(tuple(int(i) for i in line.split(',')))

    for direction, fold in folds:
        for dot in list(dots):
            if direction == 'y':
                if dot[1] == fold:
                    dots.remove(dot)
                elif dot[1] > fold:
                    new_dot = (dot[0], 2 * fold - dot[1])
                    if new_dot not in dots:
                        dots.add(new_dot)
                    dots.remove(dot)
            else:
                if dot[0] == fold:
                    dots.remove(dot)
                elif dot[0] > fold:
                    new_dot = (2 * fold - dot[0], dot[1])
                    if new_dot not in dots:
                        dots.add(new_dot)
                    dots.remove(dot)

    vals = list(zip(*list(dots)))
    plt.scatter(vals[0], vals[1])
    plt.gca().invert_yaxis()
    plt.show()

    return len(dots)

if __name__ == '__main__':
    print(part_1())
    print(part_2())
