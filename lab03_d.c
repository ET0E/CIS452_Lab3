#include <unistd.h>
#include <stdio.h>

int main() {
    // The list of args must end with a NULL
    execlp("cal", "some random string", "-3", "5", "2045", NULL);
    perror("After exec()");
    printf("Just checking\n");
    return 0;
}