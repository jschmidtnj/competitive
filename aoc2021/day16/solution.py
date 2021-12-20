#!/usr/bin/env python3

from __future__ import annotations

from typing import List, Optional
from enum import Enum


def part_1() -> int:
    input_data: str = ''
    with open('input.txt', 'r') as f:
        input_data = ''.join(f.readlines()).strip()

    bin_data = bin(int(input_data, 16))[2:]
    bin_data = '0' * (len(bin_data) % 4) + bin_data
    print(bin_data, len(bin_data))

    versions_sum = 0
    bit_idx = 0
    while bit_idx < len(bin_data):
        packet_version = int(bin_data[bit_idx: bit_idx + 3], 2)
        print(f'packet version {packet_version}')
        bit_idx += 3
        versions_sum += packet_version
        type_id = int(bin_data[bit_idx: bit_idx + 3], 2)
        bit_idx += 3
        if type_id == 4:
            # literal value
            literal_digits: List[str] = []
            continue_literal = True
            while continue_literal:
                continue_literal = bin_data[bit_idx] == str(1)
                bit_idx += 1
                literal_digits.extend(bin_data[bit_idx: bit_idx + 4])
                bit_idx += 4
            literal = int(''.join(literal_digits), 2)
            print(f'found literal {literal}')
        else:
            # operator value
            length_type = int(bin_data[bit_idx], 2)
            bit_idx += 1
            if length_type == 0:
                subpacket_bits_bin = bin_data[bit_idx: bit_idx + 15]
                if len(subpacket_bits_bin) == 0:
                    break
                subpacket_bits = int(subpacket_bits_bin, 2)
                bit_idx += 15
                print(f'subpacket bits: {subpacket_bits}')
            else:
                num_subpackets_bin = bin_data[bit_idx: bit_idx + 11]
                if len(num_subpackets_bin) == 0:
                    break
                num_subpackets = int(num_subpackets_bin, 2)
                bit_idx += 11
                print(f'num subpackets: {num_subpackets}')

    return versions_sum


class Types(Enum):
    Sum = 0
    Product = 1
    Minimum = 2
    Maximum = 3
    Literal = 4
    GT = 5
    LT = 6
    EQ = 7


class Node:
    def __init__(self, type: int, children: List[Node] = []) -> None:
        self.type = type
        self.children = children
        self.curr_num_subpackets: int = 0
        self.curr_subpacket_bits: int = 0
        self.num_subpackets: Optional[int] = None
        self.subpacket_bits: Optional[int] = None

        value = None
        if self.type == Types.Sum:
            value = 0
        elif self.type == Types.Product:
            value = 1
        elif self.type == Types.Minimum:
            value = float('inf')
        elif self.type == Types.Maximum:
            value = float('-inf')
        elif self.type == Types.Literal:
            value = None
        elif self.type == Types.GT:
            value = None
        elif self.type == Types.LT:
            value = None
        elif self.type == Types.EQ:
            value = None

        self.value = value

    def operate(self, node: Node) -> None:
        if self.type == Types.Sum:
            self.value += node.value
        elif self.type == Types.Product:
            self.value *= node.value
        elif self.type == Types.Minimum:
            self.value = min(self.value, node.value)
        elif self.type == Types.Maximum:
            self.value = max(self.value, node.value)
        elif self.type == Types.Literal:
            self.value = node.value
        elif self.type == Types.GT:
            if not self.value:
                self.value = node.value
            else:
                self.value = 1 if self.value > node.value else 0
        elif self.type == Types.LT:
            if not self.value:
                self.value = node.value
            else:
                self.value = 1 if self.value < node.value else 0
        elif self.type == Types.EQ:
            if not self.value:
                self.value = node.value
            else:
                self.value = 1 if self.value == node.value else 0


def part_2() -> int:
    input_data: str = ''
    with open('input.txt', 'r') as f:
        input_data = ''.join(f.readlines()).strip()

    bin_data = bin(int(input_data, 16))[2:]
    bin_data = '0' * (len(bin_data) % 4) + bin_data

    bit_idx = 0
    node_parents: List[Node] = []
    start_node: Optional[Node] = None
    while bit_idx < len(bin_data):
        last_bit_idx = bit_idx

        bin_len = 3
        packet_version = int(bin_data[bit_idx: bit_idx + bin_len], 2)
        bit_idx += bin_len
        print(f'packet version {packet_version}')
        type_id = int(bin_data[bit_idx: bit_idx + bin_len], 2)
        bit_idx += bin_len
        print(f'packet type {type_id}')

        node = Node(type_id)

        if type_id == Types.Literal:
            # literal value
            literal_digits: List[str] = []
            continue_literal = True
            while continue_literal:
                bin_len = 1
                continue_literal = bin_data[bit_idx] == str(1)
                bit_idx += bin_len
                bin_len = 4
                literal_digits.extend(bin_data[bit_idx: bit_idx + bin_len])
                bit_idx += bin_len
            literal = int(''.join(literal_digits), 2)
            print(f'found literal {literal}')
            node.value = literal
        else:
            # operator value
            bin_len = 1
            length_type = int(bin_data[bit_idx], 2)
            bit_idx += bin_len
            if length_type == 0:
                bin_len = 15
                subpacket_bits_bin = bin_data[bit_idx: bit_idx + bin_len]
                subpacket_bits = int(subpacket_bits_bin, 2)
                bit_idx += bin_len
                print(f'subpacket bits: {subpacket_bits}')
                node.subpacket_bits = subpacket_bits
            else:
                bin_len = 11
                num_subpackets_bin = bin_data[bit_idx: bit_idx + bin_len]
                num_subpackets = int(num_subpackets_bin, 2)
                bit_idx += bin_len
                print(f'num subpackets: {num_subpackets}')
                node.num_subpackets = num_subpackets

        if not node_parents:
            start_node = node

        node_parents.append(node)

        has_removed = True
        while has_removed:
            has_removed = False
            node = node_parents[-1]

            delta_bits = bit_idx - last_bit_idx
            node.curr_subpacket_bits += delta_bits
            node.curr_num_subpackets += 1

            if (node.type == Types.Literal) or \
                (node.subpacket_bits is not None and
                 node.subpacket_bits == node.curr_subpacket_bits) \
                or (node.num_subpackets is not None and
                    node.num_subpackets == node.curr_num_subpackets):

                has_removed = True
                node_parents.pop()
                if len(node_parents) == 0:
                    break
                new_parent_node = node_parents[-1]
                if new_parent_node.subpacket_bits is not None:
                    new_parent_node.curr_subpacket_bits += node.curr_subpacket_bits
                if new_parent_node.num_subpackets is not None:
                    new_parent_node.curr_num_subpackets += node.curr_num_subpackets

        if len(node_parents) == 0:
            break
        node_parents[-1].children.append(node)

    if not start_node:
        return 0

    node_stack: List[Node] = [start_node]
    while node_stack:
        node = node_stack[-1]
        if node.type == Types.Literal or len(node.children) == 0:
            if len(node_stack) > 1:
                parent_node = node_stack[-2]
                parent_node.operate(node)
                parent_node.children.remove(node)
        node_stack.pop()

    return start_node.value


if __name__ == '__main__':
    # print(part_1())
    print(part_2())
