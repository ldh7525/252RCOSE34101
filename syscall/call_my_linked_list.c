#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define add 335    // system call number for os2025_add
#define insert 336 // system call number for os2025_insert
#define delete 337 // system call number for os2025_remove
#define NUM_RANDOMS 6

int main(void)
{
    srand(time(NULL));

    int random_values[NUM_RANDOMS];

    printf("--- 1. Calling 'add' system call (add to front with random values) ---\n");

    for (int i = 0; i < 3; i++)
    {
        int r = rand() % 1000;
        random_values[i] = r;

        syscall(add, r);
        printf("Add : %d\n", r);
    }

    printf("\n--- 2. Calling 'insert' system call (insert after a node) ---\n");

    for (int i = 3; i < 6; i++)
    {
        int r = rand() % 1000;
        random_values[i] = r;

        syscall(insert, random_values[i - 3]), r;
        printf("Insert : %d\n", r);
    }

    printf("\n--- 3. Calling 'remove' system call ---\n");

    for (int i = 0; i < NUM_RANDOMS; i++)
    {
        int r = random_values[i];
        syscall(delete, r);
        printf("Remove : %d\n", r);
    }

    return 0;
}
