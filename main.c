asm(".code16gcc\n");
#define G80x45 0x3
void setVideo(int mode);
void setChar(int x,int y,int color,int c);
void print(char *text, int x, int y, int color);
void batteryCMOS();
void extraMemory();
void floppyDrive();
void existFPU();
void monitorType();
void existKeyboard();
//void numberFloppy();
int start() {
	
	char text1[] = "Battery:";
	char text2[] = "Extra Memory:";
	char text3[] = "Floppy drive:";
	char text4[] = "FPU:";
	char text5[] = "Keyboard:";
	char text6[] = "Monitor Type:";
	char text7[] = "Number Floppy:";
	setVideo(G80x45);
	print(text5,0,5,0x3);
	existKeyboard();
	//print(text7,26,1,0x3);		
	//numberFloppy();
	print(text1,0,0,0x3);
	batteryCMOS();
	print(text2,0,1,0x3);
	extraMemory();
	print(text3,0,2,0x3);
	floppyDrive();
	print(text4,0,3,0x3);
	existFPU();
	print(text6,0,4,0x3);
	monitorType();
	asm("cli");
return 0;
}
/*void setChar(int x,int y,int color,int c) {
	int pos = y*80*2+x*2;
	asm("mov ax,0xB800");
	asm("mov es,ax");
	asm("mov di,0");
	asm("mov di, word ptr [ebp-0x4]");
	asm("mov ah,byte ptr[ebp+0x10]");
	asm("mov al,byte ptr[ebp+0x14]");
	asm("mov word ptr es:[di],ax");
}
void print(char *t, int x, int y, int color){
int i=0;
for(i=0;t[i];i++)
	setChar((x+i),y,color,t[i]);
}
void setVideo(int mode) {
	asm("mov ah, 0x0");
	asm("mov al,[ebp+0x8]");
	asm("int 0x10");
}*/
void batteryCMOS() {
	int a;
	char text1[] = "have a power";
	char text2[] = "have't a power";
	asm("mov al,0xD");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("shr al,7");
	asm("mov byte ptr[ebp-0x4],al");
	if(a==0x1) {
	print(text1,9,0,0x4);
	}
	else print(text2,9,0,0x4);
}
void extraMemory() {
	int a=0;
	int b=0;
	char text1[] = "65535 KB";
	char text2[] = "0 KB";
	asm("mov al,0x17");
	asm("out 0x70,al");
	asm("in al,0x71"); 
	asm("mov byte ptr[ebp-0x8],al");
	setChar(0,2,0x4,b);
	asm("mov al,0x17");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("mov byte ptr[ebp-0x4],al");
	setChar(0,3,0x4,a);
	if(b==0xFF&&a==0xFF)
		print(text1,14,1,0x4);
	else print(text2,14,1,0x4);
}
void existKeyboard(){
	char a;
	char text1[] = "no";
	char text2[] = "yes";
	asm("mov al,0x14");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("shr al,2");
	asm("mov byte ptr[ebp-0x4],al");
	if(a==0x1)
		print(text1,10,5,0x4);
	else print(text2,10,5,0x4);
}
void floppyDrive() {
	int a,b;
	char text1[] = "yes,";
	char text2[] = "no";
	char text3[] = "(0)";
	asm("mov al,0x14");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("shl al,7");
	asm("mov byte ptr[ebp-0x4],al");
	if(a==0b10000000)
		print(text1,14,2,0x4);
	else 
	print(text2,14,2,0x4);
	asm("mov al,0x14");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("shr al,6");
	asm("mov byte ptr[ebp-0x8],al");
	if(b==0x0)
	print(text3,19,2,0x4);
}
void existFPU() {
	int a;
	char text1[] = "no";
	char text2[] = "yes";
	asm("mov al,0x14");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("shr al,1");
	asm("shl al,7");
	asm("shr al,7");
	asm("mov byte ptr[ebp-0x4],al");
	if(a==0b1) 
		print(text2,5,3,0x4);
	else print(text1,5,3,0x4);
	 // 00000111
	}
	void monitorType() {
	int a;
	char text1[] = "EGA/VGA";
	char text2[] = "40x25 CGA";
	char text3[] = "80x25 CGA";
	char text4[] = "MDA";
	asm("mov al,0x14");
	asm("out 0x70,al");
	asm("in al,0x71");
	asm("shr al,4");
	asm("mov byte ptr[ebp-0x4],al");
	switch(a) {
		case 0b00: print(text1,14,4,0x4);
		break;
		case 0b01: print(text2,14,4,0x4);
		break;
		case 0b10: print(text3,14,4,0x4);
		break;
		case 0b11: print(text4,14,4,0x4);
		break;
	}
}


