import csv
import sys
from sys import argv


def main():

    # three args needed: name of .py file, name of .csv, name of .txt
    if len(argv) != 3:
        print("Program requires a .csv of DNA strings and a .txt of a string to match.")
        return
    # define rows to be our array of dicts
    rows = []
    with open(argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:  # for every row, add it to rows[]
            rows.append(row)

    # read the .txt into a string
    with open(argv[2]) as input:
        match = input.read()
    # define the STRS that we match against
    strs = list(rows[0])
    strs[0:1] = []
    # define an empty counts list
    counts = []
    # iterate over the input string and find the longest runs of every STR
    for i in range(len(strs)):
        counts.append(longest_match(match, strs[i]))
    # define checking variable
    foundsame = 0
    # iterate over all the rows in the .csv
    for i in range(len(rows)):
        # set currententry as a dict of the indexed row
        currententry = dict(rows[i])
        # set currentvalues to the values (counts of each STR) for the current entry
        currentvalues = list(currententry.values())
        # define another checking variable
        issame = 0
        # iterate over all the values and increment issame if they
        # match the counts from the input string
        for j in range(len(strs)):
            if int(currentvalues[j+1]) == int(counts[j]):
                issame += 1
        # if the issame list is the same length as the counts, that means that the
        # current entry has the same counts as the input string
        if issame == len(counts):
            print(currentvalues[0])
            foundsame += 1
    # if there's no match found, print such
    if foundsame == 0:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
