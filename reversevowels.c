#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

bool isVowel(char c) {
    return 
        c == 'A' || c == 'a' ||
        c == 'E' || c == 'e' ||
        c == 'I' || c == 'i' ||
        c == 'O' || c == 'o' ||
        c == 'U' || c == 'u';
}

char *reverseVowels(const char *s) {

    size_t len = strlen(s);

    char *result = malloc(sizeof(char) * len + sizeof(char));
    strncpy(result, s, len + 1);

    char *first = result;
    char *last = &result[len - 1];
    // loop
    while (first <= last)
    {
        bool isFirstVowel = isVowel(*first);
        bool isLastVowel = isVowel(*last);

        if (isFirstVowel && isLastVowel) {
            char tmp = *first;
            *first = *last;
            *last = tmp;
            first++;
            last--;
        } else {
            if (!isFirstVowel)
                first++;
            if (!isLastVowel)
                last--;
        }

    }
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
            .input = "hello",
            .output = "holle",
        },
        {
            .name = "Example 2",
            .input = "leetcode",
            .output = "leotcede",
        }
    };

    for (int i = 0; i < 2; i++) {
        struct test t = tests[i];

        printf("%s: \"%s\" -> ", t.name, t.input);
        char *got = reverseVowels(t.input);
        printf("\"%s\", expect \"%s\"\n", got, t.output);
        assert(strcmp(got, t.output) == 0);
        free(got);
    }

    printf("\n***** All test passed ******\n");

    return 0;
}
