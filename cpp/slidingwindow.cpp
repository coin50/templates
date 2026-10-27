using T = ll;
auto f = [&](ll x,ll y){ return max(x,y); };
T defT = LLONG_MIN / 2;

T racc = defT;
vector<T> front;
vector<T> back = {defT};
auto query = [&](){ return f(back.back(),racc); };
auto push = [&](T x){ front.push_back(x); racc = f(racc,x); };
auto pop = [&](){
        if( back.size() == 1 ){
                T lacc = defT;
                while( front.size() ){
                        T v = front.back(); front.pop_back();
                        lacc = f(v,lacc);
                        back.push_back(lacc);
                }
                racc = defT;
        }
        back.pop_back();
};
