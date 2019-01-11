#include<bits/stdc++.h>

using namespace std;

const int inf=0x3f3f3f3f;

class MaxFlow
{
    private:
        struct Edge
        {
            int to,nxt,val;

            Edge():nxt(-1){}
            Edge(int to,int nxt,int val):to(to),nxt(nxt),val(val){}

            ~Edge(){}
        }e[500010];
        int head[10010],cnt;

        void addedge(int u,int v,int val)
        {
            e[++cnt]=Edge(v,head[u],val);
            head[u]=cnt;
        }

        queue<int>q;
        int dpth[10010];
        bool bfs(int s,int t)
        {
            memset(dpth,0,sizeof(dpth));
            q.push(s);
            dpth[s]=1;
            while(!q.empty())
            {
                int now=q.front();
                q.pop();
                for(int i=head[now];~i;i=e[i].nxt)
                {
                    int vs=e[i].to,valn=e[i].val;
                    if(dpth[vs]||!valn) continue;
                    dpth[vs]=dpth[now]+1;
                    q.push(vs);
                }
            }
            return dpth[t];
        }

        int dfs(int now,int fl,int t)
        {
            if(now==t||fl==0)
            {
                return fl;
            }
            int res=0;
            for(int i=head[now];~i;i=e[i].nxt)
            {
                int vs=e[i].to;
                if(dpth[now]!=dpth[vs]-1||!e[i].val) continue;
                int tmp=dfs(vs,min(fl-res,e[i].val),t);
                if(!tmp)
                {
                    dpth[vs]=0;
                }
                res+=tmp;
                e[i].val-=tmp;
                e[i^1].val+=tmp;
                if(res==fl) break;
            }
            return res;
        }

    public:
        MaxFlow(){}

        ~MaxFlow(){}

        void insedge(int u,int v,int val)
        {
            addedge(u,v,val);
            addedge(v,u,0);
        }

        int dinic(int s,int t)
        {
            int res=0;
            while(bfs(s,t))
            {
                res+=dfs(s,inf,t);
            }
            return res;
        }

        void init()
        {
            memset(head,-1,sizeof(head));
            cnt=-1;
        }
}a;

int main()
{
    int n,m,s,t;
    ios::sync_with_stdio(0);
    cin.tie(0) ,cout.tie(0);
    cin>>n>>m>>s>>t;
    a.init();
    for(int i=1;i<=m;i++)
    {
        int u,v,val;
        cin>>u>>v>>val;
        a.insedge(u,v,val);
    }
    cout<<a.dinic(s,t)<<endl;
}
