#include<bits/stdc++.h>

namespace Poly
{
    const int mod=998244353;
    const int g=3;

    int l,N,*r,*A,*B,*C,Size;

    void Make(int &x) 
    {
        if(x>=mod) 
        {
            x-=mod;
        }
    }

    int Kasumi(int a,int b) 
    {
        int res=1,base=a;
        while (b) 
        {
            if(b&1) 
            {
                res=1ll*res*base%mod;
            }
            base=1ll*base*base%mod;
            b >>= 1;
        }
        return res;
    }
        
    void NTT(int *a,int op) 
    {
        for(register int i=0;i<N;i++) 
        {
            if(i<r[i]) 
            {
                std::swap(a[i],a[r[i]]);
            }
        }
        for(register int i=1;i<N;i<<=1) 
        {
            int one=Kasumi(g,(mod-1) / (i<<1));
            if(op==-1) 
            {
                one=Kasumi(one,mod-2);
            }
            for(register int j=0;j<N;j+=i<<1) 
            {
                for(register int len=0,w=1;len<i;len++,w=1ll*w*one%mod) 
                {
                    int x=a[j+len],y=1ll*w*a[i+j+len]%mod;
                    Make(a[j+len]=x+y);
                    Make(a[i+j+len]=x+mod-y);
                }
            }
        }
        if(op==-1) 
        {
            for(register int i=0,inv=Kasumi(N,mod-2);i<N;i++) 
            {
                a[i]=1ll*a[i]*inv%mod;
            }
        }
    }
    
    class Polynomial
    {
        private :
            int *a;

            Polynomial InvMul(const Polynomial &x) 
            {
                Polynomial res;
                res.max=N;
                res.a=new int[res.max+1];
                
                r=new int[N+1];
                r[0]=0;
                for(register int i=0;i<N;i++) 
                {
                    r[i]=r[i>>1]>>1|(i&1)<<(l-1);
                }
                
                A=new int[N+1],B=new int[N+1];
                memset(A,0,(N+1)<<2);
                memset(B,0,(N+1)<<2);
                memcpy(A,a,(std::min(max,N-1)+1)<<2);
                memcpy(B,x.a,(std::min(x.max,N-1)+1)<<2);
                
                NTT(A,1),NTT(B,1);
                for(register int i=0;i<N;i++) 
                {
                    A[i]=1ll*B[i]*(2+mod-1ll*A[i]*B[i]%mod)%mod;
                }
                NTT(A,-1);

                memcpy(res.a,A,(res.max+1)<<2);
                
                delete[] A,delete[] B,delete[] r;
                return res;
            }

            Polynomial Reverse() 
            {
                Polynomial res;
                res=*this;
                std::reverse(res.a,res.a+1+max);
                return res;
            }

            Polynomial Direv() 
            { 
                Polynomial res;
                res.max=max-1;
                res.a=new int[res.max+1];
                for(register int i=1;i<=max;i++) 
                {
                    res.a[i-1]=1ll*a[i]*i%mod;
                }
                return res;
            }

            Polynomial Inrev() 
            { 
                Polynomial res;
                res.max=max+1;
                res.a=new int[res.max+1];
                res.a[0]=0;
                for(register int i=1;i<=max;i++) 
                {
                    res.a[i]=1ll*a[i-1]*Kasumi(i,mod-2)%mod;
                }
                return res;
            }
        
        public :
            int max;

            Polynomial(int x=0):max(0) 
            {
                a=new int[1];
                a[0]=x;
            }

            int& operator [](int x) 
            {
                return (this->a[x]);
            }

            void Init(int m) 
            {
                delete[] a;
                a=new int[(max=m)+1];
                memset(a,0,(max+1)<<2);
            }

            void Init(int *x,int m) 
            {
                delete[] a;
                a=new int[(max=m)+1];
                memcpy(a,x,(max+1)<<2);
            }
        
            int operator [](int pos) const 
            {
                if(pos>max) 
                {
                    return 0;
                }
                return this->a[pos];
            }

            Polynomial operator*(const Polynomial &x) const 
            {
                Polynomial res;
                res.max=max+x.max;
                res.a=new int[res.max+1];
                for(l=0,N=1;N<=res.max;N<<=1) 
                {
                    l++;
                }
                r=new int[N+1];
                r[0]=0;
                for(register int i=0;i<N;i++) 
                {
                    r[i]=r[i>>1]>>1|(i&1)<<(l-1);
                }
                A=new int[N+1],B=new int[N+1];
                memset(A,0,(N+1)<<2),memset(B,0,(N+1)<<2);
                memcpy(A,a,(max+1)<<2),memcpy(B,x.a,(x.max+1)<<2);
                NTT(A,1),NTT(B,1);
                for(register int i=0;i<N;i++) 
                {
                    A[i]=1ll*A[i]*B[i]%mod;
                }
                NTT(A,-1);
                memcpy(res.a,A,(res.max+1)<<2);
                delete[] A,delete[] B,delete[] r;
                return res;
            }

