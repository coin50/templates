alph = [0]*256
for c in s: alph[ord(c)] += 1
f = 1
for i in range(256):
        if alph[i]:
                alph[i] = f
                f += 1
rnk = [0]*n
for i in range(n): rnk[i] = alph[ord(s[i])]

def count_sort(inds,a):
        f = [0]*(n+2)
        for i in range(n): f[a[i]+1] += 1
        for i in range(n+1): f[i+1] += f[i]

        out = [0]*n
        for i in inds:
                out[f[a[i]]] = i
                f[a[i]] += 1
        return out

j = 1
while j < n:
        x = rnk
        y = rnk[j:] + [0]*j
        inds = list(range(n))
        inds = count_sort(inds,y)
        inds = count_sort(inds,x)
        f = 0
        l = 0
        for i in inds:
                t = (x[i],y[i])
                if t != l: f += 1
                l = t
                rnk[i] = f
        j *= 2

inv = [0]*n
for i in range(n): inv[rnk[i]-1] = i

lcp = [0]*(n-1)
h = 0
for i in range(n):
        a = rnk[i] - 1
        if a == n-1: h = 0; continue
        j = inv[a+1]
        while i+h < n and j+h < n and s[i+h] == s[j+h]: h += 1
        lcp[a] = h
        h = max(0,h-1)
