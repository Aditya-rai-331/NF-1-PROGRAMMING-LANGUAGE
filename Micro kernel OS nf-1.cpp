#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f_asm = fopen("kernel.bin", "rb");
    if (!f_asm) { printf("[ERR] kernel.bin missing!\n"); return 1; }

    FILE *f_img = fopen("nf1_os.img", "wb");
    unsigned char buffer[512];
    fread(buffer, 1, 512, f_asm);
    fwrite(buffer, 1, 512, f_img);

    fclose(f_asm); fclose(f_img);
    printf("--- NF-1 OS BUILD SUCCESSFUL: nf1_os.img ready ---\n");
    return 0;
}

