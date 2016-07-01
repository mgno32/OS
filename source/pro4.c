#include<chprint.h>
char *str = "OperatingSystem";
//int *color = [0x7,0x4,0x9];

int getchar(){
	int ch;
	asm volatile("int 0x16;"
			:"=a"(ch)
			:"a"(0x1000)
			);
	return ch;

}

int main(){
 	while(1){
		int i = 0;

		int r;
		int c;
	 	for (r = 10,c = 40; r < 25;++r,c--){
			globalColor ++;
			globalColor &= 0x07;
			if (globalColor == 0)globalColor = 1;
			printColor(r,c,str[i]);
			i++;
		}
	}
	return 0;
}
