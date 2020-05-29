import csv
import sys


# Checks to see how many times a substring occurs within the provided sequence
def numberOfOccurences(s, sub):
    ans = [0] * len(s)

    for i in range(len(s)-len(sub), -1, -1):
        if s[i: i + len(sub)] == sub:
            if i + len(sub) > len(s) - 1:
                ans[i] = 1
            else:
                ans[i] = 1 + ans[i + len(sub)]
    # returns the largest number in the ans[] list
    return max(ans)


# Prints the person that matches the results gathered in supplied array(actual)
def print_match(reader, actual):
    for line in reader:
        person = line[0]
        values = []
        # Creates an array of the values listed alongside a Person in the CSV
        for val in line[1:]:
            values.append(int(val))
        # If the values match the results supplied in actual then the name is printed out
        if values == actual:
            print(person)
            return
    print("No Match")


# Main method to compare a DNA sequence to a specific person
# Matches the number of times a sequence repeats
def main():
    if len(sys.argv) == 3:
        dbPath = sys.argv[1]
        seqPath = sys.argv[2]
        
        # Opens the database stored in the CSV
        with open(dbPath) as db_File:
            reader = csv.reader(db_File)
            check_seq = next(reader)[1:]

            # Copys the sequence from the supplied file path into a variable
            with open(seqPath) as seq_File:
                seq = seq_File.read()

                # Creates a List to store the number of times a DNA sequence(check) occurs within the larger sequence(seq)
                actual = [numberOfOccurences(seq, check) for check in check_seq]
                # for check in check_seq:
                #     actual.append([numberOfOccurences(seq, check)])
                # for i in actual:
                #     print(i)
                print_match(reader, actual)

    else:
        print("Usage: python dna.py data.csv sequence.txt")


main()