#!/usr/bin/env python3

from collections import defaultdict, deque


def part_1() -> int:
    graph = defaultdict(list)
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            parent, child = line.split('-')
            graph[parent].append(child)
            graph[child].append(parent)

    num_paths: int = 0
    to_check = deque([('start', set(['start']))])
    while to_check:
        parent, seen = to_check.popleft()
        if parent == 'end':
            num_paths += 1
            continue
        for child in graph[parent]:
            if child not in seen:
                seen_copy = seen.copy()
                if child.islower():
                    seen_copy.add(child)
                to_check.append((child, seen_copy))

    return num_paths

def part_2() -> int:
    graph = defaultdict(list)
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            parent, child = line.split('-')
            graph[parent].append(child)
            graph[child].append(parent)

    num_paths: int = 0
    to_check = deque([('start', set(['start']), False)])
    while to_check:
        parent, seen, visited = to_check.popleft()
        if parent == 'end':
            num_paths += 1
            continue
        for child in graph[parent]:
            if child not in seen:
                seen_copy = seen.copy()
                if child.islower():
                    seen_copy.add(child)
                to_check.append((child, seen_copy, visited))
            elif not visited and child not in ['start', 'end']:
                to_check.append((child, seen, child))

    return num_paths

if __name__ == '__main__':
    print(part_1())
    print(part_2())
