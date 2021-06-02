#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<string>
#include<algorithm>
#include<vector>
#include<time.h>
#include<sys/time.h>
#include<queue>
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
#define maxm 200005
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

struct Edge
{
    int from,to,_dis;
};
vector<Edge>edge(199990010);
int fa[maxn],n,m,ans,eu,ev,cnt;
//father数组用来存储父亲节点 
bool cmp(Edge a,Edge b)
{
    return a._dis<b._dis;//比较函数 
}
inline int find_die(int x)
{
    while(x!=fa[x]) x=fa[x]=fa[fa[x]];
    return x;//找爹 
} 
inline int kruskal()
{
    sort(edge.begin(),edge.begin()+m,cmp);//先将所有的边按权值排序 
    rep(i,1,m)
    {
        eu=find_die(edge[i].from);
        ev=find_die(edge[i].to);//分别找始点和终点的祖宗节点 
        if(eu==ev)//如果是一个祖宗，就说明他们在一个联通图中 
            continue;
        ans+=edge[i]._dis;//更新最小生成树长度 
        fa[ev]=eu;//顺便标记父亲 
        if(++cnt==n-1)//知道生成最小生成树 
            break;
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
    rep(i,1,n)
        fa[i]=i;//初始化自己是自己的父亲 
    rep(i,1,m)
        edge[i].from=read(),edge[i].to=read(),edge[i]._dis=read();
    double td = get_time();
	kruskal();
	printf("%le\n", get_time() - td);
	return 0;
}
