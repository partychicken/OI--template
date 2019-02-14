class PA
{
    private:
        struct Node
        {
            int len;
            int ptr[26],fail;
            Node(int len=0):len(len),fail(0)
            {
                memset(ptr,0,sizeof(ptr));
            }
        }nd[100010];
        int size,cnt;
        char s[100010];

        int getfail(int x)
        {
            while(s[size-nd[x].len-1]!=s[size])
            {
                x=nd[x].fail;
            }
            return x;
        }

    public:
        int cur;
        PA():size(0),cnt(0),cur(0)
        {
            nd[cnt]=Node(0);
            nd[cnt].fail=1;
            nd[++cnt]=Node(-1);
            nd[cnt].fail=0;
            s[0]='$';
        }

        void extend(char c)
        {
            s[++size]=c;
            int now=getfail(cur);
            if(!nd[now].ptr[c-'a'])
            {
                int tmp=++cnt;
                nd[tmp]=Node(nd[now].len+2);
                nd[tmp].fail=nd[getfail(nd[now].fail)].ptr[c-'a'];
                nd[now].ptr[c-'a']=tmp;
            }
            cur=nd[now].ptr[c-'a'];
        }

        int qlen()
        {
            return nd[cur].len;
        }
}A,B;
