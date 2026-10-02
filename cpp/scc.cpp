#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);i++)

int main(){
	int n,m; cin >> n >> m;
	vector<vector<int>> edges(n);
	rep(_,0,m){
		int u,v; cin >> u >> v;
		edges[u].push_back(v);
	}
	
	int clk = 1, cnum = 0;
        vector<int> time(n,0), ci(n,-1), stack;
	auto dfs = [&]( auto&& dfs, int u ) -> int {
		stack.push_back(u);
		time[u] = clk++;

		int mt = time[u];
		for( auto v: edges[u] ) if( ci[v] == -1 )
                        mt = min(mt, time[v] ?: dfs(dfs,v));

		if( mt == time[u] ){
                        int v;
                        do{
                                v = stack.back(); stack.pop_back();
                                ci[v] = cnum;
                        } while( v != u );
			cnum++;
		}
		return mt;
	};
	rep(i,0,n) if( 0 == time[i] ){ dfs(dfs,i); }
	
	cout << cnum << endl;
	vector<vector<int>> bins(cnum);
	rep(i,0,n) bins[ci[i]].push_back(i);
	for( int i = cnum-1; i >= 0; i-- ){
		cout << bins[i].size() << " ";
		for( auto e: bins[i] ) cout << e << " ";
		cout << endl;
	}
}
