def main():
    height = get_height()
    mario(height)


def mario(height):
    for i in range(height):
        for j in range(i + height + 3):
            if j < height - 1 - i:
                print(" ", end="")
            elif j == height or j == height + 1:
                print(" ", end="")
            else:
                print("#", end="")
        print()


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n <= 8 and n >= 1:
                break
            else:
                print("That's not between 1 and 8!")
        except ValueError:
            print("That's not an integer!")
    return n


main()