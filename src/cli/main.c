#include <stdio.h>
#include <argtable3.h>
#include <stdlib.h>

#include "actions.h"


int main(int argc, char *argv[]) {
    char* init_dir_path = "C:\\Users\\bryan\\Documents\\temp_c";
    char* project_name = "LispProject";
    InitArgs init_args = {
        NORMAL,
        init_dir_path,
        project_name,
        false
    };

    char* err = NULL;
    init_project(init_args, &err);

    if (err) {
        printf("%s\n", err);
    }
/*
    struct arg_lit *verbose = arg_lit0("v", "verbose", "Enable verbose output");
    struct arg_int *count = arg_int0("n", "number", "<n>", "Number of iterations");
    struct arg_end *end = arg_end(20);

    void *argtable[] = { verbose, count, end };

    int nerrors = arg_parse(argc, argv, argtable);
    if (nerrors > 0) {
        arg_print_errors(stderr, end, argv[0]);
        arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
        return 1;
    }

    printf("Verbose: %s\n", verbose->count ? "yes" : "no");
    printf("Number: %d\n", count->count ? count->ival[0] : 0);

    arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
 */
    return 0;
}
