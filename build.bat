gcc -nostdlib -masm=intel -m32 main.c module.c -o main.bin
nasm -f bin loader.asm -o loader.bin
objcopy -O binary main.bin
copy /b loader.bin+main.bin start.bin
del loader.bin start.bin 
C:\programs\qemu\qemu-system-i386.exe start1.bin
pause