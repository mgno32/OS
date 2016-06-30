#include<chprint.h>
char *str = "I Love ";

int main(){ 
	int r = 0;
	int c = 0;
	while(1) {
		for(r  = 0, c = 60; r <= 12 ;r ++, c--){
			print(r,c,str[r % 7]);
		}
	}
	return 0;
}
