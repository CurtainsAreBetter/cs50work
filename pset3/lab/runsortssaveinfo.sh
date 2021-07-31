#!/bin/bash



# updates
echo "Running..."
echo "{" > holdinfo.json
for name in 'sorted' 'random' 'reversed'
do
    echo "$name"
    printf "\t\"%s\":\n\t{\n" $name >> holdinfo.json
    for FCOUNT in 5000 10000 50000
    do
        echo "$FCOUNT"
        printf "\t\t\"%i\":\n\t\t{\n" $FCOUNT >> holdinfo.json
        for v in 1 2 3
        do
            printf "\t\t\t\"sort%i\": \n\t\t\t[\n" $v >> holdinfo.json
            for i in {1..5}
            do
                printf "*"
                timing=$({ time ~/pset3/lab3/sort$v "$name$FCOUNT.txt"; } 2>&1 | grep real)
                timingb=$(echo "$timing" | cut -f 2 -d 'm' | cut -f 1 -d 's')
                if [ "$i" -eq 5 ]
                then
                    printf "\t\t\t\t%s\n" $timingb >> holdinfo.json
                else
                    printf "\t\t\t\t%s,\n" $timingb >> holdinfo.json
                fi
            done
            printf "\n"
            if [ "$v" -eq 3 ]
            then
                printf "\t\t\t]\n" >> holdinfo.json
            else
                printf "\t\t\t],\n" >> holdinfo.json
            fi
        done
        if [ "$FCOUNT" -eq 50000 ]
        then
            printf "\t\t}\n" >> holdinfo.json
        else
            printf "\t\t},\n" >> holdinfo.json
        fi
    done
    if [ "$name" = 'reversed' ]
    then
        printf "\t}\n" >> holdinfo.json
    else
        printf "\t},\n" >> holdinfo.json
    fi
done
echo "}" >> holdinfo.json
exit
