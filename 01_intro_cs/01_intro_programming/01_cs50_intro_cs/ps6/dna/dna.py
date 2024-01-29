import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py <FILE.CSV> <FILE.TXT>")
        sys.exit(1)

    # TODO: Read database file into a variable
    csv_file_data = []
    with open(sys.argv[1]) as csv_file:
        csv_file_reader = csv.DictReader(csv_file)
        for row in csv_file_reader:
            csv_file_data.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as txt_file:
        for index, line in enumerate(txt_file):
            if index == 0:
                txt_file_data = line.strip()

    # TODO: Find longest match of each STR in DNA sequence
    str_list = list(csv_file_data[0].keys())[1:]
    count_dict = {}
    for str_element in str_list:
        count_dict[str_element] = longest_match(txt_file_data, str_element)

    # TODO: Check database for matching profiles
    for profile in csv_file_data:
        count_equal = 0
        for index, str_element in enumerate(str_list):
            if int(profile[str_element]) == count_dict[str_element]:
                count_equal += 1

        if count_equal == len(str_list):
            print(profile["name"])
            sys.exit(0)

    print("No match")
    sys.exit(1)


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


if __name__ == "__main__":
    main()
