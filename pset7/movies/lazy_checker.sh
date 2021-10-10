#!/bin/bash
# Use this script to check if your sql queries result in the correct line count
# If you have a file named "sqltesthere.txt" I would change its name or change
# the file name found on line 16

# User arg should be the max file to go up to. If left blank will default to 13
if [ "$#" -ne 1 ]
then
    maxn=13
else
    maxn="$1"
fi
# array with line count goals in order of file number
goals=(9545 1 50863 1 10 1 6864 4 18237 1887 5 6 176)
# sql results file
testfilename="sqltesthere.txt"
i=1
echo "sql_file | line_count | result"
while [ "$i" -le "$maxn" ]
do
    cat "$i.sql" | sqlite3 movies.db > "$testfilename"
    # get line count
    count=$(wc -l "$testfilename" | cut -d " " -f 1 )
    # remove column title from the count
    count=$((count - 1))
    rm -f "$testfilename"
    if [[ "$count" -eq "${goals[$((i - 1))]}" ]]
    then
        res="Pass"
    else
        res="Fail"
    fi
    echo "$i.sql $count $res"
    i=$((i + 1))
done
