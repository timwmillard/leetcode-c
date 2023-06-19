#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n) {

    for (int i = 0; i < flowerbedSize; i++) {
        bool plot = flowerbed[i];
        bool left = false;
        bool right = false;
        if (i > 0)
            left = flowerbed[i-1];
        if (i < flowerbedSize - 1)
            right = flowerbed[i+1];

        bool canPlant = !plot && !left && !right;
        if (canPlant) {
            flowerbed[i] = true;
            n--;
        }
    }
    return n <= 0;
}

int main() {

    struct test {
        char *name;
        int *flowerbed;
        int flowerbedSize;
        int n;
        bool output;
    };

    struct test tests[] = {
        {
            .name = "Example 1",
            .flowerbed = (int[]){1, 0, 0, 0, 1},
            .flowerbedSize = 5,
            .n = 1,
            .output = true
        },
        {
            .name = "Example 2",
            .flowerbed = (int[]){1, 0, 0, 0, 1},
            .flowerbedSize = 5,
            .n = 2,
            .output = false
        },
        {
            .name = "Example 3",
            .flowerbed = (int[]){1, 0, 0, 0, 0, 1},
            .flowerbedSize = 6,
            .n = 2,
            .output = false 
        },
        {
            .name = "Example 4",
            .flowerbed = (int[]){0, 0, 1, 0, 1},
            .flowerbedSize = 5,
            .n = 1,
            .output = true
        }
    };

    for (int i = 0; i < 4; i++) {
        struct test t = tests[i];

        bool got1 = canPlaceFlowers(t.flowerbed, t.flowerbedSize, t.n);
        printf("%s = %s\n", t.name, got1? "true" : "false");
        assert(got1 == t.output);
    }


    printf("\n***** All test passed ******\n");

    return 0;
}
