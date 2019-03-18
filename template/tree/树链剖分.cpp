#include<bits/stdc++.h>

using namespace std;

struct Edge
{
    int to,nxt;

    Edge(){}
    Edge(int to,int nxt):to(to),nxt(nxt){}
}e[100010];
int head[30010],cnt;

void addedge(int u,int v)
{
    e[++cnt]=Edge(v,head[u]);
    head[u]=cnt;
}

int fa[30010],dpth[30010],siz[30010],son[30010];
int top[30010];
int id[30010],idx;
void dfs1(int now)
{
    siz[now]=1;
    int maxx=0;
    for(int i=head[now];i;i=e[i].nxt)
    {
        int vs=e[i].to;
        if(vs==fa[now]) continue;
        fa[vs]=now;
        dpth[vs]=dpth[now]+1;
        dfs1(vs);
        siz[now]+=siz[vs];
        if(siz[vs]>maxx)
        {
            son[now]=vs;
            maxx=siz[vs];
        }
    }
}

void dfs2(int now,int ntop)
{
    top[now]=ntop;
    id[now]=++idx;
    if(!son[now]) return;
    dfs2(son[now],ntop);
    for(int i=head[now];i;i=e[i].nxt)
    {
        int vs=e[i].to;
        if(vs==fa[now]||vs==son[now]) continue;
        dfs2(vs,vs);
    }
}
