struct SA
{

    int rak[500010],sa[500010],tp[500010];
    int tax[500010],a[500010];

    void Qsort()
    {
        for(int i=0;i<=m;i++)
        {
            tax[i]=0;
        }
        for(int i=1;i<=n;i++)
        {
            tax[rak[i]]++;
        }
        for(int i=1;i<=m;i++)
        {
            tax[i]+=tax[i-1];
        }
        for(int i=n;i>=1;i--)
        {
            sa[tax[rak[tp[i]]]--]=tp[i];
        }
    }

    void getSA()
    {
        m=127;
        for(int i=1;i<=n;i++)
        {
            rak[i]=a[i];
            tp[i]=i;
        }
        Qsort();
        for(int w=1,p=1;p<n;m=p,w<<=1)
        {
            p=0;
            for(int i=1;i<=w;i++)
            {
                tp[++p]=n-w+i;
            }
            for(int i=1;i<=n;i++)
            {
                if(sa[i]>w)
                {
                    tp[++p]=sa[i]-w;
                }
            }
            Qsort();
            swap(rak,tp);
            rak[sa[1]]=p=1;
            for(int i=2;i<=n;i++)
            {
                rak[sa[i]]=(tp[sa[i-1]]==tp[sa[i]]&&tp[sa[i-1]+w]==tp[sa[i]+w])?p:++p;
            }
        }
    }

    int height[500010];

    void geth()
    {
        int k=0;
        for(int i=1;i<=n;i++)
        {
            rak[sa[i]]=i;
        }
        for(int i=1;i<=n;i++)
        {
            if(rak[i]==1) continue;
            if(k) --k;
            int j=sa[rak[i]-1];
            while(j+k<=n&&i+k<=n&&a[i+k]==a[j+k])
            {
                k++;
            }
            height[rak[i]]=k;
        }
    }

    int minn[500010][22];

    void pre()
    {
        getSA();
        geth();
        for(int i=1;i<=n;i++)
        {
            minn[i][0]=height[i];
        }
        for(int j=1;(1<<j)<=n;j++)
        {
            for(int i=1;(i+(1<<j)-1)<=n;i++)
            {
                minn[i][j]=min(minn[i][j-1],minn[i+(1<<j-1)][j-1]);
            }
        }
    }

    int lcp(int a,int b)
    {
        a=rak[a];
        b=rak[b];
        if(a>b)
        {
            swap(a,b);
        }
        a++;
        int k=log2(b-a+1);
        return min(minn[a][k],minn[b-(1<<k)+1][k]);
    }
}A;
