#include <stdio.h>
int main(int argc, char *argv[])
{
    /*
     * bitmap file header
     * 0: 1 byte file type
     * 1: 2 byte file size
     * 3: 1 byte reserved
     * 4: 1 byte reserved
     * 5: 2 byte offset to start of pixel array
     */
    FILE *inImage, *outImage;
    int startOfPixelArray[1];

    inImage       = fopen("sheldon.bmp", "r");
    outImage      = fopen("enc.bmp", "w");
    char *message = argv[3];

    fseek(inImage, 10, SEEK_SET);
    fread(startOfPixelArray, 4, 1, inImage);
    printf("Pixels start at: %d\n", startOfPixelArray[0]);

    fclose(inImage);
    fclose(outImage);

    return 0;
}
