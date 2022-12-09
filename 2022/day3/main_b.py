
def main():
    with open('input_ab.txt', 'r') as input:
        lines = input.readlines()
        lines = map(str.strip, lines)

        groups = zip(*(iter(lines),) * 3)

        groups = map(lambda x: (''.join(sorted(x[0])), ''.join(sorted(x[1])), ''.join(sorted(x[2]))), groups)

        def to_ord(x: str):
            a = ord('a')
            A = ord('A')
            x_ord = ord(x)
            if x_ord > a:
                return x_ord - a + 1
            else:
                return x_ord - A + 27

        def find_common_item(a: str, b: str, c: str):
            i = [0, 0, 0]
            s = [a, b, c]
            while all(map(lambda v: v[0] < len(v[1]), zip(i, s))):
                ords = list(map(lambda v: ord(v[1][v[0]]), zip(i, s)))
                low_index = min(enumerate(ords), key=lambda x: x[1])[0]
                if all(map(lambda v: v == ords[low_index], ords)):
                    ch = chr(ords[low_index])
                    return ch
                else:
                    i[low_index] += 1

            return None

        common_items = map(lambda a: find_common_item(a[0], a[1], a[2]), groups)

        print(sum(map(to_ord, common_items)))


if __name__ == '__main__':
    main()
