struct MCMF {
        const ll INF = LLONG_MAX / 4;
        struct Edge{ int to; ll cap, flow, cost; };

        int n;
        vector<Edge> edges;
        vector<vector<int>> adj; vector<pair<int,int>> par; vector<int> inq;
        vector<ll> dist;
        MCMF( int n ) : n(n), adj(n), par(n), inq(n), dist(n) {}
        void add_edge( int u,int v,ll f,ll c ){
                int i = edges.size();
                edges.push_back({v,f,0,c});
                edges.push_back({u,f,f,-c});
                adj[u].push_back(i);
                adj[v].push_back(i^1);
        }
        bool find_path( int s,int t ){
                for( auto& e: dist ) e = INF;
                for( auto& e: inq ) e = 0;
                queue<int> q; q.push(s);
                dist[s] = 0; inq[s] = 1;
                while( !q.empty() ){
                        int cur = q.front(); q.pop();
                        inq[cur] = 0;
                        for( int idx: adj[cur] ){
                                auto [nxt,cap,fl,wt] = edges[idx];
                                ll nxtD = dist[cur] + wt;
                                if( fl >= cap or nxtD >= dist[nxt] ) continue;
                                dist[nxt] = nxtD;
                                par[nxt] = {cur,idx};
                                if( inq[nxt] ) continue;
                                q.push(nxt); inq[nxt] = 1;
                        }
                }
                return dist[t] < INF;
        }
        pair<ll,ll> solve( int s,int t ){
                ll flow = 0, cost = 0;
                while( find_path(s,t) ){
                        ll f = INF;
                        for( int v = t; v != s; ){
                                auto [u, i] = par[v];
                                f = min(f, edges[i].cap - edges[i].flow);
                                v = u;
                        }
                        flow += f;
                        for( int v = t; v != s; ){
                                auto [u, i] = par[v];
                                edges[i].flow += f;
                                edges[i^1].flow -= f;
                                v = u;
                        }
                }
                rep(i,0,edges.size()/2) cost += edges[i<<1].cost * edges[i<<1].flow;
                return {flow,cost};
        }
};
