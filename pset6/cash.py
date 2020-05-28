from cs50 import get_float


# Main method for determining how much change is owed to a person
def main():
    cents = valid_input()
    # multiplies the change owed by 100 to find out how many cents are owed
    cents = cents * 100

    # Converts the float to an int to round down every time
    # Divides the cents by 25 to find out how many quarters
    # then places the remainder of cents / 25 into the variable change
    quarters = int(cents / 25)
    change = cents % 25
    # Repeats the previous two steps with each different demonination to find the vaid change
    dimes = int(change / 10)
    change = change % 10

    nickels = int(change / 5)
    change = change % 5

    pennies = change / 1
    # adds all of the different types of coins together to find out how much change is required
    totalChange = quarters + dimes + nickels + pennies
    print(int(totalChange))


# A method to return a valid input that is greater than 1 cent
def valid_input():
    while True:
        n = get_float("Change owed: ")
        if n >= .01:
            break
    return n


main()