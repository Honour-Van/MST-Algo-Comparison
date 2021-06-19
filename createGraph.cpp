#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>

using namespace std;

const int maxLen = 50;
const int maxn = 10000 + 10;
#define maxm (50000010)

// 邻接表 
struct Node{
	int data;
	int next;
	int weight;	
}/*node[maxm * 2]*/;
vector<Node > node(maxm*2);

// 边 
struct Edge{
	int u, v, w;
}/*edge[maxm]*/;
vector<Edge > edge(maxm);

// 邻接表位置 
int cnt = 0;
int edgePoint; 
int n, m;
int head[maxn];
//int weight[maxm];
vector<int > weight(maxm);
char fileName[maxLen];

int deg[maxn];
bool vis[maxn];

// 添加无向边 
void add_edge(int u, int v, int w){
	node[cnt].data = v; node[cnt].next = head[u]; node[cnt].weight = w; head[u] = cnt++;
	node[cnt].data = u; node[cnt].next = head[v]; node[cnt].weight = w; head[v] = cnt++;
	deg[u] ++;
	deg[v] ++;
}

// T 表示轮次，每次给度数不超过 T + 1 的节点补 
void Generate_Edge_Average(int T){
	for(int i = 0; i < n; i++){
		if(deg[i] > T) continue;
		memset(vis, 0, sizeof(vis));
		for(int j = head[i]; j != -1; j = node[j].next){
			vis[node[j].data] = true;
		}
		for(int j = 0; j < n; j++)
			if(i != j)
				if(vis[j] == false && deg[j] <= T){
					add_edge(i, j, weight[edgePoint]);
					edge[edgePoint].u = i, edge[edgePoint].v = j, edge[edgePoint].w = weight[edgePoint];
					edgePoint ++; 
					break;
				}
	}
}

// 每次给一个节点补到满 
void Generate_Edge_Pernode(){
	for(int i = 0; i < n; i++){
		if(deg[i] < n - 1){
			//printf("%d, %d\n", i, deg[i]);
			memset(vis, 0, sizeof(vis));
			for(int j = head[i]; j != -1; j = node[j].next){
				vis[node[j].data] = true;
			}
			for(int j = 0; j < n; j++){
				if(vis[j] == false && i != j){
					add_edge(i, j, weight[edgePoint]);
					edge[edgePoint].u = i, edge[edgePoint].v = j, edge[edgePoint].w = weight[edgePoint];
					edgePoint ++;
				}
			}
			break;
		}
	}
}

void itoa(char* ch, int n){
	if(n == 0){
		ch[0] = '0';
		ch[1] = '\0';
		return;
	}
	int len = 0;
	char tmp[10];
	while(n > 0){
		tmp[len++] = n % 10 + '0';
		n /= 10;
	}
	for(int i = 0; i < len; i++){
		ch[i] = tmp[len - i - 1];
	}
	ch[len] = '\0';
}

// createGraph fileName n m
int main(int argc, char** argv){
	
	strcpy(fileName, argv[1]);
	n = atoi(argv[2]);
	m = atoi(argv[3]);

	printf("%d %d %s\n", n, m, fileName);
	FILE* fileIn = fopen(fileName, "r");
	
	// 从边权文件中读取边权 
	for(int i = 0; i < m; i++){
		fscanf(fileIn, "%d", &weight[i]);
	}
	
	// 创建初始树图 
	edgePoint = 0;
	for(int i = 0; i < n; i++){
		head[i] = -1;
	}
	for(int i = 1; i < n; i++){
		int u = i, v = rand() % i, w = weight[edgePoint];
		edge[edgePoint].u = u, edge[edgePoint].v = v, edge[edgePoint].w = w;
		add_edge(u, v, w);
		edgePoint++;
	}
	
	// 放在 node=n 的目录下
	char intStr[10]; itoa(intStr, n); 
	string dirName = string(intStr);
	string order = "mkdir -p " + dirName + "average";
	system(order.c_str()); 
	
    int p = 0;
    // 按轮次逐步添加边 
	for(int T = 0; T <= 300; T++){
        if(T % 2  == 0){
		string fileName = "./" + dirName + "average/" + "graph";
		itoa(intStr, T);
		fileName += string(intStr);
		fileName += ".txt";
		FILE* fout = fopen(fileName.c_str(), "w");
		// printf("%s\n", fileName.c_str());
		fprintf(fout, "%d %d\n", n, edgePoint);
		for(int i = 0; i < edgePoint; i++){
			fprintf(fout, "%d %d %d\n", edge[i].u + 1, edge[i].v + 1, edge[i].w); 
		}
		fclose(fout);
		}
		Generate_Edge_Average(T);
	}
	
	order = "mkdir -p " + dirName + "pernode";
	system(order.c_str());

	
	// 创建初始树图 
	edgePoint = 0;
	cnt = 0;
	for(int i = 0; i < n; i++){
		head[i] = -1; deg[i] = 0;
	}
	for(int i = 1; i < n; i++){
		int u = edge[edgePoint].u, v = edge[edgePoint].v, w = edge[edgePoint].w;
		add_edge(u, v, w);
		edgePoint++;
	}
    
    p=0;	
	// 按轮次逐步添加边 
	for(int T = 0; T <= 300; T++){
        if(T % 2 == 0){
        string fileName = "./" + dirName + "pernode/" + "graph";
		itoa(intStr, T);
		fileName += string(intStr);
		fileName += ".txt";
		FILE* fout = fopen(fileName.c_str(), "w");
		// printf("%s\n", fileName.c_str());
		fprintf(fout, "%d %d\n", n, edgePoint);
		for(int i = 0; i < edgePoint; i++){
			fprintf(fout, "%d %d %d\n", edge[i].u + 1, edge[i].v + 1, edge[i].w); 
		}
		fclose(fout);
		}
		Generate_Edge_Pernode();
	}
	
	return 0;
}
