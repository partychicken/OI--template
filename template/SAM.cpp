#include<bits/stdc++.h>

using namespace std;

struct Node
{
    int len,link;
    map<char,int>nxt;
}nd[3000010];

int sz(0),last(1);

void init()
{
    nd[1].len=0;
    nd[1].link=0;
    ++sz;
}

string s;

void extend(char c)
{
    int cur=++sz;
    nd[cur].len=nd[last].len+1;
    int p=last;
    while(p&&!nd[p].nxt.count(c))
    {
        nd[p].nxt[c]=cur;
        p=nd[p].link;
    }
    if(p==0)
    {
        nd[cur].link=1;
    }
    else
    {
        int q=nd[p].nxt[c];
        if(nd[p].len+1==nd[q].len)
        {
            nd[cur].link=q;
        }
        else
        {
            int clone=++sz;
            nd[clone].len=nd[p].len+1;
            nd[clone].nxt=nd[q].nxt;
            nd[clone].link=nd[q].link;
            while(p&&nd[p].nxt[c]==q)
            {
                nd[p].nxt[c]=clone;
                p=nd[p].link;
            }
            nd[q].link=nd[cur].link=clone;
        }
    }
    last=cur;
}
