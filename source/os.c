#include<chprint.h>
#include<disk.h>

int getchar(){
	int ch;
	asm volatile("int 0x16;"
			:"=a"(ch)
			:"a"(0x1000)
			);
	return ch;

}

char *filename = "PRO4    COM";
int main(){
	if(LoadFile(filename, 0x100, 0x4000))
		print(10,10,'a');
	asm volatile(
			"mov ax, 0x4000;"
			"mov ds, ax;"
			"jmp 0x4000:0x100;"
			);
 	while(1){
	}
	return 0;
}
