
def main():
    with open('input_ab.txt', 'r') as input:
        lines = input.readlines()
        calories = []
        current_calories = 0
        for line in lines:
            line = line.strip()
            if len(line) == 0:
                calories.append(current_calories)
                current_calories = 0
            else:
                current_calories += int(line)

        calories = list(sorted(calories))

        print(sum(calories[-3:]))


if __name__ == '__main__':
    main()
