struct Node
{
    int child[2];
    long long val,sum;
    int siz;
}nd[100010];
int root[100010];

int merge(int u,int v)
{
    if(!(u&&v)) return u|v;
    int x=rand()&1,p=nd[u].val>nd[v].val?u:v;
    nd[p].child[x]=merge(nd[p].child[x],u+v-p);
    nd[p].siz=nd[nd[p].child[0]].siz+nd[nd[p].child[1]].siz+1;
    nd[p].sum=nd[nd[p].child[0]].sum+nd[nd[p].child[1]].sum+nd[p].val;
    return p;
}

void pop(int &now)
{
    now=merge(nd[now].child[0],nd[now].child[1]);
}
