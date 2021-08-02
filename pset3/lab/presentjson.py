import json

# intake
f = open("holdinfo.json", "r")
r = f.read()
f.close()
fulljson = json.loads(r)
inf = []

for key in fulljson:
    for n in fulljson[key]:
        for sortn in fulljson[key][n]:
            laz = fulljson[key][n][sortn]
            tot = round(sum(laz)/5, 3)
            fulljson[key][n][sortn] = tot
            inf.append((sortn, tot))




newl=[]
c = 0
templist = []
for tup in inf:
    templist.append(tup)
    if len(templist) == 3:
        templist.sort(key=lambda x: x[1])
        newl.append(templist.copy())
        templist.clear()

topline = "Sorted" + (" "*15) + "|  Random" + (" "*2) + (" "*13) + "|  Reversed"
line5000 ="--5,000-- " + (" "*11) + (("|  --5,000-- " + (" "*11))*2)
line10000 ="--10,000-- " + (" "*10) + (("|  --10,000-- " + (" "*12))*2)
line50000 ="--50,000-- " + (" "*10) + (("|  --50,000-- " + (" "*12))*2)
lineshere = [line5000, line10000, line50000]
print(topline)
for i in range(3):
    print(lineshere[i])
    first = "1st: " + newl[i][0][0] + "  " + str(newl[i][0][1]).ljust(6,'0') + "s  |  " + "1st: " + str(newl[i+3][0][0]) + "  " + str(newl[i+3][0][1]).ljust(6,'0') + "s  |  " + "1st: " + str(newl[i+6][0][0]) + "  " + str(newl[i+6][0][1]).ljust(6,'0') + "s"
    second = "2nd: " + newl[i][1][0] + "  " + str(newl[i][1][1]).ljust(6,'0') + "s  |  " + "2nd: " + str(newl[i+3][1][0]) + "  " + str(newl[i+3][1][1]).ljust(6,'0') + "s  |  " + "2nd: " + str(newl[i+6][1][0]) + "  " + str(newl[i+6][1][1]).ljust(6,'0') + "s"
    third = "3rd: " + newl[i][2][0] + "  " + str(newl[i][2][1]).ljust(6,'0') + "s  |  " + "3rd: " + str(newl[i+3][2][0]) + "  " + str(newl[i+3][2][1]).ljust(6,'0') + "s  |  " + "3rd: " + str(newl[i+6][2][0]) + "  " + str(newl[i+6][2][1]).ljust(6,'0') + "s"
    print(first)
    print(second)
    print(third)



"""
Prints:

Sorted               |  Random               |  Reversed
--5,000--            |  --5,000--            |  --5,000--            
1st: sort1  0.0010s  |  1st: sort2  0.0150s  |  1st: sort2  0.0020s
2nd: sort2  0.0020s  |  2nd: sort3  0.0600s  |  2nd: sort3  0.0500s
3rd: sort3  0.0610s  |  3rd: sort1  0.1070s  |  3rd: sort1  0.1090s
--5,000--            |  --5,000--            |  --5,000--            
1st: sort1  0.0020s  |  1st: sort2  0.0040s  |  1st: sort2  0.0040s
2nd: sort2  0.0030s  |  2nd: sort3  0.2260s  |  2nd: sort3  0.2200s
3rd: sort3  0.2080s  |  3rd: sort1  0.4990s  |  3rd: sort1  0.4350s
--5,000--            |  --5,000--            |  --5,000--            
1st: sort1  0.0190s  |  1st: sort2  0.0390s  |  1st: sort2  0.0400s
2nd: sort2  0.0370s  |  2nd: sort3  5.0620s  |  2nd: sort3  5.1790s
3rd: sort3  5.1570s  |  3rd: sort1  13.516s  |  3rd: sort1  9.9380s


"""
