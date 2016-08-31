f = open('inp.csv','r')
p=sorted(map(int,raw_input().strip(',').split(',')))
count = 0
for i in f.readlines():
    j = sorted(map(int,i.strip('\n').strip(',').split(',')))
    k=len(p)
    l=len(j)
    m=0
    n=0
    while n<l and m<k:
        while n<l and j[n]<p[m]:
            n+=1
        if n<l and j[n]==p[m]:
            n+=1
            m+=1
        else:
            break
    if m==k:
        count += 1
print count
