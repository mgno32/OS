int color[3] = {0x7,0x4,0x9}; 
int printNumber = 0;
int globalColor = 0x7;
__attribute__((regparm(3)))
void print(int r, int c, char ch){
	int offset=(80 * (r) + c) * 2;
	int conum = printNumber % 3;
	printNumber ++;
	int co = color[conum];
	asm volatile("push es;"
			"mov es,ax;"
			"mov es:[bx], cx;"
			"pop es;":
			:"a"(0xB800),"b"(offset),"c"((co << 8) | ch)
			);
}

__attribute__((regparm(3)))
void printColor(int r, int c, char ch){
	int offset=(80 * (r) + c) * 2;
	asm volatile("push es;"
			"mov es,ax;"
			"mov es:[bx], cx;"
			"pop es;":
			:"a"(0xB800),"b"(offset),"c"((globalColor << 8) | ch)
			);
}
