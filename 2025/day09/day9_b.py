import intervaltree

xtree = intervaltree.IntervalTree()
ytree = intervaltree.IntervalTree()

def area(a, b):
    return (abs(a[0] - b[0]) + 1) * (abs(a[1] - b[1]) + 1)

def make_interval(a, b):
    if (a[0] == b[0]):
        if (a[1] < b[1]):
            ytree.addi(a[1], b[1], a[0])
        else:
            ytree.addi(b[1], a[1], a[0])
    elif a[1] == b[1]:
        if (a[0] < b[0]):
            xtree.addi(a[0], b[0], a[1])
        else:
            xtree.addi(b[0], a[0], a[1])
    else:
        print(f"ERROR {a} {b}")

def intersecting_edges(a, b):
    x1, y1 = a
    x2, y2 = b
    x_min, x_max = min(x1, x2), max(x1, x2)
    y_min, y_max = min(y1, y2), max(y1, y2)

    for iv in xtree.overlap(x_min, x_max):
        if y_min < iv.data < y_max:
            return True

    for iv in ytree.overlap(y_min, y_max):
        if x_min < iv.data < x_max:
            return True

    return False

def ray_casting(a, b):
    mid = [(a[0] + b[0]) // 2, (a[1] + b[1]) // 2]
    h_edges = xtree.at(mid[0])

    above = 0
    for e in h_edges:
        if e.data > mid[1]:
            above += 1
    
    left = 0
    v_edges = ytree.at(mid[1])
    for e in v_edges:
        if e.data < mid[0]:
            left += 1
    
    return above % 2 != 0 or left % 2 != 0

with open("./input", "r") as INFILE:
    data = INFILE.readlines()
    points = []
    for line in data:
        points.append(tuple(map(int, line.split(','))))

    for i in range(0, len(points) - 1):
        make_interval(points[i], points[i+1])

    max_area = 0
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            if not intersecting_edges(points[i], points[j]) and ray_casting(points[i], points[j]):
                # print(f"{points[i]} and {points[j]} in polygon: {area(points[i], points[j])}")
                max_area = max(max_area, area(points[i], points[j]))
            # else:
            #     print(f"{points[i]} and {points[j]} NOT in polygon")

    print(max_area)
