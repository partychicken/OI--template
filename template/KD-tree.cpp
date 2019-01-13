#include<bits/stdc++.h>

using namespace std;

const int N=100010;

int wd;

class KDT
{
    private:
        int top,cur,rub[N];

        struct Point
        {
            int x[2],w;

            bool operator<(const Point &b)const
            {
                return x[wd]<b.x[wd];
            }
        }p[N];

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

        bool in(int x1,int y1,int x2,int y2,int xx1,int yy1,int xx2,int yy2)
        {
            return (xx1>=x1&&xx2<=x2&&yy1>=y1&&yy2<=y2);
        }

        bool out(int x1,int y1,int x2,int y2,int xx1,int yy1,int xx2,int yy2)
        {
            return (x1>xx2||x2<xx1||y1>yy2||y2<yy1);
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

        int query(int k,int x1,int y1,int x2,int y2)
        {
            if(!k)
            {
                return 0;
            }
            int res=0;
            if(in(x1,y1,x2,y2,tr[k].mn[0],tr[k].mn[1],tr[k].mx[0],tr[k].mx[1]))
            {
                return tr[k].sum;
            }
            if(out(x1,y1,x2,y2,tr[k].mn[0],tr[k].mn[1],tr[k].mx[0],tr[k].mx[1]))
            {
                return 0;
            }
            if(in(x1,y1,x2,y2,tr[k].tp.x[0],tr[k].tp.x[1],tr[k].tp.x[0],tr[k].tp.x[1]))
            {
                res+=tr[k].tp.w;
            }
            res+=query(tr[k].ls,x1,y1,x2,y2)+query(tr[k].rs,x1,y1,x2,y2);
            return res;
        }
}a;
