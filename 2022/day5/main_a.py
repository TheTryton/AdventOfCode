
def main():
    with open('input_ab.txt', 'r') as input:
        '''
                        [Q] [B]         [H]        
                    [F] [W] [D] [Q]     [S]        
                    [D] [C] [N] [S] [G] [F]        
                    [R] [D] [L] [C] [N] [Q]     [R]
                [V] [W] [L] [M] [P] [S] [M]     [M]
                [J] [B] [F] [P] [B] [B] [P] [F] [F]
                [B] [V] [G] [J] [N] [D] [B] [L] [V]
                [D] [P] [R] [W] [H] [R] [Z] [W] [S]
                 1   2   3   4   5   6   7   8   9
        '''
        stacks = [
            ['D', 'B', 'J', 'V'],
            ['P', 'V', 'B', 'W', 'R', 'D', 'F'],
            ['R', 'G', 'F', 'L', 'D', 'C', 'W', 'Q'],
            ['W', 'J', 'P', 'M', 'L', 'N', 'D', 'B'],
            ['H', 'N', 'B', 'P', 'C', 'S', 'Q'],
            ['R', 'D', 'B', 'S', 'N', 'G'],
            ['Z', 'B', 'P', 'M', 'Q', 'F', 'S', 'H'],
            ['W', 'L', 'F'],
            ['S', 'V', 'F', 'M', 'R'],
        ]

        lines = input.readlines()
        lines = map(str.strip, lines)

        def split(a: str):
            _, cnt, _, f, _, t = a.split(' ')
            return (int(cnt), int(f) - 1, int(t) - 1)

        def execute(op: tuple[int, int, int]):
            cnt, f, t = op
            cnt = min(len(stacks[f]), cnt)
            stacks[t] += list(reversed(stacks[f][-cnt:]))
            stacks[f] = stacks[f][:-cnt]

        moves = map(split, lines)

        for move in moves:
            execute(move)

        print(''.join(map(lambda x: x[-1], stacks)))


if __name__ == '__main__':
    main()
