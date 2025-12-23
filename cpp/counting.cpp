const ll MOD = 998244353;
ll p0w(ll x,ll e){
	ll p = 1;
	ll acc = x;
	while(e){
		if(e&1) p = p*acc%MOD;
		acc = acc*acc%MOD;
		e /= 2;
	}
	return p;
}

const int MAX = 1e6 + 1;
const array<ll,MAX> fact = []{
	array<ll,MAX> fact = {1};
	rep(i,1,MAX) fact[i] = fact[i-1]*i%MOD;
	return fact;
}();
const array<ll,MAX> anti = []{
	array<ll,MAX> anti;
	anti[MAX-1] = p0w(fact[MAX-1],MOD-2);
	for( int i = MAX-2; i >= 0; i-- ) anti[i] = anti[i+1]*(i+1)%MOD;
	return anti;
}();
ll cmb(ll n, ll k){ return 0 <= k and k <= n ? fact[n]*anti[k]%MOD*anti[n-k]%MOD : 0; }
