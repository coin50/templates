using T = int;
T defT = INT_MAX;
T f( const T& a, const T& b ){ return min(a,b); }
 
struct Seg{
        int N;
        vector<T> seg;
        Seg( int n, const vector<T> &a ){
                N = n;
                //while( N < n ) N *= 2;
                seg.resize(2*N);
                rep(i,0,a.size()) seg[i+N] = a[i];
                rep(i,a.size(),N) seg[i+N] = defT;
                for( int i = N-1; i > 0; i-- ) seg[i] = f(seg[2*i],seg[2*i+1]);
        }
        void update( int i, T x ){
                seg[i+N] = x;
                i = (i+N)/2;
                while( i > 0 ){
                        seg[i] = f(seg[2*i],seg[2*i+1]);
                        i /= 2;
                }
        }
        T query( int l, int r ){
                T ml = defT, mr = defT;
                l += N; r += N;
                while( l < r ){
                        if( l&1 ) ml = f(ml,seg[l++]);
                        if( r&1 ) mr = f(seg[--r],mr);
                        l /= 2; r /= 2;
                }
                return f(ml,mr);
        }
};
*/
