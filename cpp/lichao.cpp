struct Line{
        ll a,b;
        ll eval( ll x ) const { return a*x + b; }
};
struct LiChao{
        int N;
        vector<ll> xs;
        vector<Line> seg;
        vector<int> left,right;

        LiChao( int n ){
                N = 1;
                while( N < n ) N *= 2;
                xs.resize(2*N);
                rep(i,0,2*N) xs[i] = i;
                //while( N < x.size() ) N *= 2;
                //x.resize(N,x.back());
                //xs = move(x);
                
                seg.resize(2*N);
                rep(i,1,2*N) seg[i] = {0,LLONG_MIN};

                left.resize(2*N); right.resize(2*N);
                rep(i,0,N){ left[i+N] = i; right[i+N] = i+1; }
                for( int i = N-1; i > 0; i-- ){ left[i] = left[2*i]; right[i] = right[2*i+1]; }
        }
        
        int find( ll x ){ return x; }
        //int find( ll x ){ return lower_bound(xs.begin(),xs.end(),x) - xs.begin(); }
        ll query( ll x ){
                int i = find(x) + N;
                ll best = LLONG_MIN;
                while( i ){
                        best = max(best, seg[i].eval(x));
                        i /= 2;
                }
                return best;
        }
        void insert(int i, const Line& ell){
                int m = (left[i] + right[i])/2;
                int l = left[i];
 
                Line other = ell;
                if( seg[i].eval(xs[m]) < ell.eval(xs[m]) ) swap(other,seg[i]);
                if( i >= N ) return;
                if( seg[i].eval(xs[l]) < other.eval(xs[l]) ) insert(2*i,other);
                else insert(2*i+1,other);
        }
        void insert( ll xl, ll xr, const Line& ell ){
                int l = find(xl) + N;
                int r = find(xr) + N;
                while( l<r ){
                        if( l&1 ) insert(l++,ell);
                        if( r&1 ) insert(--r,ell);
                        l /= 2; r /= 2;
                }
        };
};
