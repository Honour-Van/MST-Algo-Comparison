#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

const int maxLen = 50;
const int maxn = 20000 + 10;
const int maxm = 19999000 + 10;
 
int n, m;
vector<int> weight(199990000);
char fileName[maxLen];

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
		int x; 
		fscanf(fileIn, "%d", &weight[i]);
	}
	
	// 放在 node=n 的目录下
	char intStr[10]; itoa(intStr, n); 
	string dirName = string(intStr);
	string order = "mkdir -p " + dirName + "average";
	system(order.c_str()); 
	
	string fileName = "./" + dirName + "average/" + "graph";
	itoa(intStr, 0);
	fileName += string(intStr);
	fileName += ".txt";
	FILE* fout = fopen(fileName.c_str(), "w");
	
	// T = 0
	fprintf(fout, "%d %d\n", n, n - 1);
	for(int i = 1; i < n; i++){
		int u = i, v = rand() % i, w = weight[i];
		fprintf(fout, "%d %d %d\n", u + 1, v + 1, w);
	}
	fclose(fout);
	fileName = "./" + dirName + "average/" + "graph";
	itoa(intStr, n-1);
	fileName += string(intStr);
	fileName += ".txt";
	fout = fopen(fileName.c_str(), "w");
	
	// T = N - 1
	int p = 0;
	fprintf(fout, "%d %d\n", n, n * (n - 1) / 2);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			if(i != j)
				fprintf(fout, "%d %d %d\n", i + 1, j + 1, weight[p++]);
	}
	fclose(fout);
	return 0;
}
