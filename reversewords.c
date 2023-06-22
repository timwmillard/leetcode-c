#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Given an input string s, reverse the order of the words.
 *
 * A word is defined as a sequence of non-space characters. The words in s will
 * be separated by at least one space.
 *
 * Return a string of the words in reverse order concatenated by a single space.
 *
 * Note that s may contain leading or trailing spaces or multiple spaces between
 * two words. The returned string should only have a single space separating the
 * words. Do not include any extra spaces. A word is defined as a sequence of
 * non-space characters. The words in s will be separated by at least one space.
 *
 * Return a string of the words in reverse order concatenated by a single space.
 *
 * Note that s may contain leading or trailing spaces or multiple spaces between
 * two words. The returned string should only have a single space separating the
 * words. Do not include any extra spaces.
 *
 */
char *reverseWords(char *s) {

    if (s == NULL || *s == '\0')
        return NULL;

    size_t len = strlen(s);

    char *result = malloc(sizeof(char) * len + sizeof(char));
    char *resultPtr = result;

    char *ptr = &s[len - 1]; // start at the end
    bool inWord = false;
    int wordLen = 0;
    while (ptr != s) {
        if (*ptr != ' ') {
            // any letter
            inWord = true;
            wordLen++;
        } else {
            // space
            if (inWord) {
                // copy word to result
                memcpy(resultPtr, ptr + 1, wordLen);
                resultPtr += wordLen;

                *resultPtr = ' ';
                resultPtr++;

                inWord = false;
                wordLen = 0;
            }
        }
        ptr--;
    }
    if (inWord) {
        memcpy(resultPtr, ptr, wordLen + 1);
        resultPtr += wordLen + 1;
    }

    if (*(resultPtr-1) == ' ')
        *(resultPtr-1) = '\0';
    else 
        *resultPtr = '\0';

    return result;
}

int main() {

    struct test {
        char *name;
        char *input;
        char *output;
    };

    struct test tests[] = {
        {
            .name = "Example 1",
            .input = "the sky is blue",
            .output = "blue is sky the",
        },
        // Your reversed string should not contain leading or trailing
        // spaces.
        {
            .name = "Example 2",
            .input = "  hello world  ",
            .output = "world hello",
        },
        // You need to reduce multiple spaces between two words to a single
        // space in the reversed string.
        {
            .name = "Example 3",
            .input = "a good   example",
            .output = "example good a",
        },

    };

    for (int i = 0; i < sizeof(tests); i++) {
        struct test t = tests[i];

        char *got = reverseWords(t.input);
        printf("%s: \"%s\" -> \"%s\", expect \"%s\"\n", t.name, t.input, got,
               t.output);
        assert(strcmp(got, t.output) == 0);
        free(got);
    }

    printf("\n***** All test passed ******\n");

    return 0;
}
