struct TwoSat{
        int n;
        vector<vector<int>> edges;
        vector<int> values;
        TwoSat( int _n = 0 ){
                n = _n;
                edges.resize(2*n);
        }

        void either( int f, int j ){
                f = max(2*f, -1-2*f);
                j = max(2*j, -1-2*j);
                edges[f].push_back(j^1);
                edges[j].push_back(f^1);
        }
        vector<int> val,comp,z;
        int ti;
        int dfs( int i ){
                int low = val[i] = ++ti;
                int x;
                z.push_back(i);
                for( int e: edges[i] ) if( !comp[e] ) 
                        low = min(low,val[e] ?: dfs(e));
                if( low == val[i] ) do{
			x = z.back(); 
                        z.pop_back();
			comp[x] = low;
			if( values[x/2] == -1 ) values[x/2] = x&1;
		} while( x != i );
                return val[i] = low;
        }
        int solve(){
                ti = 0;
                z.clear();
                values.assign(n,-1);
                val.assign(2*n,0); 
                comp = val;
		rep(i,0,2*n) if( !comp[i] ) dfs(i);
		rep(i,0,n) if( comp[2*i] == comp[2*i+1] ) return 0;
		return 1;
	}

        int add_var(){
                edges.resize(2*n+2);
                return n++;
        }
        void at_most_one( const vector<int>& vs ){
                if( vs.size() <= 1 ) return;
                int cur = ~vs[0];
                rep(i,2,vs.size()){
                        int nxt = add_var();
                        either(cur,~vs[i]);
                        either(cur,nxt);
                        either(~vs[i],nxt);
                        cur = ~nxt;
                }
                either(cur,~vs[1]);
        }
};
