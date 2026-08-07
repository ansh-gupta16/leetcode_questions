class Solution {
public:
    int A,B,C,D, dimB,dimC,dimD;
    vector<int> minDig;
    int contrib[10][4] = {
        {0,0,0,0},{0,0,0,0},{1,0,0,0},{0,1,0,0},{2,0,0,0},
        {0,0,1,0},{1,1,0,0},{0,0,0,1},{3,0,0,0},{0,2,0,0}
    };
    inline int idx(int a,int b,int c,int d){ return ((a*dimB+b)*dimC+c)*dimD+d; }

    vector<int> greedyFill(int a,int b,int c,int d,int L){
        vector<int> res; res.reserve(L);
        for(int pos=0; pos<L; pos++){
            int remAfter = L-pos-1;
            for(int dig=1; dig<=9; dig++){
                int na=max(a-contrib[dig][0],0), nb=max(b-contrib[dig][1],0);
                int nc=max(c-contrib[dig][2],0), nd=max(d-contrib[dig][3],0);
                if(minDig[idx(na,nb,nc,nd)]<=remAfter){
                    a=na;b=nb;c=nc;d=nd; res.push_back(dig); break;
                }
            }
        }
        return res;
    }

    string smallestNumber(string num, long long t) {
        int a=0,b=0,c=0,d=0; long long tt=t;
        while(tt%2==0){tt/=2;a++;}
        while(tt%3==0){tt/=3;b++;}
        while(tt%5==0){tt/=5;c++;}
        while(tt%7==0){tt/=7;d++;}
        if(tt!=1) return "-1";

        A=a;B=b;C=c;D=d; dimB=B+1; dimC=C+1; dimD=D+1;
        long long sizeL=(long long)(A+1)*(B+1)*(C+1)*(D+1);
        minDig.assign(sizeL, INT_MAX/2);
        minDig[idx(0,0,0,0)]=0;

        for(int ai=0; ai<=A; ai++)
        for(int bi=0; bi<=B; bi++)
        for(int ci=0; ci<=C; ci++)
        for(int di=0; di<=D; di++){
            if(!ai&&!bi&&!ci&&!di) continue;
            int best=INT_MAX/2;
            for(int dig=2; dig<=9; dig++){
                int na=max(ai-contrib[dig][0],0), nb=max(bi-contrib[dig][1],0);
                int nc=max(ci-contrib[dig][2],0), nd=max(di-contrib[dig][3],0);
                if(na==ai&&nb==bi&&nc==ci&&nd==di) continue;
                best=min(best, minDig[idx(na,nb,nc,nd)]+1);
            }
            minDig[idx(ai,bi,ci,di)]=best;
        }

        int n=num.size();

        if(num.find('0')==string::npos){
            int ea=0,eb=0,ec=0,ed=0;
            for(char ch: num){
                int dig=ch-'0';
                ea=min(A,ea+contrib[dig][0]); eb=min(B,eb+contrib[dig][1]);
                ec=min(C,ec+contrib[dig][2]); ed=min(D,ed+contrib[dig][3]);
            }
            if(ea>=A&&eb>=B&&ec>=C&&ed>=D) return num;
        }

        size_t fzPos = num.find('0');
        int maxI = (fzPos==string::npos) ? n-1 : (int)fzPos;

        vector<array<int,4>> remReq(maxI+1);
        remReq[0] = {A,B,C,D};
        for(int i=0;i<maxI;i++){
            int dig=num[i]-'0'; auto &cur=remReq[i];
            remReq[i+1] = { max(cur[0]-contrib[dig][0],0), max(cur[1]-contrib[dig][1],0),
                             max(cur[2]-contrib[dig][2],0), max(cur[3]-contrib[dig][3],0) };
        }

        string answer="";
        for(int i=maxI;i>=0&& answer.empty();i--){
            auto &req_i=remReq[i];
            int dnum=num[i]-'0', remLen=n-i-1;
            for(int cdig=dnum+1; cdig<=9; cdig++){
                int na=max(req_i[0]-contrib[cdig][0],0), nb=max(req_i[1]-contrib[cdig][1],0);
                int nc=max(req_i[2]-contrib[cdig][2],0), nd=max(req_i[3]-contrib[cdig][3],0);
                if(minDig[idx(na,nb,nc,nd)]<=remLen){
                    vector<int> suf=greedyFill(na,nb,nc,nd,remLen);
                    string s=num.substr(0,i)+char('0'+cdig);
                    for(int x:suf) s+=char('0'+x);
                    answer=s; break;
                }
            }
        }
        if(!answer.empty()) return answer;

        int M=minDig[idx(A,B,C,D)];
        int L0=max(n+1, M);
        vector<int> suf=greedyFill(A,B,C,D,L0);
        string s;
        for(int x:suf) s+=char('0'+x);
        return s;
    }
};