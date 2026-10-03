struct Dinic{
        struct Edge{
                int to,rev;
                ll c,oc;
                ll flow(){ return max(oc-c,0LL); }
        };
        vector<int> lvl,ptr,q;
        vector<vector<Edge>> adj;
        Dinic( int n ): lvl(n), ptr(n), q(n), adj(n) {}
        void add_edge( int u,int v,ll f ){
                adj[u].push_back( {v,(int)adj[v].size(),f,f} );
                adj[v].push_back( {u,(int)adj[u].size()-1,0,0} );
        }
        ll dfs( int v,int t,ll f ){
                if( v == t or f == 0 ) return f;
                for( int& i = ptr[v]; i < adj[v].size(); i++ ){
                        Edge& e = adj[v][i];
                        if( lvl[e.to] == lvl[v] + 1 ) if( ll p = dfs(e.to,t,min(f,e.c)) ){
                                e.c -= p, adj[e.to][e.rev].c += p;
                                return p;
                        }
                }
                return 0;
        }
        ll solve( int s,int t ){
                ll flow = 0;
                q[0] = s;
                rep(L,0,31) 
                do {
                        lvl = ptr = vector<int>(q.size());
                        int qi = 0, qe = lvl[s] = 1;
                        while( qi < qe and 0 == lvl[t] ){
                                int v = q[qi++];
                                for( auto e: adj[v] ) if( 0 == lvl[e.to] and (e.c)>>(30-L) )
                                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
                        }
                        while( ll p = dfs(s,t,LLONG_MAX) ) flow += p;
                } while( lvl[t] );
                return flow;
        }
        bool left_of_min_cut(int a) { return lvl[a] != 0; }
};
