def digits(number: int) -> int:
    return len(str(abs(number)))

def repeat_check(num: int, digit: int) -> bool:
    no_digits = digits(num)
    parts = []
    if no_digits % digit == 0:
        fac = 10 ** (no_digits // digit)
        while num > 0:
            parts.append(num % fac)
            num = num // fac
        for i, part in enumerate(parts[:-1]):
            if part != parts[i+1]:
                return False
        return True
    else:
        return False

with open("./input", "r") as INPUT:
    data = INPUT.read().strip().split(",")
    ranges = []
    sum = 0
    for i in data:
        ranges.append(i.split("-"))
    for thing in ranges:
        begin = int(thing[0])
        end = int(thing[1])

        while begin <= end:
            for i in range(2, digits(begin) + 1):
                if repeat_check(begin, i):
                    sum += begin
                    break
            begin = begin + 1

    print(sum)
