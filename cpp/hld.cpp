vector<int> subt(n), par(n), depth(n), heavy(n,-1);
auto dfs1 = [&]( auto&& dfs1, int u ) -> void {
        subt[u] = 1;
        for( auto v: edges[u] ) if( v != par[u] ){
                depth[v] = depth[u] + 1;
                par[v] = u;
                dfs1(dfs1,v);
                subt[u] += subt[v];
                if( heavy[u] == -1 or subt[v] > subt[heavy[u]] ) heavy[u] = v;
        }
};

vector<int> head(n), enter(n);
int ti = 0;
auto dfs2 = [&]( auto&& dfs2, int u, int h ) -> void {
        enter[u] = ti++;
        head[u] = h;
        if( heavy[u] > -1 ) dfs2(dfs2,heavy[u],h);
        for( auto v: edges[u] ) if( v != par[u] and v != heavy[u] ){
                dfs2(dfs2,v,v);
        }
};
par[0] = 0; depth[0] = 0;
dfs1(dfs1,0);
dfs2(dfs2,0,0);


auto query = [&]( int a,int b ){
        T res = defT;
        while( head[a] != head[b] ){
                if( depth[head[a]] < depth[head[b]] ) swap(a,b);
                res = f(res, seg.query(enter[head[a]],enter[a]+1));
                a = par[head[a]];
        }
        if( depth[a] > depth[b] ) swap(a,b);
        return f(res, seg.query(enter[a],enter[b]+1));
};

auto lca = [&]( int u,int v ){
        while( head[u] != head[v] ){
                if( depth[head[u]] > depth[head[v]] ) u = par[head[u]];
                else v = par[head[v]];
        }
        return depth[u] < depth[v] ? u : v;
};
