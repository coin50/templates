int I = INT_MAX;
auto f = [&](int x,int y){ return min(x,y); };

int racc = I;
vector<int> front;
vector<int> back = {I};
auto query = [&](){ return f(back.back(),racc); };
auto push = [&](int x){ front.push_back(x); racc = f(racc,x); };
auto pop = [&](){
        if( back.size() == 1 ){
                int lacc = I;
                while( front.size() ){
                        int v = front.back(); front.pop_back();
                        lacc = f(v,lacc);
                        back.push_back(lacc);
                }
                racc = I;
        }
        back.pop_back();
};
