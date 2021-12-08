#!/usr/bin/env python3

from typing import List, Dict, Set


def part_1() -> int:
    output_values: List[List[str]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            output = line.strip().split('|')[1].strip().split(' ')
            output_values.append(output)

    num_1, num_4, num_7, num_8 = 0, 0, 0, 0
    for vals in output_values:
        for val in vals:
            if len(val) == 4:
                num_4 += 1
            elif len(val) == 3:
                num_7 += 1
            elif len(val) == 2:
                num_1 += 1
            elif len(val) == 7:
                num_8 += 1
    return num_1 + num_4 + num_7 + num_8

def part_2() -> int:
    input_values: List[List[str]] = []
    output_values: List[List[str]] = []
    with open('input.txt', 'r') as f:
        for line in f:
            split = line.strip().split('|')
            input = split[0].strip().split(' ')
            input_values.append(input)
            output = split[1].strip().split(' ')
            output_values.append(output)

    # 2: 5, 0: 6, 9: 6, 6: 6, 5: 5
    res = 0
    for i, vals in enumerate(output_values):
        mapping_nums: List[frozenset] = [None] * 10
        mappings: Dict[Set[str], int] = {}
        for val in input_values[i]:
            val_set = frozenset(val)
            curr_num = None
            if len(val) == 4:
                curr_num = 4
            elif len(val) == 3:
                curr_num = 7
            elif len(val) == 2:
                curr_num = 1
            elif len(val) == 7:
                curr_num = 8
            if curr_num is not None:
                mappings[val_set] = curr_num
                mapping_nums[curr_num] = val_set


        for val in input_values[i]:
            if len(val) == 6:
                val_set = frozenset(val)
                curr_num = None
                if not mapping_nums[1].issubset(val_set):
                    curr_num = 6
                elif mapping_nums[7].issubset(val_set) and mapping_nums[4].issubset(val_set):
                    curr_num = 9
                else:
                    curr_num = 0
                mappings[val_set] = curr_num
                mapping_nums[curr_num] = val_set

        for val in input_values[i]:
            if len(val) == 5:
                val_set = frozenset(val)
                curr_num = None
                if val_set.issubset(mapping_nums[6]):
                    curr_num = 5
                else:
                    curr_num = 2
                mappings[val_set] = curr_num
                mapping_nums[curr_num] = val_set


        curr_num = ''
        for val in vals:
            val_set = frozenset(val)
            curr_num += str(mappings[val_set])
        res += int(curr_num)
    return res

if __name__ == '__main__':
    print(part_1())
    print(part_2())
