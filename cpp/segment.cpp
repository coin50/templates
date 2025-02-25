using T = int;
const T def = INT_MAX;
T f(T a, T b){ return min(a,b); }

int N;
const int MAX = 200000;
T seg[2*MAX]; //set to default
void update(int i, T v){
    seg[i += N] = v;
    while(i /= 2) seg[i] = f(seg[2*i],seg[2*i+1]);
}
T query(int l, int r){
    l += N, r += N;
    T m1 = def, m2 = def;
    while(l<r){
        if(l&1) m1 = f(m1,seg[l++]);
        if(r&1) m2 = f(seg[--r],m2);
        l /= 2, r /= 2;
    }
    return f(m1,m2);
}

"""
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n,q; cin >> n >> q;
    N = n;
    for( int i = 0; i < n; i++ ) cin >> seg[i+n];
    for( int i = n-1; i > 0; i-- ) seg[i] = f(seg[2*i],seg[2*i+1]);
    while(q--){
        int o; cin >> o;
        switch(o){
            case 2: int l,r; cin >> l >> r; cout << query(l-1,r) << '\n'; break;
            case 1: int i,x; cin >> i >> x; update(i-1,x); break;
        }
    }
}
"""