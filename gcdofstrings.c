#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pseudo Code of the Algorithm-
// Step 1:  Let  a, b  be the two numbers
// Step 2:  a mod b = R
// Step 3:  Let  a = b  and  b = R
// Step 4:  Repeat Steps 2 and 3 until  a mod b  is greater than 0
// Step 5:  GCD = b
// Step 6: Finish
int gcd(int a, int b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;

    int r;
    while ((a % b) > 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return b;
}

char *gcdOfStrings(char *str1, char *str2) {
    size_t str1_len = strlen(str1);
    size_t str2_len = strlen(str2);
    size_t len = str1_len + str2_len;

    char *str1str2 = malloc(sizeof(char) * len + sizeof(char));
    str1str2[0] = '\0';
    str1str2 = strncat(str1str2, str1, str1_len);
    str1str2 = strncat(str1str2, str2, str2_len);

    char *str2str1 = malloc(sizeof(char) * len + sizeof(char));
    str2str1[0] = '\0';
    str2str1 = strncat(str2str1, str2, str2_len);
    str2str1 = strncat(str2str1, str1, str1_len);

    if (strcmp(str1str2, str2str1) != 0) {
        char *empty = malloc(sizeof(char));
        empty[0] = '\0';
        return empty;
    }
    free(str1str2);
    free(str2str1);

    int gcd_num = gcd(str1_len, str2_len);
    char *output = malloc(sizeof(char) * gcd_num + sizeof(char));
    strncpy(output, str1, gcd_num);
    output[gcd_num] = '\0';

    return output;
}

void test_gcd() {
    int example1 = gcd(270, 192);
    printf("example1 = %d\n", example1);
    assert(example1 == 6);

    printf("** GCD Tests Passed **\n");
}

int main() {

    test_gcd();

    char *example1 = gcdOfStrings("ABCABC", "ABC");
    printf("example1 = %s\n", example1);
    assert(strcmp(example1, "ABC") == 0);
    free(example1);

    char *example2 = gcdOfStrings("ABABAB", "ABAB");
    printf("example2 = %s\n", example2);
    assert(strcmp(example2, "AB") == 0);
    free(example2);

    char *example3 = gcdOfStrings("LEET", "CODE");
    printf("example3 = %s\n", example3);
    assert(strcmp(example3, "") == 0);
    free(example3);

    printf("*** All tests passed\n");

    return 0;
}
