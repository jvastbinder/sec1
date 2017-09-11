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
    short imageWidth[1];
    short imageHeight[1];

    inImage       = fopen("sheldon.bmp", "r");
    outImage      = fopen("enc.bmp", "w");
    char *message = argv[3];

    fseek(inImage, 10, SEEK_SET);
    fread(startOfPixelArray, 4, 1, inImage);
    fseek(inImage, 18, SEEK_SET);
    fread(imageWidth, 2, 1, inImage);
    fseek(inImage, 22, SEEK_SET);
    fread(imageHeight, 2, 1, inImage);
    printf("Pixels start at: %d\n", startOfPixelArray[0]);
    printf("Width of image: %d\n", imageWidth[0]);
    printf("Height of image: %d\n", imageHeight[0]);

    fclose(inImage);
    fclose(outImage);

    return 0;
}
