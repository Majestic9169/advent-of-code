def digits(number: int) -> int:
    return len(str(abs(number)))

with open("./input", "r") as INPUT:
    data = INPUT.read().strip().split(",")
    ranges = []
    count = 0
    sum = 0
    for i in data:
        ranges.append(i.split("-"))
    for range in ranges:
        begin = int(range[0])
        end = int(range[1])

        while begin <= end:
            nodigits = digits(begin)
            if nodigits % 2 == 0:
                fac = 10 ** (nodigits // 2)
                low = begin % fac
                high = begin // fac
                if low == high:
                    count = count + 1
                    sum += begin
            begin = begin + 1

    print(sum)
