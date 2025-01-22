EPS = 1e-8
class Point:
	def __init__(self,x,y):
		self.x = x; self.y = y
	def __add__(self,P):
		return Point(self.x+P.x, self.y+P.y)
	def __sub__(self,P):
		return Point(self.x-P.x, self.y-P.y)
	def __mul__(self,k):
		return Point(self.x*k, self.y*k)
	def __matmul__(self,P):
		return self.x*P.x + self.y*P.y
	def __xor__(self,P):
		return self.x*P.y - self.y*P.x
	def dis2(self):
		return self.x**2 + self.y**2
	def unit(self):
		d = self.dis2()
		return self*(d**-0.5) if d else Point(0,0)
	def __repr__(self):
		return f"({self.x}, {self.y})"

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
	k = ((C-A)^(D-C)) / ((B-A)^(D-C))
	return A + (B-A)*k

"""
a = Point(1,1)
b = Point(3,3)
c = Point(5,0)
d = Point(0,5)
I = intersect((a,b),(c,d)) 

print( onseg(I,(a,b)) )
"""