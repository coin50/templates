const ll INF = LLONG_MAX;
struct Line {
        ll a,b;
        ll eval( ll x ) const { return a*x + b; }
};
ll fdiv( ll a, ll b ){ return a/b - ((a^b)<0 && a%b); }
ll breakpoint( Line a, Line b ){ return fdiv( a.b-b.b, b.a-a.a ); }

struct Hull{
        vector<Line> hull;
        int size(){ return hull.size(); }
        Line operator[]( int i ){ return hull[i]; }
        void insert( Line ell ){
                if( hull.size() >= 1 and hull.back().a == ell.a ){
                        if( hull.back().b >= ell.b ) return;
                        hull.pop_back();
                }
                while( hull.size() >= 2 ){
                        int s = hull.size();
                        ll x = breakpoint( hull[s-2],hull[s-1] );
                        ll y = breakpoint( hull[s-1],ell );
                        if( y > x ) break;
                        hull.pop_back();
                }
                hull.push_back(ell);
        }
        ll bp( int i ){ return i+1 == hull.size() ? +INF : breakpoint( hull[i],hull[i+1] ); }

        int t = 0;
        ll query( ll x ){
                while( t+1 < hull.size() and bp(t) < x ) t++;
                while( t > 0 and bp(t-1) >= x ) t--;
                return hull[t].eval(x);
        }
};
