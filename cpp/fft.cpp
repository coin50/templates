void dft( vector<ll>& a, int inv ){
	int n = a.size();
	for(int i = 1,j = 0; i < n; i++){
		int b = n>>1;
		for(; j&b; b>>=1) j ^= b;
		j ^= b;
		if(i < j) swap(a[i],a[j]);
	}
	for(int len = 2; len <= n; len <<= 1){
		ll wn = p0w(inv ? 224678 : 4443,(MOD-1)/len);
		for(int i = 0; i < n; i += len){
			ll w = 1;
			rep(j,0,len/2){
				ll u = a[i+j],v = a[i+j+len/2]*w%MOD;
				a[i+j] = (u+v)%MOD;
				a[i+j+len/2] = (u-v+MOD)%MOD;
				w = w*wn%MOD;
			}
		}
	}
	if(inv){
		ll ni = p0w(n,MOD-2);
		for(ll& x:a) x = x*ni%MOD;
	}
}
vector<ll> mul( vector<ll> a, vector<ll> b ){
	int sz = a.size()+b.size()-1;
	int n = 1;
	while(n < sz) n <<= 1;
	a.resize(n); b.resize(n);
	dft(a,0); dft(b,0);
	rep(i,0,n) a[i] = a[i]*b[i]%MOD;
	dft(a,1);
	a.resize(sz);
	return a;
}
 
