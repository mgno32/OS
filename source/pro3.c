#include<chprint.h>
char *str = "hahahahaha";

int main(){
	int r = 0;
	int c = 0;
	while(1){
		for(r = 12, c = 60; r <= 24; r++, c++){
			print(r,c,str[r % 10]);
		}
	}
	return 0;
}
