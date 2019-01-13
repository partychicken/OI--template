#include<bits/stdc++.h>

using namespace std;

const int N=100010;

int wd;

struct Point
{
    int x[2],w;

    bool operator<(const Point &b)const
    {
        return x[wd]<b.x[wd];
    }
};

class KDT
{
    private:
        int top,cur,rub[N];

        Point p[N];

        struct Node
        {
            int mn[2],mx[2],sum,ls,rs,siz;
            Point tp;
        }tr[N];

        int newNode()
        {
            if(top)
            {
                return rub[top--];
            }
            else
            {
                return ++cur;
            }
        }

        void up(int k)
        {
            int l=tr[k].ls,r=tr[k].rs;
            for(int i=0;i<=1;i++)
            {
                tr[k].mn[i]=tr[k].mx[i]=tr[k].tp.x[i];
                if(l)
                {
                    tr[k].mn[i]=min(tr[k].mn[i],tr[l].mn[i]);
                    tr[k].mx[i]=max(tr[k].mx[i],tr[l].mx[i]);
                }
                if(r)
                {
                    tr[k].mn[i]=min(tr[k].mn[i],tr[r].mn[i]);
                    tr[k].mx[i]=max(tr[k].mx[i],tr[r].mx[i]);
                }
            }
            tr[k].sum=tr[l].sum+tr[k].tp.w+tr[r].sum;
            tr[k].siz=tr[l].siz+tr[r].siz+1;
        }

        int build(int l,int r,int ww)
        {
            if(l>r)
            {
                return 0;
            }
            int mid=l+r>>1;
            int k=newNode();
            wd=ww;
            nth_element(p+l,p+mid,p+r+1);
            tr[k].tp=p[mid];
            tr[k].ls=build(l,mid-1,ww^1);
            tr[k].rs=build(mid+1,r,ww^1);
            up(k);
            return k;
        }

        void pia(int &k,int num)
        {
            if(tr[k].ls)
            {
                pia(tr[k].ls,num);
            }
            p[tr[tr[k].ls].siz+num+1]=tr[k].tp;
            rub[++top]=k;
            if(tr[k].rs)
            {
                pia(tr[k].rs,num+tr[tr[k].ls].siz+1);
            }
        }

        void check(int &k,int ww)
        {
            if(tr[k].siz*0.75<tr[tr[k].ls].siz||tr[k].siz*0.75<tr[tr[k].rs].siz)
            {
                pia(k,0);
                k=build(1,tr[k].siz,ww);
            }
        }

        bool in(int x,int y,int a,int b,int c)
        {
            return a*x+b*y<c;
        }

        bool out(int x,int y,int a,int b,int c)
        {
            return a*x+b*y>=c;
        }
    public:
        int root;

        void ins(int &k,Point tmp,int ww)
        {
            if(!k)
            {
                k=newNode();
                tr[k].ls=tr[k].rs=0;
                tr[k].tp=tmp;
                up(k);
                return;
            }
            if(tmp.x[ww]<=tr[k].tp.x[ww])
            {
                ins(tr[k].ls,tmp,ww^1);
            }
            else
            {
                ins(tr[k].rs,tmp,ww^1);
            }
            up(k);
            check(k,ww);
        }

        int query(int k,int a,int b,int c)
        {
            if(!k)
            {
                return 0;
            }
            int res=0;
            int tmp=0;
            tmp+=in(tr[k].mx[0],tr[k].mx[1],a,b,c);
            tmp+=in(tr[k].mn[0],tr[k].mx[1],a,b,c);
            tmp+=in(tr[k].mx[0],tr[k].mn[1],a,b,c);
            tmp+=in(tr[k].mn[0],tr[k].mn[1],a,b,c);
            if(!tmp)
            {
                return 0;
            }
            if(tmp==4)
            {
                return tr[k].sum;
            }
            if(in(tr[k].tp.x[0],tr[k].tp.x[1],a,b,c))
            {
                res+=tr[k].tp.w;
            }
            res+=query(tr[k].ls,a,b,c)+query(tr[k].rs,a,b,c);
            return res;
        }
}a;

main()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        int x,y,w;
        cin>>x>>y>>w;
        a.ins(a.root,(Point){x,y,w},0);
    }
    for(int i=1;i<=m;i++)
    {
        int sa,sb,sc;
        cin>>sa>>sb>>sc;
        cout<<a.query(a.root,sa,sb,sc)<<'\n';
    }
}
