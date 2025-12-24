from os import strerror
import intervaltree

with open("./input", "r") as INPUT:
    data = list(INPUT.readlines())
    data.remove('\n')

    ans = 0

    fresh = []
    for line in data:
        if line.find('-') != -1:
            fresh.append(line.strip())

    ranges = []
    for line in fresh:
        r = list(map(int, line.strip().split('-')))
        if r[0] == r[1]:
            r[1] += 0.1
        ranges.append(r)

    ranges.sort()
    tree = intervaltree.IntervalTree.from_tuples(ranges)
    tree.merge_overlaps(strict=False)
    tree = list(tree)
    tree.sort()

    for interval in tree:
        ans += (interval[1] - interval[0] + 1) // 1

    print(int(ans))
