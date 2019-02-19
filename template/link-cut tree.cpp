#include<bits/stdc++.h>

using namespace std;

struct LCT
{
    int siz[200010],fa[200010];
    int child[200010][2];
    bool rev[200010];

    void update(int x)
    {
        siz[x]=child[x][0][siz]+child[x][1][siz]+1;
    }

    void pushdown(int x)
    {
        if(rev[x])
        {
            swap(child[x][0],child[x][1]);
            child[x][0][rev]^=1;
            child[x][1][rev]^=1;
            rev[x]=0;
        }
    }

    bool isroot(int x)
    {
        return child[fa[x]][0]!=x&&child[fa[x]][1]!=x;
    }

    void rotate(int now)
    {
        int nfa=fa[now],anc=fa[nfa];
        int _id=child[nfa][0]==now,id=_id^1;
        if(!isroot(nfa))
        {
            child[anc][child[anc][0]!=nfa]=now;
        }
        fa[now]=anc;
        fa[nfa]=now;
        fa[child[now][_id]]=nfa;
        child[nfa][id]=child[now][_id];
        child[now][_id]=nfa;
        update(nfa);
        update(now);
    }

    int st[200010];

    void splay(int now)
    {
        int cnt=0;
        st[++cnt]=now;
        for(int x=now;!isroot(x);x=fa[x])
        {
            st[++cnt]=fa[x];
        }
        while(cnt) pushdown(st[cnt--]);
        while(!isroot(now))
        {
            int nfa=fa[now],anc=fa[nfa];
            if(!isroot(nfa))
            {
                if((nfa==child[anc][0])^(now==child[nfa][0])) rotate(now);
                else rotate(nfa);
            }
            rotate(now);
        }
    }

    void access(int now)
    {
        for(int last=0;now;now=fa[now])
        {
            splay(now);
            child[now][1]=last;
            update(now);
            last=now;
        }
    }

    void makeroot(int now)
    {
        access(now);
        splay(now);
        rev[now]^=1;
    }

    void link(int x,int y)
    {
        makeroot(x);
        fa[x]=y;
    }

    void cut(int x,int y)
    {
        makeroot(x);
        access(y);
        splay(y);
        child[y][0]=0;
        fa[x]=0;
        update(y);
    }

    int query(int x,int y)
    {
        makeroot(x);
        access(y);
        splay(y);
        return siz[y];
    }
}s;
