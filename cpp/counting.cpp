const ll MOD = 1e9 + 7;
ll p0w(ll x,ll e){
	ll p = 1;
	while(e){
		if(e&1) p = p*x%MOD;
		x = x*x%MOD;
		e /= 2;
	}
	return p;
}

const int MAX = 6000;
ll fact[MAX], anti[MAX];
void init(){
        fact[0] = 1;
        rep(i,1,MAX) fact[i] = fact[i-1]*i%MOD;
        anti[MAX-1] = p0w(fact[MAX-1],MOD-2);
        for(int i = MAX-2; i >= 0; i--) anti[i] = anti[i+1]*(i+1)%MOD;
}
ll cmb(int n,int k){ return (0 <= k and k <= n) ? fact[n]*anti[k]%MOD*anti[n-k]%MOD : 0; }
ll star(int v,int s){ return (v == 0 and s == 0) + cmb(s+v-1,v-1); }
ll cat(int n){ return cmb(2*n,n) - cmb(2*n,n-1); }


//other version
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
