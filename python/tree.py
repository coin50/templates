edges = [[] for _ in range(n)]
for _ in range(n-1):
	a,b = [int(t)-1 for t in input().split()]
	edges[a].append(b)
	edges[b].append(a)

par = [0]*n
queue = [0]
for a in queue:
	for b in edges[a]:
		edges[b].remove(a)
		par[b] = a
		queue.append(b)

subt = [1]*n
for a in reversed(queue): subt[par[a]] += (a > 0) * subt[a]

enter = [0]*n
exit = [0]*n
for a in queue:
	exit[a] = enter[a] + subt[a]
	c = enter[a] + 1
	for b in edges[a]:
		enter[b] = c
		c += subt[b]

depth = [0]*n
for a in queue:
	for b in edges[a]:
		depth[b] = depth[a] + 1

LOG = 17
jump = [par]
for _ in range(LOG):
	last = jump[-1]
	jump.append( [last[last[i]] for i in range(n)] )
def lca(u,v):
	if depth[u] < depth[v]: u,v = v,u
	for j in reversed(jump):
		if depth[j[u]] >= depth[v]:
			u = j[u]
	if u == v: return v
	for j in reversed(jump):
		if j[u] != j[v]:
			u = j[u]
			v = j[v]
	return par[u]
