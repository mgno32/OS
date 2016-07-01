#include<chprint.h>
#include<disk.h>
char *str = "hahahahaha";

char *filename = "PRO3    COM";


 int main(){
	int c;
	int r;
	while(1){
		for(r = 12, c = 60; r <= 24; r++, c++){
			print(r,c,str[r % 10]);
		}
	}
	return 0;
}
