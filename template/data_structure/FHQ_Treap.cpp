#include<bits/stdc++.h>

using namespace std;

int faq; 

int rnd()
{
    return faq=((faq+123456789)^19260817)|3153151; 
}

class FHQ
{
    private:
        static const int N=1e5+10;
        
        struct Node
        {
            int ls,rs;
            int key;

            int val,siz;


            Node():ls(0),rs(0),key(0),val(0),siz(0){}
            Node(int val):ls(0),rs(0),key(rnd()),val(val),siz(1){}
        }nd[N];

        int root,cnt;
    
        void update(int x)
        {
            nd[x].siz=nd[nd[x].ls].siz+nd[nd[x].rs].siz+1;
        }

        void split_val(int now,int val,int &x,int &y)
        {
            if(!now)
            {
                x=y=0;
                return;
            }
            if(val<nd[now].val)
            {
                y=now;
                split_val(nd[now].ls,val,x,nd[y].ls);
            }
            else
            {
                x=now;
                split_val(nd[now].rs,val,nd[x].rs,y);
            }
            update(now);
        }

        int merge(int x,int y)
        {
            if(!x||!y) return x+y;
            if(nd[x].key<nd[y].key)
            {
                nd[x].rs=merge(nd[x].rs,y);
                update(x);
                return x;
            }
            else
            {
                nd[y].ls=merge(x,nd[y].ls);
                update(y);
                return y;
            }
        }

        int findKth(int now,int k)
        {
            if(nd[nd[now].ls].siz>=k) return findKth(nd[now].ls,k);
            if(nd[nd[now].ls].siz==k-1) return now;
            else return findKth(nd[now].rs,k-nd[nd[now].ls].siz-1);
        }
    public:
        FHQ():root(0),cnt(0){}

        void insert(int val)
        {
            int x,y;
            split_val(root,val,x,y);
            nd[++cnt]=Node(val);
            root=merge(merge(x,cnt),y);
        }

        void remove(int val)
        {
            int x,y,z;
            split_val(root,val,x,z);
            split_val(x,val-1,x,y);
            y=merge(nd[y].ls,nd[y].rs);
            root=merge(merge(x,y),z);
        }

        int queryrank(int val)
        {
            int x,y;
            split_val(root,val-1,x,y);
            int res=nd[x].siz+1;
            root=merge(x,y);
            return res;
        }

        int querynum(int rak)
        {
             return nd[findKth(root,rak)].val;
        }

        int querypre(int val)
        {
            int x,y;
            split_val(root,val-1,x,y);
            int res=findKth(x,nd[x].siz);
            root=merge(x,y);
            return nd[res].val;
        }

        int querynxt(int val)
        {
            int x,y;
            split_val(root,val,x,y);
            int res=findKth(y,1);
            root=merge(x,y);
            return nd[res].val;
        }
}s;
