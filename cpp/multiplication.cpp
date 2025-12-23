const array<ll,23> W = []{
	array<ll,23> W = {2200}; //order 2^23
	rep(i,0,22) W[i+1] = W[i]*W[i]%MOD;
	return W;
}();
vector<ll> dft( vector<ll> poly, int b ){
	int n = 1<<b;
	poly.resize(n,0);

	rep(loop,1,b+1){
		vector<ll> nv(n,0);

		ll acc = 1;
		int space = n>>loop;
		for( int q = 0; q < n; q += space ){
			rep(r,0,space) nv[q+r] = (poly[2*q%n + r] + acc*poly[2*q%n + space + r])%MOD;
			acc = acc*W[23-loop]%MOD;
		}
		poly = nv;
	}
	return poly;
}
vector<ll> mul( vector<ll> a, vector<ll> b ){
	int sz = a.size() + b.size() - 1;
	int j = 1;
	while( 1<<j < sz ) j++;
	
	vector<ll> A = dft(a,j);
	vector<ll> B = dft(b,j);
	ll inv = p0w(1<<j,MOD-2);
	rep(i,0,B.size()) B[i] = A[i]*B[i]%MOD*inv%MOD;
	
	A = dft(B,j);
	reverse(A.begin()+1,A.end());
	A.resize(sz);
	return A;
}
