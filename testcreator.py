from math import comb


count = 0

done = {}

maxint =18446744000000000000
print()


val = comb(66,33)

print(val)

print(val > maxint)




# for i in range(1, 18446744000000000000):
#     for j in range(1, i):
#         choose = str(i) + " choose " + str(j)
#         if choose in done:
#             continue
#         a = i
#         b = j
#         if b > a:
#             a, b = b, a

#         c = comb(a, b)
        
#         if (c > 18446744000000000000):
#             continue
        
#         print(choose, c)

#         done[choose] = c
        
#         count += 1

