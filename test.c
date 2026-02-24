#include "error.h"

int main(void) {
    warning("works? %d\n", 69);
    error_exit("will it exit? %d\n", 67);
}