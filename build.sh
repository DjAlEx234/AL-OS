export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
cf=0
af=0
cfc()
{
  cf=$((cf+1))
  echo "C File $cf has been processed"
}
afc()
{
  af=$((af+1))
  echo "ASM File $af has been processed"
}
mkdir temp
cd temp
i686-elf-gcc -c ../Boot-Loader/entry.c -o entry.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I"../Headers/"
cfc
i686-elf-gcc -c ../Input-Output/asm-io.c -o asm-io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I"../Headers/"
cfc
i686-elf-gcc -c ../IRQ-ISR/interrupt.c -o interrupt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I"../Headers/"
cfc
i686-elf-gcc -c ../Input-Output/terminal.c -o terminal.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I"../Headers/"
cfc
i686-elf-gcc -c ../Input-Output/keyboard.c -o keyboard.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I"../Headers/"
cfc
nasm -felf32 ../Boot-Loader/entry.asm -o entry2.o
afc
nasm -felf32 ../IRQ-ISR/interrupt.asm -o interrupt2.o
afc
i686-elf-gcc -T ../Boot-Loader/link.ld -o ../AL-OS.bin -I"../Headers/" -ffreestanding -O2 -nostdlib entry.o entry2.o asm-io.o interrupt.o interrupt2.o terminal.o keyboard.o
echo Stitching all output files...
rm *.*
cd ..
rmdir temp
echo Build finished!
if grub-file --is-x86-multiboot AL-OS.bin; then
	echo Multiboot confirmed
else
	echo No multiboot
fi
echo Now loading QEMU...
qemu-system-i386 -kernel AL-OS.bin -d guest_errors
