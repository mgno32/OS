#include "chprint.h"
#include "disk.h"
#include "pcb.h"
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
PCB pcbs[5];
#define dw uint16_t
#define dd uint32_t

int main(){
	LoadFile(filename1, 0x100, 0x4000);
	int pid;
	pid = 1;
	pcbs[pid].DS = pcbs[pid].SS = pcbs[pid].CS = 0x4000;
	pcbs[pid].IP = 0x100;
	pcbs[pid].SP = 0x100 - 2;
	pcbs[pid].FLAGS = 512;

	LoadFile(filename2, 0x100, 0x5000);
	pid++;
	pcbs[pid].DS = pcbs[pid].SS = pcbs[pid].CS = 0x5000;
	pcbs[pid].IP = 0x100;
	pcbs[pid].SP = 0x100 - 2;
	pcbs[pid].FLAGS = 512;

	LoadFile(filename3, 0x100, 0x6000);
	pid++;
	pcbs[pid].DS = pcbs[pid].SS = pcbs[pid].CS = 0x6000;
	pcbs[pid].IP = 0x100;
	pcbs[pid].SP = 0x100 - 2;
	pcbs[pid].FLAGS = 512;

	LoadFile(filename4, 0x100, 0x7000);
	pid++;
	pcbs[pid].DS = pcbs[pid].SS = pcbs[pid].CS = 0x7000; 
	pcbs[pid].IP = 0x100;
	pcbs[pid].SP = 0x100 - 2;
	pcbs[pid].FLAGS = 512;
	int input;
	int i = 0;
	while(1){
		/*
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
		*/
		print(10,10,'a' + i);
		i++;
		if (i > 26)i = 0;
	}

	return 0;
}
