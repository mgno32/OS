#include<chprint.h>
#include<disk.h>
char *str = "shirley";
char *filename = "PRO1    COM";
int main(){
	int r = 0;
	int c = 0;
	while(1){
		for(r = 0, c = 0; r <= 11; r++, c++){
			print(r,c,str[r % 7]);
		}
		for (int r = 12; r < 14;++r){
			for (int c = 0; c < 5;++c){
				print(r,c,'a'+r);
			}
		}
	}
	return 0;
}
