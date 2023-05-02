from math import comb

# 10100903263463355200
# maxint = 18446744000000000000

inp = open("3.in","w")
ans = open("3.ans","w")

for i in range(1, 18446744000000000000):
    for j in range(1, i):
        choose = str(i) + " " + str(j)
        c = comb(i, j)
        if (c > 18446744000000000000):
            continue
        
        inp.write(choose+ "\n")
        ans.write(str(c) + "\n")
