//
// Created by gomonuk on 23.12.18.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void about(void) {
    printf("Python + C++ = ctypes\n");
}

int simple_function(void) {
    static int counter = 0;
    counter++;
    return counter;
}

void add_one_to_string(char *input) {
    int ii = 0;
    for (; ii < strlen(input); ii++) {
        input[ii]++;
    }
}

char * alloc_C_string(void) {
    char* phrase = strdup("I was written in C");
    printf("C just allocated %p(%ld):  %s\n",
           phrase, (long int)phrase, phrase);
    return phrase;
}

void free_C_string(char* ptr) {
    printf("Free %p(%ld):  %s\n",
           ptr, (long int)ptr, ptr);
    free(ptr);
}
