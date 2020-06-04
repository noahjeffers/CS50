import cs50
import csv
import sys


if len(sys.argv) == 2:
    #open("students.db", "w").close()
    db = cs50.SQL("sqlite:///students.db")
    # Copy the command line input into a variable
    data = sys.argv[1]
    with open(data, "r") as characters:

        # Copies the information from the CSV into a Dictionary
        reader = csv.DictReader(characters)
        # Loops through each line of the CSV
        for row in reader:

            name = row['name']
            # Substrings the name because the full name is stored in a single string
            fIndex = name.index(" ")
            fname = name[0:fIndex]
            lIndex = name.rindex(" ") + 1
            lname = name[lIndex:len(name)]
            # Checks if the first name + the last name is the same as the total length to determine if there is a middle name
            if len(fname) + len(lname) + 1 != len(name):
                mname = name[fIndex+1:lIndex-1]
            else:
                mname = None
            # Enters the other values into variables and executes an INSERT
            house = row['house']
            birth = row['birth']
            db.execute("INSERT INTO students(first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       fname, mname, lname, house, birth)
            #print(fname, mname, lname,",", house,",",birth)

else:
    print("Usage: python import.py data.csv")