struct SAM
{
    struct Node
    {
        int link,ptr[26];
        int len;

        Node():link(0),len(0)
        {
            memset(ptr,0,sizeof(ptr));
        }

        Node(int link,int len):link(link),len(len)
        {
            memset(ptr,0,sizeof(ptr));
        }
    }nd[100010];
    int cnt,last;

    SAM():cnt(1),last(1){}

    void extend(int x)
    {
        int now=++cnt;
        nd[now].len=nd[last].len+1;
        int p=last;
        while(p&&!nd[p].ptr[x])
        {
            nd[p].ptr[x]=now;
            p=nd[p].link;
        }
        if(!p)
        {
            nd[now].link=1;
        }
        else
        {
            int q=nd[p].ptr[x];
            if(nd[p].len+1==nd[q].len)
            {
                nd[now].link=q;
            }
            else
            {
                int clone=++cnt;
                nd[clone]=Node(nd[q].link,nd[p].len+1);
                memcpy(nd[clone].ptr,nd[q].ptr,sizeof(nd[clone].ptr));
                while(p&&nd[p].ptr[x]==q)
                {
                    nd[p].ptr[x]=clone;
                    p=nd[p].link;
                }
                nd[q].link=nd[now].link=clone;
            }
        }
        last=now;
    }

    int tax[100010],topo[100010];

    void gettop()
    {
        for(int i=1;i<=cnt;i++)
        {
            tax[nd[i].len]++;
        }
        for(int i=1;i<=cnt;i++)
        {
            tax[i]+=tax[i-1];
        }
        for(int i=1;i<=cnt;i++)
        {
            topo[tax[nd[i].len]--]=i;
        }
    }
}A;
