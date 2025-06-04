#include <bits/stdc++.h>
using namespace std;

const int def = 0;
int f(int a, int b){ return a+b; }
struct Node{
    int val;
    Node* lc; Node* rc;
    Node( int v ): val(v) {}
    Node( Node* left, Node* right ): val(f(left->val,right->val)), 
        lc(left), rc(right) {}
};

Node* build( int l, int r ){
    if( r-l == 1 ) return new Node(def);
    int m = (l+r)/2;
    return new Node(build(l,m),build(m,r));
}
Node* update( Node* root, int v, int i, int l, int r ){
    if( r-l == 1 ) return new Node(root->val + v);
    int m = (l+r)/2;
    return i < m
        ? new Node( update( root->lc, v,i,l,m ), root->rc )
        : new Node( root->lc, update( root->rc, v,i,m,r) );
}
int query( Node* root, int ql, int qr, int l, int r ){
    if( qr <= l or r <= ql ) return def;
    if( ql <= l and r <= qr ) return root->val;
    int m = (l+r)/2;
    return f(
        query( root->lc, ql,qr,l,m ),
        query( root->rc, ql,qr,m,r )
    );
}

/*
//find Kth smallest number in a[L:R]
int main(){
    int n,q; cin >> n >> q;
    vector<int> a(n);
    for( int& x: a ) cin >> x;

    vector<int> b = a;
    sort(b.begin(),b.end());
    map<int,int> comp;
    for( int i = 0; i < n; i++ ) comp[b[i]] = i;
    
    for( int i = 0; i < n; i++ ) a[i] = comp[a[i]];

    vector<Node*> roots(n+1);
    roots[0] = build(0,n);
    for( int i = 0; i < n; i++ )
        roots[i+1] = update( roots[i],1,a[i],0,n );

    while(q--){
        int l,r,k; cin >> l >> r >> k;

        Node *left = roots[l], *right = roots[r];
        int L = 0, R = n;
        int S = 0;
        while( R-L > 1 ){
            int M = (L+R)/2;
            int leftside = (right->lc->val) - (left->lc->val);
            if( S + leftside <= k ){
                S += leftside;
                right = right->rc;
                left = left->rc;
                L = M;
            } else {
                right = right->lc;
                left = left->lc;
                R = M;
            }
        }
        cout << b[L] << endl;
    }
}*/
