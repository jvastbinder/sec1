#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

enum ASCII_CATEGORY
{
    uppercase,
    lowercase,
    number,
    nonalphanum,
    nonprintable
};

short calcCaseOffset(char c);
int len(const char *str);
bool isAlpha(char c);
bool isNumber(char c);
bool stringsEqual(char *s1, char *s2);
enum ASCII_CATEGORY getASCIICategory(char c);

int main(int argc, char **argv) {
    if(argc > 4)
    {
        printf("   Usage: ./crypto [-d/-e] [shift distance] [input file path]\n"
                       "Defaults:           -e      7                stdin");
        return 1;
    }
    char plaintext[1024], character, *notsurehowthisworks;
    int plaintextLength;
    int shiftDistance = 7;
    short letterCaseOffset;


    for(int i = 1; i < argc; ++i)
    {
        if(argv[i][0] == '-')
        {
            if((argv[i][1] != 'e') && (argv[i][1] != 'd'))
            {
                printf("   Usage: ./crypto [-d/-e] [shift distance] [input file path]\n"
                       "Defaults:           -e      7                stdin");
                return 1;
            }
            if(argv[i][1] == 'd')
            {
               shiftDistance = -1;
            }

        }
        if(isNumber(argv[i][0]))
        {
            shiftDistance *= strtol(argv[i], &notsurehowthisworks, 10);
        }
        if(isAlpha(argv[i][0]))
        {
           FILE *inFile = fopen(argv[i], "r");
        }
    }

    if(!plaintext)
    {
        fgets(plaintext, sizeof(plaintext) - 1, stdin);
        plaintextLength           = len(plaintext);
    }

    char ciphertext[plaintextLength];

    for(int i = 0; i < plaintextLength; ++i)
    {
        character = plaintext[i];
        letterCaseOffset = 0;
        if(isAlpha(character))
        {
            letterCaseOffset = calcCaseOffset(character); // Finds start of alphabet based on case of the char
            character -= letterCaseOffset;                // Changes char value with respect to A/a being 0
            character += shiftDistance;
            character %= 26;
        }
        character += letterCaseOffset;
        puts(&character);
    }

    ciphertext[plaintextLength - 1] = 0;

    //printf("%s\n", ciphertext);

    return 0;
}

enum ASCII_CATEGORY getASCIICategory(char c)
{
    if((c == 127) || ((0 <= c) && (c < 32)))
        return nonprintable;
    if(((31 < c) && (c < 47)) ||
       ((57 < c) && (c < 65)) ||
       ((90 < c) && (c < 97)) ||
       ((122 < c) && (c < 127)))
        return nonalphanum;
    else if((47 < c) && (c < 58))
        return number;
    else if((64 < c) && (c < 91))
        return uppercase;
    else if((96 < c) && (c < 123))
        return lowercase;

}

short calcCaseOffset(char c)
{
    if(getASCIICategory(c) == uppercase)
        return 65;
    return 97;
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

bool isAlpha(char c)
{
    enum ASCII_CATEGORY category = getASCIICategory(c);
    return (category == uppercase) || (category == lowercase);
}
bool isNumber(char c)
{
    enum ASCII_CATEGORY category = getASCIICategory(c);
    return category == number;
}
