#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=(a);i<(b);i++)

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

int main(){
        //random
        mt19937 rng(time(0));
        mt19937_64 rng64(time(0));
        
        vector<int> a;
        shuffle(a.begin(),a.end(),rng);

        uniform_real_distribution<> dist(0,1);
        double r = dist(rng);

        
        //bits
        int x,y;
        x = __builtin_ctz(y);
        x = __builtin_clzll(y);
        x = __builtin_popcountll(y);

        bitset<1000> b;
        b.set(); b.reset(); b.flip();
        b.count(); b.any(); b.all(); b.none();

        
        //input
        cin.tie(0)->sync_with_stdio(0);
        string s;
        cin >> s;
        getline(cin >> ws,s);

        
        //vector
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());

        bool adv = next_permutation(a.begin(),a.end());

        
        //priority queue TODO
        //custom set comparator TODO
}
