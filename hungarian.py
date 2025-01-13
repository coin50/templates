def hungarian(g):
    BIG = 1<<55
    n = len(g)
    pot = [-BIG]*(2*n)
    match = [-1]*(2*n)
 
    for _ in range(n):
        s = match.index(-1)
        par = [-1]*n
        v = [1]*n
 
        min_slack = [(g[s][i]-pot[s]-pot[i+n], s) for i in range(n)]
        while True:
            cap, L, R = BIG,-1,-1
            for i,(x,y) in enumerate(min_slack): 
                if not v[i]: continue
                if x < cap: cap,L,R = x,y,i
 
            pot[s] += cap
            for i in range(n):
                if not v[i]:    pot[i+n] -= cap
                if par[i] > -1: pot[i] += cap
            
            if match[R+n] == -1: 
                while L > -1:
                    match[R+n] = L
                    R, match[L] = match[L], R
                    L = par[L]
                break
            
            M = match[R+n]
            par[M] = L
            v[R] = 0
            for i,(x,y) in enumerate(min_slack):
                if not v[i]: continue
                slack = g[M][i]-pot[M]-pot[i+n]
                min_slack[i] = (slack,M) if slack < x-cap else (x-cap,y)
    return sum(pot), match[:n]

"""
n = int(input())
g = [[int(t) for t in input().split()] for _ in range(n)]
cost,match = hungarian(g)
print(cost)
for i in range(n):
    print(i+1,match[i]+1)
"""