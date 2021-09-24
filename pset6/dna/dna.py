from csv import DictReader
import sys


def main():
    # if argv len is not 3 then print error message
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1
    dbfn = sys.argv[1]  # database file name
    sqfn = sys.argv[2]  # dna sequence file name

    with open(dbfn, "r") as dbfile, open(sqfn, "r") as sqfile:
        # Gets dna sequence
        sq = sqfile.readline()
        # Gets list of STRs to look for
        list_STR = dbfile.readline().rstrip().split(',')
        list_STR.remove('name')
        # Set up dict reader for the csv dbfile
        dbfile.seek(0)
        r = DictReader(dbfile)

        # get repeats from dna sequence
        str_dict = {}
        for dna_str in list_STR:
            str_dict[dna_str] = strRepeatCount(sq, dna_str)

        # Search for matches
        for row in r:
            matches = 0
            for dna, num in str_dict.items():
                if row[dna] == str(num):
                    matches += 1
            if matches == len(row) - 1:  # -1 for 'name' key in row
                print(row['name'])
                return 0
        print("No match")


# Function to get largest count of repeats of a given string found within another given str
def strRepeatCount(dnaSq, STR):
    largest, count, i = 0, 0, 0
    # Search groups of letters the size of str, char by char
    while i < len(dnaSq) - len(STR):
        lookAt = dnaSq[i:len(STR)+i]
        if lookAt == STR:
            count += 1
            i += len(STR) - 1  # -1 because i always adds 1 to itself at the end of each loop
        elif count > 0:
            largest = max(count, largest)
            count = 0
        i += 1
    return largest


if __name__ == "__main__":
    main()
