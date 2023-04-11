from math import comb

done = set()

count = 0
x = []
y = []
z = []

print(comb(0,33))


# for i in range(1, 67):
#     for j in range(1, 34):
#         # choose = str(i) + " choose " + str(j)
#         # inverse = str(j) + " choose " + str(i)
#         # if choose in done:
#         #     continue
#         # if inverse in done:
#         #     continue

#         a = i
#         b = j
#         if b > a:
#             a, b = b, a

#         x.append(i)
#         y.append(j)
#         c = comb(a, b)
#         z.append(c)
#         # done.add(choose)
#         # done.add(inverse)
#         count += 1

