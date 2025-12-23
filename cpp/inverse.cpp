vector<ll> inv( vector<ll> f, int n ){
	vector<ll> g = {p0w(f[0],MOD-2)};
	
	while( g.size() < n ){
		int m = min(2*(int)g.size(),n);
		
		vector<ll> f0 = f;
		f0.resize(m);
		
		vector<ll> fg = mul(f0,g);
		fg.resize(m);
		rep(i,0,m) fg[i] = -fg[i];
		fg[0] += 2;

		g = mul(g,fg);
		g.resize(m);
	}
	return g;
}
