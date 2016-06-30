#include<chprint.h>
char *str = "shirley";
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
	 	for(i = 0; str[i] != 0; i++){
			char* a=0xB8000 + i * 2;
			*a = str[i];
			*(a + 1) = 0x7;
		} 
		char* a=0xB8000 + i * 2;
		//*a = getchar();
		//*(a + 1) = 0x7;
	 	for (int r = 10; r < 20;++r){
	 		for (int c = 10; c < 14;++c){
				print(r,c,'a'+r);
			}
		}
	}
	return 0;
}
