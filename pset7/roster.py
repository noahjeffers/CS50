import cs50
import csv
import sys

if len(sys.argv) == 2:
    # Puts the command line input into a variable
    house = sys.argv[1]
    db = cs50.SQL("sqlite:///students.db")
    # Executes a SELECT using the input to refine the search
    students = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC;", house)

    # Loops through the results and formats them
    for student in students:
        # Formats the last name so that it appears as specified
        last = student['last'] + ", born"
        if student['middle'] == None:
            # If there is no middle name 
            print(student['first'], last, student['birth'])
        else:
            print(student['first'], student['middle'], last, student['birth'])

else:
    print("Usage: python import.py string")