#----------------------------#
#Wanted pattern(for m = 5):
#     1       1 
#     21     12 
#     321   123 
#     4321 1234 
#     321   123 
#     21     12 
#     1       1 
#----------------------------#


m = 5
trig_list = []
for i in range(1, m):
    sub_trig_list = []
    remain = (m - i) * 2 - 1

    while i > 0:
        sub_trig_list.append(i)
        i = i - 1

    while remain > 0:
        sub_trig_list.append(0)
        remain = remain - 1

    trig_list.append(sub_trig_list)

for sub in trig_list:
    for j in sub:
        if j != 0:
            print(j, end='')
        else:
            print(" ", end='')
    for j in reversed(sub):
        if j != 0:
            print(j, end='')

    print(" ")

for sub in reversed(trig_list):
    if len(sub) != m:
        for j in sub:
            if j != 0:
                print(j, end='')
            else:
                print(" ", end='')
        for j in reversed(sub):
            if j != 0:
                print(j, end='')

        print(" ")

