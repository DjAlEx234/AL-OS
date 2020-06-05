cd "Grub Setup"
cp ../AL-OS.bin iso/al-os.bin
grub-mkrescue -o ../al-os.iso iso
qemu-system-i386 -cdrom ../al-os.iso
