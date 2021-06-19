#include <cstdio>
#include <cstring>
#include <cctype>
#include <stdlib.h>
#include <string>
#include <map>
#include <iostream>
#include <set>
#include <stack>
#include <cmath>
#include <queue>
#include <vector>
#include <algorithm>
#include <sys/time.h> 
using namespace std;
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;
typedef pair<int,int> pir;
const int N=10000+10;
const int M=100000000;

int first[N],tot;
int vis[N],dis[N],n,m;
priority_queue <pir,vector<pir>,greater<pir> >q;
struct edge
{
    int v,w,next;
};
vector<edge>e(M);

void add_edge(int u,int v,int w)
{
    e[tot].v=v;
    e[tot].w=w;
    e[tot].next=first[u];
    first[u]=tot++;
}

void init()
{
    mem(first,-1);
    tot=0;
    mem(dis,127);
}

void prim()
{
    int cnt=0,sum=0;
    dis[1]=0;
    q.push(make_pair(0,1));
    while(!q.empty()&&cnt<n)
    {
        int d=q.top().first,u=q.top().second;
        q.pop();
        if(!vis[u])
        {
            cnt++;
            sum+=d;
            vis[u]=1;
            for(int i=first[u]; ~i; i=e[i].next)
                if(e[i].w<dis[e[i].v])
                {
                    dis[e[i].v]=e[i].w;
                    q.push(make_pair(dis[e[i].v],e[i].v));
                }
        }
    }
    //if(cnt==n) printf("%d\n",sum);
    //else puts("orz");
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
    int u,v,w;
    init();
    scanf("%d%d",&n,&m);
    for(int i=1; i<=m; i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    double td = get_time();
	prim();
    printf("%le\n", get_time() - td);
	return 0;
}
