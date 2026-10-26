mt19937 rng(time(0));
using T = ll;
const T defT = 0;
T f( const T& a, const T& b ){ return a+b; };

struct Node{
        Node *left = nullptr, *right = nullptr;
        int sz = 1, priority = rng();
        int rev = 0;
        T self,data;
        Node( T x ){ self = data = x; }
};

int sz( Node* n ){ return n == nullptr ? 0 : n->sz; }
T get( Node* n ){ return n == nullptr ? defT : n->data; }
void update( Node* rt ){
        rt->sz = 1 + sz(rt->left) + sz(rt->right);
        rt->data = f( get(rt->left), f(rt->self,get(rt->right)) );
}
void push( Node* rt ){
        if( !rt ) return;
        if( !rt->rev ) return;
        swap(rt->left,rt->right);
        rt->rev = 0;
        if( rt->left ) rt->left->rev ^= 1;
        if( rt->right ) rt->right->rev ^= 1;
}
 
pair<Node*,Node*> split( Node* rt, int i ){ //split into [0,i) and [i,n)
        if( !rt ) return {nullptr,nullptr};
        push(rt);
        if( i > sz(rt->left) ){
                auto [L,R] = split( rt->right, i - 1 - sz(rt->left) );
                rt->right = L;
                update(rt);
                return {rt,R};
        } else {
                auto [L,R] = split( rt->left, i );
                rt->left = R;
                update(rt);
                return {L,rt};
        }
}
Node* merge( Node* a, Node* b ){
        if( !a ) return b;
        if( !b ) return a;
        if( a->priority > b->priority ){
                push(a);
                a->right = merge(a->right,b); 
                update(a);
                return a;
        } else {
                push(b);
                b->left = merge(a,b->left);
                update(b);
                return b;
        }
}
