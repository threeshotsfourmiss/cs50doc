# import get_string
from cs50 import get_string
input = get_string("Text: ")
# we find the number of words by counting the spaces and adding one,
# as there would be a single word in the input if there were no spaces,
# e.g. "bathroom" has no spaces but is a single word.
words = input.count(" ")+1
# the average number of letters per 100 words is found by taking the
# length of the string, subtractiving the number of spaces (this is
# probably better handled by counting the alphabetical characters, but
# this is simple enough and works anyways), then multiplying the
# resulting ratio by 100.
avgletter = ((len(input)-words-1)/words)*100
# the average number of sentences per 100 words is found by adding up all
# the punctuation marks that signify an end of a sentence, dividing by the
# number of words, then multiplying by 100.
avgsent = ((input.count('.')+input.count('!')+input.count('?'))/words)*100
# this is the colemann-liau index calculation
index = (0.0588*avgletter) - (0.296 * avgsent) - 15.8
# the grade is equal to the index minus 0.5 (in C this isn't neccessary,
# because round() always rounds down, but in python this isn't the case,
# so we subtract a little.)
grade = round(index-0.5)
# debug prints
# print(words)
# print(len(input))
# print(avgletter)
# print(avgsent)
# print(index-0.5)
# print(grade)
if grade < 1:
    print("Before Grade 1")
elif grade > 15:
    print("Grade 16+")
else:
    # it's important to convert the grade into a string, otherwise we get
    # an error about types when the program is run.
    print("Grade " + str(grade))
