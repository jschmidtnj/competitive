#!/usr/bin/env python3

from typing import List, Optional, Set
from collections import Counter


def part_1() -> int:
    draws: List[int] = []
    boards: List[List[List[int]]] = []
    with open('input.txt', 'r') as f:
        draws.extend(int(i) for i in f.readline().split(','))
        board: List[List[int]] = []
        for line in f:
            line = line.strip()
            if not line:
                if board:
                    boards.append(board)
                    board = []
                continue
            board.append([int(i) for i in line.split()])

    if not draws or not boards:
        return -1

    winner: Optional[List[List[int]]] = None
    last_draw = -1

    for draw in draws:
        for board in boards:
            for row in board:
                for c, elem in enumerate(row):
                    if elem == draw:
                        row[c] = -1

            count_row = Counter()
            count_col = Counter()
            for r, row in enumerate(board):
                for c, elem in enumerate(row):
                    if elem == -1:
                        count_row[r] += 1
                        count_col[c] += 1
            row_count = count_row.most_common()
            col_count = count_col.most_common()

            if (len(row_count) > 0 and row_count[0][1] == len(board)) or \
                    (len(col_count) > 0 and col_count[0][1] == len(board[0])):
                winner = board
                last_draw = draw
                break

        if winner is not None:
            break

    if winner is None:
        return -1

    res = last_draw * \
        sum([0 if elem == -1 else elem for row in winner for elem in row])

    return res

def part_2() -> int:
    draws: List[int] = []
    boards: List[List[List[int]]] = []
    with open('input.txt', 'r') as f:
        draws.extend(int(i) for i in f.readline().split(','))
        board: List[List[int]] = []
        for line in f:
            line = line.strip()
            if not line:
                if board:
                    boards.append(board)
                    board = []
                continue
            board.append([int(i) for i in line.split()])

    if not draws or not boards:
        return -1

    last_winner: Optional[List[List[int]]] = None
    last_draw = -1

    winning_boards: Set[int] = set()

    for draw in draws:
        for i, board in enumerate(boards):
            for row in board:
                for c, elem in enumerate(row):
                    if elem == draw:
                        row[c] = -1

            count_row = Counter()
            count_col = Counter()
            for r, row in enumerate(board):
                for c, elem in enumerate(row):
                    if elem == -1:
                        count_row[r] += 1
                        count_col[c] += 1
            row_count = count_row.most_common()
            col_count = count_col.most_common()

            if (len(row_count) > 0 and row_count[0][1] == len(board)) or \
                    (len(col_count) > 0 and col_count[0][1] == len(board[0])):
                last_winner = board
                last_draw = draw
                winning_boards.add(i)
                if len(winning_boards) == len(boards):
                    break

        if len(winning_boards) == len(boards):
            break

    if last_winner is None or len(winning_boards) != len(boards):
        return -1

    res = last_draw * \
        sum([0 if elem == -1 else elem for row in last_winner for elem in row])

    return res


if __name__ == '__main__':
    print(part_1())
    print(part_2())
