using TAG = pair<ll,ll>; //ax + b
using T = pair<ll,int>; //sum, length
const TAG defTAG = {1,0};
const T defT = {0,0};
T make( int x ){ return {x,1}; }
T f( const T& a, const T& b ){ return {a.first+b.first,a.second+b.second}; }
T eval( const TAG& t, const T& a ){ return {t.first*a.first + t.second*a.second,a.second}; }
TAG comp( const TAG& f, const TAG& g ){ return {f.first*g.first,f.first*g.second+f.second}; }

struct Lazy{
        int N;
        vector<TAG> tags;
        vector<T> seg;
        Lazy( int n, const vector<T>& a ){
                N = n;
                //while( N < n ) N *= 2;
                tags.resize(N,defTAG);
                seg.resize(2*N);
                rep(i,0,a.size()) seg[i+N] = a[i];
                rep(i,a.size(),N) seg[i+N] = defT;
                for( int i = N-1; i > 0; i-- ) seg[i] = f(seg[2*i],seg[2*i+1]);
        }
        void apply( const TAG& tag, int i ){
                if( i < N ) tags[i] = comp(tag,tags[i]);
                seg[i] = eval(tag,seg[i]);
        }
        void hammer_down( int i ){
                if( i < 2 ) return;
                for( int k = 31 - __builtin_clz(i); k > 0; k-- ){
                        int j = i>>k;
                        apply( tags[j], 2*j );
                        apply( tags[j], 2*j+1 );
                        tags[j] = defTAG;
                }
        }
        void boiler_up( int i ){
                while( i > 1 ){
                        i /= 2;
                        seg[i] = f(seg[2*i],seg[2*i+1]);
                }
        }
        void update( int l, int r, const TAG& tag ){
                l += N, r += N;
                int l0 = l >> __builtin_ctz(l);
                int r0 = r >> __builtin_ctz(r);
                hammer_down(l0);
                hammer_down(r0-1);
                while( l < r ){
                        if(l&1) apply(tag,l++);
                        if(r&1) apply(tag,--r);
                        l /= 2, r /= 2;
                }
                boiler_up(l0);
                boiler_up(r0-1);
        }
        T query( int l, int r ){
                l += N, r += N;
                hammer_down(l);
                hammer_down(r-1);
                T m1 = defT, m2 = defT;
                while( l < r ){
                        if(l&1) m1 = f(m1,seg[l++]);
                        if(r&1) m2 = f(seg[--r],m2);
                        l /= 2, r /= 2;
                }
                return f(m1,m2);
        }
};
