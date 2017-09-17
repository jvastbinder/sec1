#include <stdio.h>

void setAndPrintImageInfo(FILE *inImage,
                          int *startOfPixelArray,
                          int *sizeOfPixelArray,
                          int *imageWidth,
                          int *imageHeight,
                          int *sizeOfFile)
{
    int stats[5];
    fseek(inImage, 10, SEEK_SET); // start of pixel array
    fread(stats, 4, 1, inImage);
    fseek(inImage, 18, SEEK_SET); // image width
    fread(stats + 1, 4, 1, inImage);
    fseek(inImage, 22, SEEK_SET); // image height
    fread(stats + 2, 4, 1, inImage);
    fseek(inImage, 2, SEEK_SET);  // size of file
    fread(stats + 4, 4, 1, inImage);
    *startOfPixelArray = stats[0];
    *imageWidth = stats[1];
    *imageHeight =stats[2];
    *sizeOfPixelArray = *imageHeight * *imageWidth * -1;
    *sizeOfFile = stats[4];
    printf("Pixels start at: %d\n", *startOfPixelArray);
    printf("Width of image: %d\n", *imageWidth);
    printf("Height of image: %d\n", *imageHeight);

}

int len(const char *str)
{
    int count = 0;
    while(str[count] != '\0')
    {
        count++;
    }
    return ++count;
}

void encodeImage(FILE *inImage,
                 FILE *outImage,
                 const char *message)
{
    int startOfPixelArray,
        sizeOfPixelArray,
        i,
        sizeOfFile,
        messageLen,
        imageWidth,
        imageHeight;
    char byte[1];
    int bit;

    messageLen  = len(message);

    setAndPrintImageInfo(inImage,
                         &startOfPixelArray,
                         &sizeOfPixelArray,
                         &imageWidth,
                         &imageHeight,
                         &sizeOfFile);

    fseek(inImage, 0, SEEK_SET);
    for(i = 0; i < startOfPixelArray; ++i)
    {
        fread(byte, 1, 1, inImage);
        fwrite(byte, 1, 1, outImage);
    }
    int messageIdx = 0;

    for(i = 0; i < sizeOfPixelArray; ++i)
    {
        if((((i+1) % 4) && ((messageIdx / 8) <= messageLen)))
        {
            fread(byte, 1, 1, inImage);
            bit = ((message[messageIdx / 8] >> (messageIdx % 8))) & 1;
            if(bit && (byte[0] % 2 == 0))
                byte[0]++;
            else if(!bit && (byte[0] % 2 != 0))
                byte[0]--;
            fwrite(byte, 1, 1, outImage);
            ++messageIdx;
        }
        else
        {
            fread(byte, 1, 1, inImage);
            fwrite(byte, 1, 1, outImage);
        }
    }

    for(i += startOfPixelArray; i < sizeOfFile; ++i)
    {
        fread(byte, 1, 1, inImage);
        fwrite(byte, 1, 1, outImage);
    }

}

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
    char *message = argv[3];
    inImage       = fopen(argv[1], "r");
    outImage      = fopen(argv[2], "w");

    encodeImage(inImage, outImage, message);

    fclose(inImage);
    fclose(outImage);

    return 0;
}

