#!/usr/bin/env python3

from typing import List
from collections import Counter

def part_1() -> int:
    data: List[List[int]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            data.append([int(c) for c in line])

    if len(data) == 0:
        return 0

    num_digits = len(data[0])
    counters: List[Counter] = [Counter() for _ in range(num_digits)]
    for num in data:
        for i, digit in enumerate(num):
            counters[i][digit] += 1

    gamma, epsilon = [], []
    for counter in counters:
        gamma.append(counter.most_common()[0][0])
        epsilon.append(1 if gamma[-1] == 0 else 0)

    gamma_num, epsilon_num = 0, 0
    for i in range(num_digits):
        gamma_num += 2 ** (num_digits - i - 1) * gamma[i]
        epsilon_num += 2 ** (num_digits - i - 1) * epsilon[i]

    return gamma_num * epsilon_num

def part_2() -> int:
    data: List[List[int]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            line = line.strip()
            data.append([int(c) for c in line])

    if len(data) == 0:
        return 0

    num_digits = len(data[0])

    oxygen: List[List[int]] = [*data]
    co2: List[List[int]] = [*data]

    for i in range(num_digits):
        remove_oxygen = len(oxygen) > 1
        remove_co2 = len(co2) > 1
        if not remove_oxygen and not remove_co2:
            break

        if remove_oxygen:
            counter = Counter()
            for num in oxygen:
                counter[num[i]] += 1
            most_common = counter.most_common(2)
            most_common_elem: int = most_common[0][0]
            keep_elem = 1 if len(most_common) > 1 and most_common_elem == most_common[1][0] \
                else most_common_elem
            new_oxygen = []
            for elem in oxygen:
                if elem[i] != keep_elem:
                    new_oxygen.append(elem)
            oxygen = new_oxygen

        if remove_co2:
            counter = Counter()
            for num in co2:
                counter[num[i]] += 1
            most_common = counter.most_common(2)
            most_common_elem = most_common[0][0]
            least_common = 1 if most_common_elem == 0 else 0
            keep_elem = 0 if len(most_common) > 1 and most_common_elem == most_common[1][0] \
                else least_common
            new_co2 = []
            for elem in co2:
                if elem[i] != keep_elem:
                    new_co2.append(elem)
            co2 = new_co2

    if len(oxygen) != 1 or len(co2) != 1:
        raise ValueError('invalid input')

    oxygen_num, co2_num = 0, 0
    for i in range(num_digits):
        oxygen_num += 2 ** (num_digits - i - 1) * oxygen[0][i]
        co2_num += 2 ** (num_digits - i - 1) * co2[0][i]

    return oxygen_num * co2_num

if __name__ == '__main__':
    print(part_1())
    print(part_2())
