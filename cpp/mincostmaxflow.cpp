struct MCMF {
        const ll INF = LLONG_MAX / 4;
	struct Edge{ int from, to, rev; ll cap, cost, flow; };

	int N;
	vector<vector<Edge>> edges;
	vector<int> inq;
	vector<ll> dist;
	vector<Edge*> par;
	MCMF( int N ) : N(N), edges(N), inq(N), dist(N), par(N) {}

	void add_edge( int u, int v, ll f, ll c ){
		if( u == v ) return;
                edges[u].push_back( {u,v,(int)edges[v].size(),f,c,0} );
                edges[v].push_back( {v,u,(int)edges[u].size()-1,0,-c,0} );
	}
        bool path( int s,int t ){
                for( auto& e: dist ) e = INF;
                for( auto& e: inq ) e = 0;
                dist[s] = 0; inq[s] = 1;

                queue<int> q; q.push(s);
                while( q.size() > 0 ){
			int u = q.front(); q.pop();
			inq[u] = 0;
			for( auto& e: edges[u] ){
				ll nd = dist[u] + e.cost;
				if( e.cap > e.flow and nd < dist[e.to]){
					dist[e.to] = nd;
					par[e.to] = &e;
					if( 0 == inq[e.to] ){
						q.push(e.to);
						inq[e.to] = 1;
					}
				}
			}
		}
		return dist[t] < INF;
        }
        pair<ll,ll> solve(int s, int t) {
                ll flow = 0, cost = 0;
                while( path(s,t) ){
                        ll f = INF;
                        for( Edge* e = par[t]; e; e = par[e->from] )
                                f = min(f, e->cap - e->flow);
                        flow += f;
                        for( Edge* e = par[t]; e; e = par[e->from] ){
                                e->flow += f;
                                edges[e->to][e->rev].flow -= f;
                        }
                }
                rep(i,0,N) for( auto& e: edges[i] ) cost += e.cost * e.flow;
                return {flow, cost/2};
        }
};


struct MCMF {
        const ll INF = LLONG_MAX / 4;
	struct Edge{ int from, to, rev; ll cap, cost, flow; };
 
	int N;
	vector<vector<Edge>> edges;
	vector<int> seen;
	vector<ll> dist, pi;
	vector<Edge*> par;
	MCMF( int N ) : N(N), edges(N), seen(N), dist(N), pi(N), par(N) {}
 
	void add_edge( int u, int v, ll f, ll c ){
		if( u == v ) return;
                edges[u].push_back( {u,v,(int)edges[v].size(),f,c,0} );
                edges[v].push_back( {v,u,(int)edges[u].size()-1,0,-c,0} );
	}
        bool path( int s, int t ){
                for( auto& e: dist ) e = INF;
                for( auto& e: seen ) e = 0;
                dist[s] = 0; ll di;
 
                priority_queue<pair<ll,int>> q;
                q.push( {0,s} );
                while( q.size() > 0 ){
                        s = q.top().second; q.pop();
                        if( seen[s] ) continue;
                        seen[s] = 1; di = dist[s] + pi[s];
                        for( auto& e: edges[s] ) if( 0 == seen[e.to] ){
                                ll val = di - pi[e.to] + e.cost;
                                if( e.cap - e.flow > 0 and val < dist[e.to] ){
                                        dist[e.to] = val;
                                        par[e.to] = &e;
                                        q.push( {-dist[e.to],e.to} );
                                }
                        }
                }
                rep(i,0,N) pi[i] = min(pi[i] + dist[i],INF);
                return seen[t];
        }
        pair<ll,ll> solve(int s, int t) {
                ll flow = 0, cost = 0;
                while( path(s,t) ){
                        ll f = INF;
                        for( Edge* e = par[t]; e; e = par[e->from] )
                                f = min(f, e->cap - e->flow);
                        flow += f;
                        for( Edge* e = par[t]; e; e = par[e->from] ){
                                e->flow += f;
                                edges[e->to][e->rev].flow -= f;
                        }
                }
                rep(i,0,N) for( auto& e: edges[i] ) cost += e.cost * e.flow;
                return {flow, cost/2};
        }
};
