def area(a, b):
    return (abs(a[0] - b[0]) + 1) * (abs(a[1] - b[1]) + 1)

with open("./input", "r") as INFILE:
    data = INFILE.readlines()
    points = []
    for line in data:
        points.append(tuple(map(int, line.split(','))))

    max_area = 0
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            max_area = max(max_area, area(points[i], points[j]))

    print(f"{max_area}")
