l=[]
for _ in range(input()):
    l.append(sorted(map(int,raw_input().strip(',').split(','))))
l.sort()
for i in l:
    print i
