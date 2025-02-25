EPS = 1e-8
class Point:
    def __init__(self,x,y): self.x = x; self.y = y;
    def __add__(self,P): 	return Point(self.x+P.x, self.y+P.y)
    def __sub__(self,P): 	return Point(self.x-P.x, self.y-P.y)
    def __mul__(self,k): 	return Point(self.x*k, self.y*k)
    def __matmul__(self,P): return self.x*P.x + self.y*P.y
    def __xor__(self,P): 	return self.x*P.y - self.y*P.x
    def __repr__(self): 	return f"({self.x}, {self.y})"
    def perp(self):			return Point(self.y,-self.x)
    def dis2(self): 		return self.x**2 + self.y**2
    def mag(self):			return self.dis2() ** 0.5
    def unit(self):			return self * (self.dis2()**-0.5)

def area(pts):
	n = len(pts)
	return 0.5 * sum( pts[i]^pts[(i+1)%n] for i in range(n) )
def collinear(P,Q,R):
	return abs( (Q-P)^(R-P) ) < EPS
def onseg(P,S):
	A,B = S
	return abs( (A-P)^(B-P) ) < EPS and (A-P)@(B-P) < EPS
def intersect(L1,L2):
	A,B = L1; C,D = L2
	if abs((B-A)^(D-C)) < EPS: return 0
	k = ((C-A)^(D-C)) / ((B-A)^(D-C))
	return A + (B-A)*k
def project(P,L1):
    A,B = L1
    return intersect(L1, (P,P + (A-B).perp()))
def inside(P,poly):
	Px = P + Point(1,0)
	S = 0
	for i in range(n := len(poly)):
		seg = (poly[i],poly[(i+1)%n])
		I = intersect( (P,Px),seg )
		if I and onseg(I,seg) and not onseg( P,(I,Px) ):
			if (I-seg[0]).dis2() < EPS and seg[1].y < I.y: continue
			if (I-seg[1]).dis2() < EPS and seg[0].y < I.y: continue
			S ^= 1
	return S
def convex_hull(pts):
	if not pts: return []
	if all( (p-pts[0]).dis2() < EPS for p in pts ): return [pts[0]]
	pts = sorted(pts, key=lambda p:(p.x,p.y))
	low = []
	for p in pts:
		while len(low) > 1 and (low[-1]-low[-2])^(p-low[-1]) < EPS:
			low.pop()
		low.append(p)
	high = []	
	for p in reversed(pts):
		while len(high) > 1 and (high[-1]-high[-2])^(p-high[-1]) < EPS:
			high.pop()
		high.append(p)
	return low + high[1:-1]
"""
a = Point(1,1)
b = Point(3,3)
c = Point(5,0)
d = Point(0,5)
I = intersect((a,b),(c,d)) 

print( onseg(I,(a,b)) )
"""