import z3

with open("./input", "r") as INFILE:
    lines = INFILE.readlines()
    max_lights = 0
    max_buttons = 0
    answer = 0
    for line in lines:
        chunks = line.strip().split()

        light_diagram = []
        for ch in chunks[0]:
            if ch == '.':
                light_diagram.append(False)
            elif ch == '#':
                light_diagram.append(True)
        chunks = chunks[1:]

        max_lights = max(max_lights, len(light_diagram))

        joltage_requirements = list(map(int, chunks[-1][1:-1].split(',')))
        chunks = chunks[:-1]

        # print(f"{joltage_requirements=}")

        buttons = []
        for chunk in chunks:
            buttons.append(set(map(int, chunk[1:-1].split(','))))

        # buttons 
        butts = [ z3.Bool(f"b_{j}") for j in range(len(buttons)) ]
        press = [ z3.Int(f"p_{j}") for j in range(len(buttons))]

        s = z3.Optimize()

        for i, light in enumerate(light_diagram):
            req_buttons = []
            for j, button in enumerate(buttons):
                if i in button:
                    req_buttons.append(j)

            e = butts[req_buttons[0]]
            for r in req_buttons[1:]:
                e ^= butts[r]

            e = (e == light)
            e = z3.simplify(e)
            s.add(e)

        for i in range(len(light_diagram)):
            e = 0
            for idx, button in enumerate(buttons):
                s.add(press[idx] >= 0)
                if i in button:
                    e += press[idx]
            e = (e == joltage_requirements[i])
            e = z3.simplify(e)
            s.add(e)

        total_press = z3.Sum(press)
        s.minimize(total_press)

        if s.check():
            m = s.model()
            tot = m.evaluate(total_press)
            answer += tot.as_long()
        else:
            print(f"[-] ERROR no solution found")

    print(answer)
