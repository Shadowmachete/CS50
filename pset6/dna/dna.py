import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py DATABASENAME SEQUENCENAME")
    # TODO: Read database file into a variable
    databaseData = []
    with open(sys.argv[1], newline="\n") as database:
        reader = csv.DictReader(database)
        for row in reader:
            databaseData.append(row)
    print(databaseData)
    # TODO: Read DNA sequence file into a variable
    sequenceData = ""
    with open(sys.argv[2]) as sequence:
        reader = csv.reader(sequence)
        for row in reader:
            sequenceData = row[0]
    print(sequenceData)
    # TODO: Find longest match of each STR in DNA sequence
    #match = longest_match(sequence, subsequence)
    # TODO: Check database for matching profiles

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
