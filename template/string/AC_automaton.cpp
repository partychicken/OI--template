class ACAM
{
    private:
        struct Node
        {
            int ptr[26];
            int fail;

            int cnt;

            Node():fail(0),cnt(0)
            {
                memset(ptr,0,sizeof(ptr));
            }
        }nd[1000010];
        int cnt;

        queue<int>q;

    public:
        ACAM():cnt(0){}

        void insert(string s)
        {
            int len=s.size(),now=0;
            for(int i=0;i<len;i++)
            {
                int x=s[i]-'a';
                if(!nd[now].ptr[x])
                {
                    nd[now].ptr[x]=++cnt;
                }
                now=nd[now].ptr[x];
            }
            nd[now].cnt++;
        }

        void build()
        {
            for(int i=0;i<26;i++)
            {
                if(nd[0].ptr[i])
                {
                    nd[nd[0].ptr[i]].fail=0;
                    q.push(nd[0].ptr[i]);
                }
            }
            while(!q.empty())
            {
                int now=q.front();
                q.pop();
                for(int i=0;i<26;i++)
                {
                    if(nd[now].ptr[i])
                    {
                        nd[nd[now].ptr[i]].fail=nd[nd[now].fail].ptr[i];
                        q.push(nd[now].ptr[i]);
                    }
                    else
                    {
                        nd[now].ptr[i]=nd[nd[now].fail].ptr[i];
                    }
                }
            }
        }

        int query(string s)
        {
            int now=0,ans=0;
            int len=s.size();
            for(int i=0;i<len;i++)
            {
                int x=s[i]-'a';
                now=nd[now].ptr[x];
                for(int p=now;p&&~nd[p].cnt;p=nd[p].fail)
                {
                    ans+=nd[p].cnt;
                    nd[p].cnt=-1;
                }
            }
            return ans;
        }
}A;
