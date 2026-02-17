from collections import deque

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

        # print(f"{light_diagram=}")

        joltage_requirements = list(map(int, chunks[-1][1:-1].split(',')))
        chunks = chunks[:-1]

        # print(f"{joltage_requirements=}")

        buttons = []
        for chunk in chunks:
            buttons.append(set(map(int, chunk[1:-1].split(','))))

        # print(f"{buttons=}")

        max_buttons = max(max_buttons, len(buttons))

        q = deque()
        q.append([0, [False] * len(light_diagram)])
        visited = set()
        visited.add(tuple([False] * len(light_diagram)))

        minimum_presses = len(buttons) + 1
        while len(q) != 0:
            presses, lights = q.popleft()
            if presses > len(buttons):
                break
            for button in buttons:
                candidate_presses = presses
                candidate_lights = lights.copy()
                for x in button:
                    candidate_lights[x] = not candidate_lights[x]
                candidate_presses += 1
                if candidate_lights == light_diagram:
                    if candidate_presses < minimum_presses:
                        # print(f"[{candidate_presses}] found match with {candidate_lights=}")
                        minimum_presses = candidate_presses
                        break
                state_tuple = tuple(candidate_lights)
                if state_tuple not in visited:
                    visited.add(state_tuple)
                    q.append([candidate_presses, candidate_lights])
        # print(f"{minimum_presses=}")
        answer += minimum_presses

    print(answer)

    # print(f"{max_lights=}")
    # print(f"{max_buttons=}")
