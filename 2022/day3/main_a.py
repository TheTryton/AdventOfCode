
def main():
    with open('input_ab.txt', 'r') as input:
        lines = input.readlines()
        lines = map(str.strip, lines)

        def split(x: str):
            return x[:len(x)//2], x[len(x)//2:]

        compartments = map(split, lines)

        def to_ord(x: str):
            a = ord('a')
            A = ord('A')
            x_ord = ord(x)
            if x_ord > a:
                return x_ord - a + 1
            else:
                return x_ord - A + 27

        compartments = map(lambda a: (''.join(sorted(a[0])), ''.join(sorted(a[1]))), compartments)

        def find_common_item(a: str, b: str):
            i0 = 0
            i1 = 0
            while i0 < len(a) and i1 < len(b):
                if ord(a[i0]) < ord(b[i1]):
                    i0 += 1
                elif ord(a[i0]) > ord(b[i1]):
                    i1 += 1
                else:
                    return a[i0]
            return None

        common_items = map(lambda a: find_common_item(a[0], a[1]), compartments)

        print(sum(map(to_ord, common_items)))


if __name__ == '__main__':
    main()
