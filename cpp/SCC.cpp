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
	
	vector<int> time(n,-1); int clk = 0;
	vector<int> ci(n,-1); int cnum = 0;
	vector<int> stack;

	auto dfs = [&]( auto f, int u ) -> int {
		stack.push_back(u);
		time[u] = clk++;
		int mt = time[u];
	
		for( auto v: edges[u] ) if( ci[v] == -1 ){
			if( -1 == time[v] ) mt = min(mt, f(f,v));
			mt = min(mt,time[v]);
		}

		if( mt == time[u] ){
			while( stack.back() != u ){
				ci[stack.back()] = cnum;
				stack.pop_back();
			}
			stack.pop_back();
			ci[u] = cnum++;
		}

		return mt;
	};
	rep(i,0,n) if( -1 == time[i] ){ dfs(dfs,i); }
	
	cout << cnum << endl;
	vector<vector<int>> bins(cnum);
	rep(i,0,n) bins[ci[i]].push_back(i);
	for( int i = cnum-1; i >= 0; i-- ){
		cout << bins[i].size() << " ";
		for( auto e: bins[i] ) cout << e << " ";
		cout << endl;
	}
}
