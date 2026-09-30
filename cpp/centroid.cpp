vector<int> mark(n,0), subt(n);
auto dfs1 = [&]( auto&& dfs1, int u, int p ) -> void {
        subt[u] = 1;
        for( auto v: edges[u] ) if( 0 == mark[v] and v != p ){
                dfs1(dfs1,v,u);
                subt[u] += subt[v];
        }
};
auto dfs2 = [&]( auto&& dfs2, int u, int p, int lim ) -> int {
        for( auto v: edges[u] ) if( 0 == mark[v] and v != p ){
                if( subt[v] > lim ) return dfs2(dfs2,v,u,lim);
        }
        return u;
};

auto solve = [&]( int rt ) -> void {
        dfs1(dfs1,rt,rt);
        //centroid is rt, remember to ignore marked nodes
};

auto centroid = [&]( auto&& centroid, int u ) -> void {
        dfs1(dfs1,u,u);
        int c = dfs2(dfs2,u,u,subt[u]/2);
        solve(c);
        mark[c] = 1;
        for( auto v: edges[c] ) if( 0 == mark[v] ) centroid(centroid,v);
};
centroid(centroid,0);
