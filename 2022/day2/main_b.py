
def main():
    with open('input_ab.txt', 'r') as input:
        lines = input.readlines()
        lines = map(str.strip, lines)

        translation = {
            'A': 'R', 'B': 'P', 'C': 'S',
            'X': 'L', 'Y': 'D', 'Z': 'W'
        }

        shape_return = {
            'R': 1,
            'P': 2,
            'S': 3
        }

        result_return = {
            'L': 0,
            'D': 3,
            'W': 6,
        }

        rules_inverse = {
            'L': {'R': 'S', 'P': 'R', 'S': 'P'},
            'D': {'R': 'R', 'P': 'P', 'S': 'S'},
            'W': {'R': 'P', 'P': 'S', 'S': 'R'},
        }

        def split(x: str):
            p0, p1 = x.split(sep=' ')
            return translation[p0], translation[p1]

        strategy_guide = map(split, lines)

        def calculate_return(p01: tuple[str, str]) -> int:
            p0, p1 = p01
            return result_return[p1] + shape_return[rules_inverse[p1][p0]]

        sum_returns = map(calculate_return, strategy_guide)

        print(sum(sum_returns))


if __name__ == '__main__':
    main()
