#include<cstdio>
#include<cstring>
#include<string>

using namespace std;

const int T = 10; 

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

double a[T];

int main(){
	FILE* fin = fopen("./testData/tmp.txt", "r");
	double sum = 0;
	for(int i = 0; i < T; i++){
		fscanf(fin, "%lf", &a[T]);
		sum += a[T];
	}
	printf("%le", sum / T);
	return 0;
}
