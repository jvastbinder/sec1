#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isAlpha(char c);
bool isNumber(char c);
char encodeCharacter(char c, int shiftDistance);
enum ASCII_CATEGORY getASCIICategory(char c);
short calcCaseOffset(char c);
void printUsage();

enum ASCII_CATEGORY
{
    uppercase,
    lowercase,
    number,
    nonalphanum,
    nonprintable
};

int main(int argc, char **argv)
{
    char character, *mysterystr;
    FILE *inputFile;
    bool modeChosen, numSet, fileNotSet;
    int shiftDistance = 1;

    if(argc > 4)
    {
        printUsage();
        return 1;
    }

    fileNotSet = true;

    for(int i = 1; i < argc; ++i)
    {
        if(argv[i][0] == '-')
        {
            if(!numSet && isNumber(argv[i][1]) )
            {
                numSet = true;
                shiftDistance *= -1 * strtol(argv[i], &mysterystr, 10);
            }
            else if(modeChosen || ((argv[i][1] != 'e')) && (argv[i][1] != 'd'))
            {
                printUsage();
                return 1;
            }
            if(argv[i][1] == 'd')
            {
                shiftDistance = -1;
            }
            modeChosen = true;
        }
        else if(!numSet && isNumber(argv[i][0]))
        {
            numSet = true;
            shiftDistance *= strtol(argv[i], &mysterystr, 10);
        }
        else if (fileNotSet = !(inputFile = fopen(argv[i], "r")))
        {
            printf("%s\n", argv[i]);
            return 1;
        }
    }

    if(fileNotSet)
    {
        inputFile = stdin;
    }
    if((shiftDistance == 1) || (shiftDistance == -1))
    {
        shiftDistance *= 7;
    }

    character = (char) getc(inputFile);
    while(character != EOF)
    {
        putc(encodeCharacter(character, shiftDistance), stdout);
        character = (char) getc(inputFile);
    }
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

char encodeCharacter(char c, int shiftDistance)
{
    if(isAlpha(c))
    {
        short letterCaseOffset;
        letterCaseOffset = calcCaseOffset(c); // Finds start of alphabet based on case of the char
        c -= letterCaseOffset;                // Changes char value with respect to A/a being 0
        c += shiftDistance;
        c %= 26;
        if(c < 0)
        {
            letterCaseOffset += 26;
        }
        c += letterCaseOffset;
    }
    return c;
}

short calcCaseOffset(char c)
{
    if(getASCIICategory(c) == uppercase)
        return 65;
    return 97;
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

void printUsage()
{
    perror("   Usage: ./crypto [-d/-e] [shift distance] [input file path]\n"
                   "Defaults:           -e      7                stdin");
}
