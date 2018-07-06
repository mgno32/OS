#include<chprint.h>
#include<disk.h>
char *str = "shirley";
char *filename = "PRO2.COM";
int main(){
	int r = 0;
	int c = 0;
	while(1){
		for (int r = 14; r < 20;++r){
			for (int c = 0; c < 8;++c){
				print(r,c,filename[c % 8]);
			}
		}
	}
	return 0;
}
