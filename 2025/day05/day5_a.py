with open("./input", "r") as INPUT:
    data = list(INPUT.readlines())
    data.remove('\n')

    ans = 0

    fresh = []
    ids = []
    for line in data:
        if line.find('-') != -1:
            fresh.append(line.strip())
        else:
            ids.append(int(line.strip()))

    ranges = []
    for line in fresh:
        r = list(map(int, line.strip().split('-')))
        ranges.append(r)

    for id in ids:
        for r in ranges:
            if id >= r[0] and id <= r[1]:
                ans += 1
                break

    print(ans)
