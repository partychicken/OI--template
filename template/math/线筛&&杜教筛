#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

int prime[5000010];
bool is_prime[5000010];

ll mu[5000010],phi[5000010];

void init()
{
    memset(is_prime,1,sizeof(is_prime));
    int cnt=0;
    is_prime[1]=0;
    mu[1]=1;
    phi[1]=1;
    for(int i=2;i<=5000000;i++)
    {
        if(is_prime[i])
        {
            prime[++cnt]=i;
            mu[i]=-1;
            phi[i]=i-1;
        }
        for(int j=1;j<=cnt&&i*prime[j]<=5000000;j++)
        {
            is_prime[i*prime[j]]=0;
            if(i%prime[j])
            {
                mu[i*prime[j]]=-mu[i];
                phi[i*prime[j]]=phi[i]*phi[prime[j]];
            }
            else
            {
                mu[i*prime[j]]=0;
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
        }
    }
    for(int i=1;i<=5000000;i++)
    {
        mu[i]+=mu[i-1];
        phi[i]+=phi[i-1];
    }
}

unordered_map<int,ll>summu,sumphi;

ll s_phi(int n)
{
    if(n<=5000000) return phi[n];
    if(sumphi[n]) return sumphi[n];
    ll ans=0;
    for(int l=2,r;r<2147483647&&l<=n;l=r+1)
    {
        r=n/(n/l);
        ans+=(r-l+1)*s_phi(n/l);
    }
    return sumphi[n]=(ull)n*(n+1ll)/2ll-ans;
}

ll s_mu(int n)
{
    if(n<=5000000) return mu[n];
    if(summu[n]) return summu[n];
    ll ans=0;
    for(int l=2,r;r<2147483647&&l<=n;l=r+1)
    {
        r=n/(n/l);
        ans+=(r-l+1)*s_mu(n/l);
    }
    return summu[n]=1ll-ans;
}
