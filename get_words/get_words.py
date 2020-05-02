#!/usr/bin/python3
import argparse

parser = argparse.ArgumentParser(description='Get words from dictionary with same letters.')
parser.add_argument('-d', dest='dictionary', default=None,
                    help='dictionary file path', nargs=1, type=str)
parser.add_argument('-r', dest='repeating', default=True,
                    help='allow repeating letters', nargs=1, type=bool)
parser.add_argument('-l', dest='letters', default=None,
                    help='allowed letters', nargs=1, type=str)

def main():
    args = parser.parse_args()
    if args.dictionary is None or args.letters is None:
        parser.print_help()
        return
    letters = args.letters[0].strip().lower()
    letter_map = {}
    for letter in letters:
        if letter not in letter_map:
            letter_map[letter] = 1
        else:
            letter_map[letter] += 1
    res = []
    with open(args.dictionary[0]) as file:
        for line in file:
            word = line.strip().lower()
            can_add = True
            letters_used = {}
            for letter in word:
                if letter not in letter_map:
                    can_add = False
                    break
                else:
                    if letter not in letters_used:
                        letters_used[letter] = 1
                    elif not args.repeating and letters_used[letter] == letter_map[letter]:
                        can_add = False
                        break
                    else:
                        letters_used[letter] += 1
            if not can_add:
                continue
            for letter in letters:
                if letter not in letters_used:
                    can_add = False
                    break
            if can_add:
                res.append(word)
    print(res)

if __name__ == '__main__':
    main()