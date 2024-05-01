/*

443. String Compression
-----------------------

Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead, be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

You must write an algorithm that uses only constant extra space.
 

Example 1:
---------
Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

Example 2:
---------
Input: chars = ["a"]
Output: Return 1, and the first character of the input array should be: ["a"]
Explanation: The only group is "a", which remains uncompressed since it's a single character.

Example 3:
---------
Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".
 

Constraints:
---------
1 <= chars.length <= 2000
chars[i] is a lowercase English letter, uppercase English letter, digit, or symbol.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define PRINT_ARRAY(ns, size) printf("["); \
                              for (int i = 0; i < (size); i++) \
                                 printf("%s%s", (ns)[i], i!=(size)-1?", ":""); \
                              printf("]")

char *arrayf(char ns[], int size)
{
    char *ret = malloc(size + 3);
    char *ptr = ret;
    sprintf(ptr++, "[");
    for (int i = 0; i < (size); i++) {
        char c = ns[i];
        char str[5];
        if (c=='\0') strcpy(str, "Ø");
        else strncpy(str, &c, 1);
        ptr += sprintf(ptr, "%s%s", str, i!=(size)-1?", ":"");
    }
    sprintf(ptr, "]");
    return ret;
}

int compress(char* chars, int charsSize) 
{
    printf("BEFORE: %s\n", arrayf(chars, charsSize));
    if (charsSize < 1) return 0;
    char c = chars[0];

    int count = 0;
    char *ret = chars;
    for (int i=0; i<charsSize; i++) {
        if (c == chars[i]) {
            count++;
        } else { // change char
            *ret = c;
            ret++;
            if (count > 1) {
                char num[50];
                int countLen = snprintf(num, 50, "%d", count);
                memcpy(ret, num, countLen);
                ret += countLen;
            }

            c = chars[i];
            count = 1;
        }
    }
    *ret = c;
    ret++;
    if (count > 1) {
        char num[50];
        int countLen = snprintf(num, 50, "%d", count);
        memcpy(ret, num, countLen);
        ret += countLen;
    }
    *ret = '\0';

    printf("AFTER:  %s\n", arrayf(chars, charsSize));
    return (ret - chars);
}


int main()
{
    struct test {
        char *name;
        char *chars;
        char *anwser;
        int anwserLen;
    };

    struct test tests[] = {
        {
            .name = "Example 1",
            .chars = (char []){'a','a','b','b','c','c','c','\0'},
            .anwser = "a2b2c3",
            .anwserLen = 6,
        },
        {
            .name = "Example 2",
            .chars = (char []){'a','\0'},
            .anwser = "a",
            .anwserLen = 1,
        },
        {
            .name = "Example 3",
            .chars = (char []){'a','b','b','b','b','b','b','b','b','b','b','b','b','\0'},
            .anwser = "ab12",
            .anwserLen = 4,
        },


    };
    int testsCount = sizeof(tests) / sizeof(struct test);

    for (int i = 0; i < testsCount; i++) {
        struct test t = tests[i];

        int size = strlen(t.chars);
        char *chars = malloc(size * sizeof(char));
        memcpy(chars, t.chars, size);

        int charsLen = compress(chars, size);

        printf("%s >> compress(%s) = %s len(%d), but want %s len(%d)\n", t.name, t.chars, chars, charsLen, t.anwser, t.anwserLen);
        assert(strcmp(chars, t.anwser) == 0);
        assert(charsLen == t.anwserLen);

        printf("  ---- PASSED ----\n");
    } 

    printf("\n***** All test passed ******\n");

    return 0;
}

