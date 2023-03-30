#include <stdlib.h>

#define DEPTH 8


void branching_function (int);

void function_0 (int depth) { branching_function (depth); }
void function_1 (int depth) { branching_function (depth); }
void function_2 (int depth) { branching_function (depth); }
void function_3 (int depth) { branching_function (depth); }

void branching_function (int depth) {
    if (depth > 0) {
        switch (rand () % 4) {
            case 0: function_0 (depth - 1); break;
            case 1: function_1 (depth - 1); break;
            case 2: function_2 (depth - 1); break;
            case 3: function_3 (depth - 1); break;
        }
    }
}


int main () {
    function_0 (DEPTH);
    return (0);
}
