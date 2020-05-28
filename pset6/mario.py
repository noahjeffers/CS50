from cs50 import get_int

# prints out # in a pyramid shape


def main():
    # calls the second function to get a valid input
    n = valid_input()
    output = "#  #"
    for i in range(n):
        for j in range(n-(i+1)):
            print(" ", end="")
        print(output)
        output = "#" + output + "#"


# gets a valid input between 1-8
def valid_input():
    # loops through until a number between 1-8 is entered
    while True:
        n = get_int("Height: ")
        # breaks when a proper value is entered
        if n > 0 and n < 9:
            break
    return n


main()