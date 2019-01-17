// luogu-judger-enable-o2
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll qpow(ll a,ll b,ll p)
{
    ll res=1;
    for(;b;b>>=1)
    {
        if(b&1) res=res*a%p; 
        a=a*a%p;
    }
    return res;
}

unordered_map<ll,ll>has;
ll BSGS(ll a,ll b,ll p)
{
    if(b==1) return 0;
    ll cnt=0,d,k=1;
    while((d=__gcd(a,p))^1)
    {
        if(b%d) return -1;
        b/=d;
        p/=d;
        ++cnt;
        k*=a/d;
        k%=p;
        if(k==b) return cnt;
    }
    has.clear();
    ll t=(ll)sqrt(double(p))+1;
    ll bas=1;
    for(ll j=0;j<t;j++)
    {
        ll val=b*bas%p;
        val=b*qpow(a,j,p)%p;
        bas*=a;
        bas%=p;
        has[val]=j;
    }
    k=bas*k%p;
    for(ll i=1;i<=t;i++)
    {
        ll val=k;
        ll j=has.find(val)==has.end()?-1:has[val];
        if(j>=0&&i*t-j>=0) return i*t-j+cnt;
        k=k*bas%p;
    }
    return -1;
}
