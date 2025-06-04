using T = int;
const T defT = 0;
T f(T a, T b){ return a+b; }

struct Node{
    T val;
    int lc; int rc;
};
vector<Node> pool;

int make( T v ){
    int k = pool.size();
    pool.emplace_back( Node{v,-1,-1} );
    return k;
}
int make( int lc, int rc ){
    int k = pool.size(); 
    pool.emplace_back( Node{f(pool[lc].val,pool[rc].val),lc,rc} );
    return k;
}
int init( int l, int r ){
    if( r-l == 1 ) return make(defT);
    int m = (l+r)/2;
    return make(init(l,m),init(m,r));
}
int update( int root, T v, int i, int l, int r ){
    if( r-l == 1 ) return make( f(pool[root].val,v) );
    int m = (l+r)/2;
    return i < m
        ? make( update( pool[root].lc, v,i,l,m ), pool[root].rc )
        : make( pool[root].lc, update( pool[root].rc, v,i,m,r) );
}
int query( int root, int ql, int qr, int l, int r ){
    if( qr <= l or r <= ql ) return defT;
    if( ql <= l and r <= qr ) return pool[root].val;
    int m = (l+r)/2;
    return f(
        query( pool[root].lc, ql,qr,l,m ),
        query( pool[root].rc, ql,qr,m,r )
    );
}
