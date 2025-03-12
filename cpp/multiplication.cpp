ll W[23];
void init(){
    W[0] = 2200;
    for( int i = 0; i < 22; i++ ) W[i+1] = W[i]*W[i]%MOD;
}
vector<ll> dft( vector<ll> poly, int b ){
    int n = 1<<b;
    poly.resize(n,0);
    for( int loop = 1; loop <= b; loop++ ){
        vector<ll> nv(n,0);
        ll acc = 1;
        int space = n>>loop;
        for( int q = 0; q < n; q += space ){
            for( int r = 0; r < space; r++ )
                nv[q+r] = (poly[2*q%n + r] + acc*poly[2*q%n + space + r])%MOD;
            acc = acc*W[23-loop]%MOD;
        }
        poly = move(nv);
    }
    return poly;
}
vector<ll> mul( vector<ll> a, vector<ll> b ){
    int sz = a.size()+b.size()-1;
    int j = 1;
    for( int s = sz-1; s >>= 1; ) j++;
    
    vector<ll> A = dft(a,j);
    vector<ll> B = dft(b,j);
    ll inv = p0w(1<<j,MOD-2);
    for( int i = 1<<j; i--; ) B[i] = (A[i]*B[i]%MOD)*inv%MOD;

    A = dft(B,j);
    reverse(A.begin()+1, A.end());
    A.resize( sz );
    return A;
}

/*
int main(){
    cin.tie(0)->sync_with_stdio(0);
    init();

    int n,m; cin >> n >> m;
    vector<ll> a(n,0);
    vector<ll> b(m,0);

    for( int i = 0; i < n; i++ ) cin >> a[i];
    for( int i = 0; i < m; i++ ) cin >> b[i];

    vector<ll> c = mul( a,b );
    for( int e: c ) cout << e << " ";
    cout << endl;
}
*/