            Polynomial operator*(int x) const 
            {
                Polynomial res;
                res.max=max;
                res.a=new int[res.max+1];
                for(register int i=0;i<=res.max;i++) 
                {
                    res.a[i]=1ll*x*a[i]%mod;
                }
                return res;
            }

            Polynomial operator+(const Polynomial &x) const 
            {
                Polynomial res;
                res.max=std::max(max,x.max);
                res.a=new int[res.max+1];
                for(register int i=0;i<=res.max;i++) 
                {
                    res.a[i]=0;
                    if(i<=max) 
                    {
                        res.a[i]=a[i];
                    }
                    if(i<=x.max) 
                    {
                        Make(res.a[i]+=x.a[i]);
                    }
                }
                return res;
            }

            Polynomial operator-(const Polynomial &x) const 
            {
                Polynomial res;
                res.max=std::max(max,x.max);
                res.a=new int[res.max+1];
                for(register int i=0;i<=res.max;i++) 
                {
                    res.a[i]=0;
                    if(i<=max) 
                    {
                        res.a[i]=a[i];
                    }
                    if(i<=x.max) 
                    {
                        Make(res.a[i]+=mod-x.a[i]);
                    }
                }
                return res;
            }

            typedef std::pair<Polynomial,Polynomial> DivAns;

            DivAns operator / (Polynomial &x) 
            {
                Polynomial res,rem,tmp;
                int p=max-x.max+1;
                res=(Reverse()%p*((x.Reverse())%p).Inv()%p).Reverse();
                tmp=x*res;
                rem.max=x.max-1;
                rem.a=new int[rem.max+1];
                for(register int i=0;i<=rem.max;i++) 
                {
                    rem.a[i]=a[i];
                    if(i<=tmp.max) 
                    {
                        Make(rem.a[i]+=mod-tmp.a[i]);
                    }
                }
                return std::make_pair(res,rem);
            }

            Polynomial operator%(int x) const 
            {
                Polynomial res;
                res.max=x-1;
                res.a=new int[res.max+1];
                memset(res.a,0,(res.max+1)<<2);
                memcpy(res.a,a,(std::min(max,res.max)+1)<<2);
                return res;
            }

            Polynomial& operator=(const Polynomial &x) 
            {
                if(this->a != x.a) 
                {
                    delete[] a;
                }
                a=new int[(max=x.max)+1];
                memcpy(a,x.a,(max+1)<<2);
                return *this;
            }

            Polynomial Inv() 
            {
                Polynomial p[2];
                int now=0,last=1,len=1;
                p[now].max=0,p[now].a=new int(Kasumi(a[0],mod-2));
                for(len=1,N=2,l=1;len<=(max<<1);N<<=1,l++,len<<=1) 
                {
                    std::swap(now,last);
                    p[now]=p[last]*2;
                    p[last]=p[last]*p[last]%(len<<1)*(*this%(len<<1))%(len<<1);
                    p[now]=p[now]-p[last];
                    
                }
                return p[now]%(max+1);
            }

            Polynomial Ln() 
            {
                return (Direv()*Inv()%(max+1)).Inrev()%(max+1);
            }

            Polynomial Exp() 
            {
                Polynomial p[2];
                int now=0,last=1;
                p[now]=Polynomial(1);
                for(register int len=1;len<=(max<<1);len<<=1) 
                {
                    std::swap(now,last);
                    p[now]=p[last];
                    p[last]=p[last]*(p[last].Ln()-(*this%(len<<1)))%(len<<1);
                    p[now]=p[now]-p[last];
                    
                }
                return p[now]%(max+1);
            }

            void Print() 
            {
                for(register int i=0;i<=max;i++) 
                {
                    printf("%d ",a[i]);
                }
                putchar('\n');
            }

            Polynomial Sqrt() 
            {
                Polynomial p[2];
                int now=0,last=1,len=1;
                p[now]=Polynomial(this->a[0]);
                for(len=1,N=2,l=1;len<=(max<<1);N<<=1,l++,len<<=1) 
                {
                    std::swap(now,last);
                    p[now]=(p[last]*2).Inv();
                    p[last]=p[last]*p[last]%(len<<1);
                    p[now]=(*this%(len<<1)+p[last])*p[now]%(len<<1);
                }
                return p[now]%(max+1);
            }
    };
    typedef std::pair<Polynomial,Polynomial> DivAns;
}

using namespace std;
using namespace Poly;
