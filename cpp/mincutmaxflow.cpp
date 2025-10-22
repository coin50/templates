// untested, not my template
const int MAXN = 1e5, MAXM = 1e6;
struct EdgeList{
        int sz, begin[MAXN], dest[MAXM], next[MAXM]; ll flow[MAXM];
        void clear( int n ){ sz = 0; rep(i,0,n) begin[i] = -1; }
        EdgeList( int n = MAXN ){ clear(n); }
        void add_edge( int u,int v,ll f ){
                dest[sz] = v; next[sz] = begin[u];
                flow[sz] = f; begin[u] = sz++;
                dest[sz] = u; next[sz] = begin[v];
                flow[sz] = 0; begin[v] = sz++;
        }
};
struct Dinic{
        int n,s,t,d[MAXN],w[MAXN],q[MAXN];
        int bfs( EdgeList& e ){
                rep(i,0,n) d[i] = -1;
                int l,r;
                q[l=r=0] = s, d[s] = 0;
                for( ; l <= r; ++l )
                        for( int k = e.begin[q[l]]; ~k; k = e.next[k] )
                                if( !~d[e.dest[k]] && e.flow[k] > 0 )
                                        d[e.dest[k]] = d[q[l]] + 1, q[++r] = e.dest[k];
                return !d[t] ? 1 : 0;
        }
        int dfs( EdgeList& e, int u, ll ext ){
                if( u == t ) return ext;
                int k = w[u]; ll ret = 0;
                for( ; ~k; k = e.next[k], w[u] = k ){
                        if( !ext ) break;
                        if( d[e.dest[k]] == d[u] + 1 && e.flow[k] > 0 ){
                                ll flow = dfs(e,e.dest[k], min(e.flow[k],ext));
                                if( flow > 0 ){
                                        e.flow[k] -= flow, e.flow[k^1] += flow;
                                        ret += flow, ext -= flow;
                                }
                        }
                }
                if( !~k ) d[u] = -1;
                return ret;
        }
        int solve( EdgeList& e, int n_, int s_, int t_ ){
                ll ans = 0; n = n_, s = s_, t = t_;
                while( bfs(e) ){
                        rep(i,0,n) w[i] = e.begin[i];
                        ans += dfs(e,s,LLONG_MAX);
                }
                return ans;
        }
};
