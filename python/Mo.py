n = int(input())
B = int(n**0.5)
def Mo(x,y): return (x//B)*n + (n-y-1 if (x//B)&1 else y)

#for y in range(n): print(*(Mo(x,y) for x in range(n)),sep='\t')