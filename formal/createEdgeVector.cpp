#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <algorithm>

using namespace std;

const int maxm = 199990000;
vector<int> a;

int main(int argc, char** argv){
	
	int n = atoi(argv[1]);
	
	FILE* fileName = fopen("equalEdge.txt", "w");
	// 等权 
	for(int i = 0; i < n; i++){
		fprintf(fileName, "%d ", 1);
	}
	fclose(fileName);
	
	srand(time(0));
	// 随机
	fileName = fopen("randomEdge.txt", "w");
	for(int i = 0; i < n; i++){
		fprintf(fileName, "%d ", rand() % n);
	}
	
	fileName = fopen("permutationEdge.txt", "w");
	for(int i = 0; i < n; i++){
		a.push_back(i);
	}
	random_shuffle(a.begin(), a.end());
	for(int i = 0; i < n; i++){
		fprintf(fileName, "%d ", a[i]);
	}
	
	return 0;
}
