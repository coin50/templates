#define ll long long
#define MOD 0x3b800001
#define pow p0w
ll p0w(ll x,ll e){
    ll acc = x;
    ll p = 1;
    while(e){
        if(e&1) p=p*acc%MOD;
        acc=acc*acc%MOD;
        e >>= 1;
    }
    return p;
}

#define MAX 100
ll fact[MAX+1];
ll anti[MAX+1];
void init_fact(){
    fact[0] = 1;
    for( int i = 1; i <= MAX; i++ ) fact[i] = fact[i-1]*i%MOD;
    anti[MAX] = pow(fact[MAX],MOD-2);
    for( int i = MAX-1; i >= 0; i-- ) anti[i] = anti[i+1]*(i+1)%MOD;
}