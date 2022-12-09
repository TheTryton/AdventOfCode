
def main():
    with open('input_ab.txt', 'r') as input:
        lines = input.readlines()
        lines = map(str.strip, lines)

        def split(x: str):
            a, b = x.split(',')
            a_s, a_e = a.split('-')
            b_s, b_e = b.split('-')
            return ((int(a_s), int(a_e)), (int(b_s), int(b_e)))

        def overlap(a: tuple[int, int], b: tuple[int, int]):
            if a[1] >= b[0] and b[1] >= a[0]:
                return True
            else:
                return False

        ranges = map(split, lines)
        are_contained = list(map(lambda x: overlap(x[0], x[1]), ranges))
        print(are_contained.count(True))


if __name__ == '__main__':
    main()
