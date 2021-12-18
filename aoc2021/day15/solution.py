#!/usr/bin/env python3

def setupdata(data):
    return data.split("\n")

def rollover(s):
    if s == "9":
        return "1"
    else:
        return str(int(s)+1)

def setupdata_2(data):
    # just like the simulations
    d = data.split("\n")
    ld = len(d)
    for _ in range(4):
    	for i in range(ld):
            d[i] += ''.join([rollover(x) for x in list(d[i][-(ld):])])
    ld = len(d)
    for _ in range(4):
        sd = d[-(ld):]
        for line in sd:
            d.append(''.join([rollover(x) for x in list(line)]))
    return d


def runner(sdata):
    connectivity = connect(sdata)
    cn = astar(connectivity, sdata)
    return cn


def astar(connectivity, sdata):
    opennode = {}
    opennode[(0,0)] = {"F": 0, "G": 0, "H": hcalc((0,0), len(sdata)), "parent": "start"}
    closednode = {}
    parsing = True
    while parsing:
        lowestopen = hlowest(opennode)
        closednode[lowestopen] = opennode[lowestopen]
        del opennode[lowestopen]
        for child in connectivity[lowestopen]:
            if child in closednode:
                continue
            h = hcalc(child, len(sdata))
            g = closednode[lowestopen]["G"] + int(sdata[child[1]][child[0]])
            f = h + g
            if child not in opennode:
                opennode[child] = {"F": g, "G":g , "H": h, "parent" : lowestopen}
            else:
                if g < opennode[child]["G"]:
                    opennode[child]["F"] = f
                    opennode[child]["G"] = g
                    opennode[child]["parent"] = lowestopen
        if (len(sdata[0]) -1, len(sdata) -1) in closednode:
            parsing = False
    return closednode[(len(sdata[0]) -1, len(sdata) -1)]


def hcalc(coord, bound):
    # heuristic
    h = 4
    # convert from lenght to last index
    bound = bound -1
    return (2 * bound - coord[0] - coord[1]) * h


def hlowest(on):
    v = "start"
    kname = ""
    for k in on:
        if v == "start":
            v = on[k]["F"]
            kname = k
        else:
            if on[k]["F"] < v:
                v = on[k]["F"]
                kname = k
    return kname


def connect(sdata) -> dict:
    # returns dict of coords connected to a given coord non-diagonally
    c = {}
    for y in range(len(sdata)):
        for x in range(len(sdata[0])):
            c[(x, y)] = []
            # right check
            if x + 1 < len(sdata[0]):
                c[(x, y)] += [(x + 1, y)]
            # left check
            if x - 1 >= 0:
                c[(x, y)] += [(x - 1, y)]
            # down check
            if y + 1 < len(sdata):
                c[(x, y)] += [(x, y + 1)]
            # up check
            if y -1 >= 0:
                c[(x, y)] += [(x, y - 1)]
    return c


if __name__ == '__main__':
    data = ''.join(open('input.txt').readlines())

    print(runner(setupdata(data)))
    print(runner(setupdata_2(data)))
