from cs50 import get_string
import re

text = get_string("Text: ")
space = " "
# counts the number of letters in the provided text
l = 0

# counts the number of words in the provided text.
w = 1

# counts the number of sentences in the provided text
s = 0

# Loops through the text checking each index
for c in text:
    # if the current index is a space it adds one to the words count
    if c == " ":
        w += 1
    # if the current index is a punctuation mark it adds one to the sentence count
    elif c == "." or c == "?" or c == "!":
        s += 1
    # if the current index is a letter it adds one to the letters count
    elif re.search("\w", c, re.IGNORECASE):
        l += 1
# determines the averages as required in the specifications
L = 100 * (l / w)
S = 100 * (s / w)
# formula provided in specification to determine Coleman-Liau formula
output = (0.0588 * L) - (0.296 * S) - 15.8


if output >= 1 and output <= 16:
    print(f"Grade {round(output)}")
elif output > 16:
    print("Grade 16+")
else:
    print("Before Grade 1")