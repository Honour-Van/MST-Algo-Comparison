#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

const int maxm = 50000000;
int a[maxm];

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
		a[i] = i;
	}
	random_shuffle(a, a + n);
	for(int i = 0; i < n; i++){
		fprintf(fileName, "%d ", a[i]);
	}
	
	return 0;
}
