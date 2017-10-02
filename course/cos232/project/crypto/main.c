#include <stdio.h>
#include <stdbool.h>

enum ASCII_CATEGORY
{
    uppercase,
    lowercase,
    nonalphanum,
    nonprintable
};

short calcCaseOffset(char c);
int len(const char *str);
bool isAlpha(char c);
bool stringsEqual(char *s1, char *s2);
enum ASCII_CATEGORY getASCIICategory(char c);

int main(int argc, char *argv[]) {
    char *plaintext, character;
    int plaintextLength;
    short letterCaseOffset;

    int SHIFT_DISTANCE = 1;
    int ALPHABET_LENGTH = 26;

    plaintext                 = "abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ";
    plaintextLength           = len(plaintext);

    char ciphertext[plaintextLength];

    for(int i = 0; i < plaintextLength; ++i)
    {
        character = plaintext[i];
        letterCaseOffset = 0;
        if(isAlpha(character))
        {
            letterCaseOffset = calcCaseOffset(character); // Finds start of alphabet based on case of the char
            character -= letterCaseOffset;                // Changes char value with respect to A/a being 0
            character += SHIFT_DISTANCE;
            character %= 26;
        }
        ciphertext[i] = (char) (character + letterCaseOffset);     // Corrects char value with respect to case
    }

    ciphertext[plaintextLength - 1] = 0;

    printf("%s\n", ciphertext);

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
bool stringsEqual(char *s1, char *s2)
{
    int size;
    if(sizeof(s1) != sizeof(s2))
        return false;
    for(int i = 0; i < sizeof(s1); ++i)
    {
        if(s1[i] != s2[i])
            return false;
    }
    return true;
}
