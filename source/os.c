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

char filename4[] = "PRO4    COM";
char filename3[] = "PRO3    COM";
char filename2[] = "PRO2    COM";
char filename1[] = "PRO1    COM";

int main(){
	LoadFile(filename1, 0x100, 0x4000);
	LoadFile(filename2, 0x100, 0x5000);
	LoadFile(filename3, 0x100, 0x6000);
	LoadFile(filename4, 0x100, 0x7000);
	int input;
	while(1){
		input = getchar();
		int choice = (input & 0xFF) - '0';

		if (choice >= 0 && choice <= 3){
			asm volatile(
					"mov ds, bx;"
					"mov ss, bx;"
					"mov sp, 0x100;"
					"push bx;"
					"push 0x100;"
					"retf;"
					:
					:"b"(0x4000  + choice * 0x1000)
			);
		}
	}

	return 0;
}
