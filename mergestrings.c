#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char *mergeAlternately(char *word1, char *word2){
    size_t word1_len = strlen(word1);
    size_t word2_len = strlen(word2);
    size_t len = word1_len + word2_len;
    char *result = malloc(sizeof(char) * len + 1);

    int i1 = 0;
    int i2 = 0;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0 && i1 < word1_len) {
            result[i] = word1[i1];
            i1++;
        }
        if (i % 2 != 0 && i2 < word2_len) {
            result[i] = word2[i2];
            i2++;
        }
    }

    return result;
}

int main()
{

    char *example1 = mergeAlternately("abc", "pqr");
    printf("example1 = %s\n", example1);
    assert(strcmp(example1, "apbqcr") == 0);
    free(example1);

    char *example2 = mergeAlternately("ab", "pqrs");
    printf("example2 = %s\n", example2);
    assert(strcmp(example2, "apbqrs") == 0);
    free(example2);

    char *example3 = mergeAlternately("abcd", "pq");
    printf("example3 = %s\n", example3);
    assert(strcmp(example3, "apbqcd") == 0);
    free(example3);

    printf("*** All tests passed\n");

    return 0;
}

