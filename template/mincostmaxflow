class Mincost
{
    private:
        static const int M=5010;
        static const int N=110;
        static const int inf=0x3f3f3f3f;

        struct Edge
        {
            int to,nxt,val,cost;

            Edge(){}
            Edge(int to,int nxt,int val,int cost):to(to),nxt(nxt),val(val),cost(cost){}
        }e[M*2];
        int head[N],cnt;
        int ans;

        void addedge(int u,int v,int val,int cost)
        {
            e[++cnt]=Edge(v,head[u],val,cost);
            head[u]=cnt;
        }

        int dis[N],pre[N],flow[N];
        bool vis[N];
        queue<int>q;

        bool SPFA(int s,int t)
        {
            memset(dis,0x3f,sizeof(dis));
            memset(pre,0,sizeof(pre));
            memset(flow,0x3f,sizeof(flow));
            dis[s]=0;
            q.push(s);
            vis[s]=1;
            while(!q.empty())
            {
                int now=q.front();
                q.pop();
                vis[now]=0;
                for(int i=head[now];i;i=e[i].nxt)
                {
                    if(!e[i].val) continue;
                    int vs=e[i].to,valn=e[i].cost;
                    if(dis[now]+valn<dis[vs])
                    {
                        dis[vs]=dis[now]+valn;
                        flow[vs]=min(flow[now],e[i].val);
                        pre[vs]=i;
                        if(!vis[vs])
                        {
                            q.push(vs);
                            vis[vs]=1;
                        }
                    }
                }
            }
            return pre[t];
        }

    public:
        Mincost():cnt(1),ans(0){}
        
        void insedge(int u,int v,int val,int cost)
        {
            addedge(u,v,val,cost);
            addedge(v,u,0,-cost);
        }

        int MCMF(int s,int t)
        {
            int res=0;
            while(SPFA(s,t))
            {
                int now=t,fl=flow[t];
                res+=fl;
                ans+=fl*dis[t];
                while(now!=s)
                {
                    e[pre[now]].val-=fl;
                    e[pre[now]^1].val+=fl;
                    now=e[pre[now]^1].to;
                }
            }
            return res;
        }

        int mincost(int s=0,int t=0)
        {
            if(ans) return ans;
            else
            {
                MCMF(s,t);
                return ans;
            }
        }
}A;
