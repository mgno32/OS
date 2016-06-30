
__attribute__((regparm(3)))
void print(int r, int c, char ch){
	int offset=(80 * (r) + c) * 2;
	int co = offset % 3;
	co = color[co];
	asm volatile("push es;"
			"mov es,ax;"
			"mov es:[bx], cx;"
			"pop es;":
			:"a"(0xB800),"b"(offset),"c"((co << 8) | ch)
			);
}

