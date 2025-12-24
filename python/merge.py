ci = list(range(n))
comps = [[i] for i in range(n)]
def connect(a,b):
	if ci[a] == ci[b]: return
	ca = ci[a]
	cb = ci[b]
	if len(comps[ca]) > len(comps[cb]):
		a,b = b,a
		ca,cb = cb,ca

	comps[cb].extend(comps[ca])
	for e in comps[ca]:
		ci[e] = cb
	comps[ca] = -1
