struct H{
        int n; ll MOD, x;
        vector<ll> p,h;
        H( const string& s, ll _MOD, ll _x ){
                n = s.size();
                MOD = _MOD;
                x = _x % MOD;
 
                p.resize(n+1); p[0] = 1;
                h.resize(n+1); h[0] = 0;
                rep(i,0,n){
                        p[i+1] = p[i] * x % MOD;
                        h[i+1] = (h[i] + p[i] * s[i]) % MOD;
                }
        }
        ll canon( int l,int r ){ return ((h[r] - h[l])*p[n-r]%MOD + MOD)%MOD; }
};
