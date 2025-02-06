using ll = long long;

int N;
const int MAX = 200000;
pair<ll,ll> lazy[MAX];
ll seg[2*MAX];
int len[2*MAX];

ll f( ll a, ll b ){ //combine segments
    return a+b;
}
void apply( pair<ll,ll> f, int i ){
    pair<ll,ll> g = lazy[i];
    if(i < N) lazy[i] = make_pair( f.first*g.first, f.first*g.second + f.second ); //compose two tags
    seg[i] = f.first*seg[i] + f.second*len[i]; //evaluate tag on segment
}

void hammer_down( int i ){
    for( int k = 20; k > 0; k-- ){
        int j = (i>>k);
        if(j==0) continue;
        apply( lazy[j], 2*j );
        apply( lazy[j], 2*j+1 );
        lazy[j] = make_pair(1,0);
    }
}
void boiler_up( int i ){
    i /= 2;
    while(i){
        seg[i] = f(seg[2*i],seg[2*i+1]);
        i /= 2;
    }
}
void update( int l, int r, pair<ll,ll> T ){ //applies the linear transformation T(x) := ax+b to the range [l,r)
    l += N, r += N;
    int l0 = l, r0 = r;
    while(l0%2==0) l0 /= 2;
    while(r0%2==0) r0 /= 2;
    hammer_down(l0);
    hammer_down(r0-1);
    while( l < r ){
        if(l&1) apply(T,l++);
        if(r&1) apply(T,--r);
        l /= 2, r /= 2;
    }
    boiler_up(l0);
    boiler_up(r0-1);
}
ll query( int l, int r ){ //range sum on [l,r)
    l += N, r += N;
    hammer_down(l);
    hammer_down(r-1);
    ll m = 0; //default value
    while( l < r ){
        if(l&1) m = f(m,seg[l++]);
        if(r&1) m = f(m,seg[--r]);
        l /= 2, r /= 2;
    }
    return m;
}