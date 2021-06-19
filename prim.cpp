#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<sys/time.h>
#include<time.h>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pr;
const double pi=acos(-1);
#define rep(i,a,n) for(int i=a;i<=n;i++)
#define per(i,n,a) for(int i=n;i>=a;i--)
#define Rep(i,u) for(int i=head[u];i;i=Next[i])
#define clr(a) memset(a,0,sizeof a)
#define pb push_back
#define mp make_pair
#define fi first
#define sc second
ld eps=1e-9;
ll pp=1000000007;
ll inf=2147483647;
#define maxn 20010
#define maxm 20000000
ll mo(ll a,ll pp){if(a>=0 && a<pp)return a;a%=pp;if(a<0)a+=pp;return a;}
ll powmod(ll a,ll b,ll pp){ll ans=1;for(;b;b>>=1,a=mo(a*a,pp))if(b&1)ans=mo(ans*a,pp);return ans;}
ll read(){
    ll ans=0;
    char last=' ',ch=getchar();
    while(ch<'0' || ch>'9')last=ch,ch=getchar();
    while(ch>='0' && ch<='9')ans=ans*10+ch-'0',ch=getchar();
    if(last=='-')ans=-ans;
    return ans;
}
//head 


struct edge
{
    int to,_dis,next;////出边的终点、出边的长度、下一条出边
};//因为是无向图，所以开双倍数组，双倍快乐 
vector<edge> edge(400000000);

int head[maxn],dis[maxn],cnt,n,m,tot,now=1,ans;
//dis数组表示当前点到最小生成树的最短路径 
bool vis[maxn];

inline void add_edge(int from,int to,int value)
{
    edge[++cnt].to=to;
    edge[cnt]._dis=value;
    edge[cnt].next=head[from];
    head[from]=cnt;
}//添加边 

inline int prim()
{
    rep(i,2,n)
        dis[i]=inf;//初始化 
    for(int i=head[1];i;i=edge[i].next)//遍历当前节点的每一条出边 
        dis[edge[i].to]=min(dis[edge[i].to],edge[i]._dis);//重边の处理 
    while(++tot<n)//就是tot<=n-1,因为最小生成树的边数一定等于节点数-1 
    {
        int minn=inf;//初始化min 
        vis[now]=1;//已经到达 
        rep(i,1,n)
            if(!vis[i]&&minn>dis[i])//寻找到最小生成树距离最短的节点 
                minn=dis[i],now=i;//更新 
        ans+=minn;//更新最小生成树 
        for(int i=head[now];i;i=edge[i].next)//遍历每一条出边 
        {
            int to=edge[i].to;
            if(dis[to]>edge[i]._dis&&!vis[to])
                dis[to]=edge[i]._dis;//更新dis数组 
        }
        
    }
    return ans;
}

double get_time(){
	struct timeval tv;
	double t;
	gettimeofday(&tv, (struct timezone *)0);
	t = tv.tv_sec + (double)tv.tv_usec * 1e-6;
	return t;
}

int main()
{
    n=read(),m=read();
    rep(i,1,m)
    {
        int from=read(),to=read(),value=read();
        add_edge(from,to,value);//因为是无向图 
        add_edge(to,from,value);//双倍存储，双倍快乐 
    }
    double td = get_time();
	prim();
	printf("%le\n", get_time() - td);
	return 0;
}
