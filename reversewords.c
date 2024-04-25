#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void printString(char *msg, char *s, size_t len) {
    printf("%s", msg);
    for (int i = 0; i < len; i++) {
        if (s[i] == '\0') printf("[Ø] ");
        else printf("[%c] ", s[i]);
    }
    printf("\n");
}

/* Example 1: "the sky is blue" -> "blue is s */
/*       [t] [h] [e] [ ] [s] [k] [y] [ ] [i] */ 
/*       [b] [l] [u] [e] [ ] [i] [s] [ ] [s] */ 
/* Example 2: "  hello world  " -> "world hel */
/*       [ ] [ ] [h] [e] [l] [l] [o] [ ] [w] */ 
/*       [w] [o] [r] [l] [d] [ ] [h] [e] [l] */ 
/* Example 3: "a good   example" -> "example */ 
/*       [a] [ ] [g] [o] [o] [d] [ ] [ ] [ ] */ 
/*       [e] [x] [a] [m] [p] [l] [e] [ ] [g] */ 



/*
          
len = 15
ptr            + 
              [0] [1] [2] [3] [4] [5] [6] [7] [8] [9] [10][11][12][13][14][15]
s             [t] [h] [e] [ ] [s] [k] [y] [ ] [i] [s] [ ] [b] [l] [u] [e]
result        [b] [l] [u] [e] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
result (act)  [b] [l] [u] [e] [ ] [i] [s] [ ] [s] [k] [y] [ ] [t] [h] [e]
resultPtr                                                      ^
inWord = false
wordLen = 0

*/

char *reverseWords(char *s) 
{

    if (s == NULL || *s == '\0')
        return NULL;

    size_t len = strlen(s);

    size_t resultlen = len + 1;
    char *result = malloc(resultlen);

    char *nextword = result;
    int wordlen = 0;
    for (int i = len - 1; i >= 0; i--) {
        char *ptr = &s[i];
        if (isspace(*ptr) && wordlen == 0) {
            wordlen = 0;
        } else if (isspace(*ptr) && wordlen > 0) {
            memcpy(nextword, ptr+1, wordlen);
            nextword += wordlen;
            *nextword = ' ';
            nextword++;
            wordlen = 0;
        } else if (!isspace(*ptr)) { // Letter of word
            wordlen++;
        } else {
            printf("PANIC\n"); // Should not occur
        }
    }
    if (wordlen>0) {
        memcpy(nextword, &s[0], wordlen);
        nextword += wordlen + 1;
    }
    *(nextword-1) = '\0'; 

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
        // Your reversed string should not contain leading or trailing spaces.
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

    int testsCount = sizeof(tests) / sizeof(struct test);

    for (int i = 0; i < testsCount; i++) {
        struct test t = tests[i];

        char *got = reverseWords(t.input);
        printf("%s: \"%s\" -> \"%s\", expect \"%s\"\n", t.name, t.input, got, t.output);
        assert(strcmp(got, t.output) == 0);
        free(got);
    }

    printf("\n***** All test passed ******\n");

    return 0;
}
