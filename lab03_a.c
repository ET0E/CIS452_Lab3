#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    puts("Before fork");
    fork();
    sleep(60);
    puts("After fork");
    return 0;
}