asm(".code16gcc\n");
void setVideo(int mode);
void setChar(int x,int y,int color,int c);
void print(char *text, int x, int y, int color);
void setChar(int x,int y,int color,int c) {
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
}