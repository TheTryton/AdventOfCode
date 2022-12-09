
def main():
    with open('input_ab.txt', 'r') as input:
        lines = input.readlines()
        max_calories = 0
        current_calories = 0
        for line in lines:
            line = line.strip()
            if len(line) == 0:
                max_calories = max(current_calories, max_calories)
                current_calories = 0
            else:
                current_calories += int(line)

        max_calories = max(current_calories, max_calories)

        print(max_calories)


if __name__ == '__main__':
    main()
