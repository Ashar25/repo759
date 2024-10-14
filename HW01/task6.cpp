#include <iostream>
#include <cstdio>
using std::cout;
int main(int argc, char *argv[]){
    int n = std::atoi(argv[1]);
    // int n = 7;
    for(int i=0;i<=n;i++){
	printf("%d ",i);
    }
    cout << "\n";
    for(int i = n;i>=0;i--){
	cout << i << " ";
    }
    return 0;
}
