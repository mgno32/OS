#include<chprint.h>
int *color = [0x7,0x4,0x9];
char *str = 'shirley';

int main(){
	int r = 0;
	int c = 0;
	while(1){
		for(r = 0, c = 0; r <= 11; r++, c++){
			char* a = 0x8B00;
			*a = str[r % 7];
			*(a + 1) = color[r % 3];
			print(r,c,'a')
		}
	}
}
