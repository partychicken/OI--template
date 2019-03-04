struct Node
{
    struct Tuple
    {
        int l,r,val;

        Tuple(int val):l(inf),r(-inf),val(val){}
        Tuple(int l,int r,int val):l(l),r(r),val(val){}

        Tuple operator+(const Tuple &other)const
        {
            return Tuple(min(l,other.l),max(r,other.r),val+other.val);
        }

        bool operator<(const Tuple &other)const
        {
            return val<other.val;
        }
    };
    Tuple maxright,maxleft,maxmid;
    Tuple minright,minleft,minmid;
    Tuple sum;
    bool rev;

    Node():
        maxright(-inf),
        maxleft(-inf),
        maxmid(-inf),
        minright(inf),
        minleft(inf),
        minmid(inf),
        sum(0),
        rev(0){}

    Node operator+(const Node &other)const
    {
        Node res;
        
        res.sum=sum+other.sum;

        res.maxright=max(other.maxright,maxright+other.sum);
        res.maxleft=max(maxleft,sum+other.maxleft);
        res.maxmid=max(maxmid,max(other.maxmid,maxright+other.maxleft));

        res.minright=min(other.minright,minright+other.sum);
        res.minleft=min(minleft,sum+other.minleft);
        res.minmid=min(minmid,min(other.minmid,minright+other.minleft));

        return res;
    }
};


struct SEG
{
    Node nd[100010<<2];

    void update(int x)
    {
        nd[x]=nd[x<<1]+nd[x<<1|1];
    }

    void reverse(int x)
    {
        swap(nd[x].maxright,nd[x].minright);
        swap(nd[x].maxleft,nd[x].minleft);
        swap(nd[x].maxmid,nd[x].minmid);
        nd[x].maxright.val*=-1;
        nd[x].maxleft.val*=-1;
        nd[x].maxmid.val*=-1;
        nd[x].minright.val*=-1;
        nd[x].minleft.val*=-1;
        nd[x].minmid.val*=-1;
        nd[x].sum.val*=-1;
    }

    void pushdown(int x)
    {
        if(nd[x].rev)
        {
            nd[x<<1].rev^=1;
            reverse(x<<1);
            nd[x<<1|1].rev^=1;
            reverse(x<<1|1);
            nd[x].rev=0;
        }
    }

    void modifynode(int now,int nl,int nr,int pos,int val)
    {
        if(nl==nr)
        {
            nd[now].sum=Node::Tuple(nl,nr,val);
            nd[now].maxright=nd[now].maxleft=nd[now].maxmid=Node::Tuple(nl,nr,val);
            nd[now].minright=nd[now].minleft=nd[now].minmid=Node::Tuple(nl,nr,val);
            return;
        }
        pushdown(now);
        int mid=nl+nr>>1;
        if(pos<=mid) modifynode(now<<1,nl,mid,pos,val);
        else modifynode(now<<1|1,mid+1,nr,pos,val);
        update(now);
    }

    void modifyrange(int now,int nl,int nr,int ql,int qr)
    {
        if(nl>qr||nr<ql) return;
        if(nl>=ql&&nr<=qr) 
        {
            reverse(now);
            nd[now].rev^=1;
            return;
        }
        pushdown(now);
        int mid=nl+nr>>1;
        modifyrange(now<<1,nl,mid,ql,qr);
        modifyrange(now<<1|1,mid+1,nr,ql,qr);
        update(now);
    }

//    Node queryrangemax(int now,int nl,int nr,int ql,int qr)
//    {
//        if(nl>qr||nr<ql) return Node();
//        if(nl>=ql&&nr<=qr) return nd[now];
//        pushdown(now);
//        int mid=nl+nr>>1;
//        return queryrangemax(now<<1,nl,mid,ql,qr)+queryrangemax(now<<1|1,mid+1,nr,ql,qr);
//    }
    Node queryrangemax(int now,int nl,int nr,int ql,int qr)
    {
        if(nl>=ql&&nr<=qr)
        {
            return nd[now];
        }
        pushdown(now);
        int mid=nl+nr>>1;
        if(ql>mid) return queryrangemax(now<<1|1,mid+1,nr,ql,qr);
        else if(qr<=mid) return queryrangemax(now<<1,nl,mid,ql,qr);
        else return queryrangemax(now<<1,nl,mid,ql,mid)+queryrangemax(now<<1|1,mid+1,nr,mid+1,qr);
    }
}seg;
queue<Node>q;
