#ifndef ACTIONS_H
#define ACTIONS_H

#include <stdbool.h>

typedef enum {
    NORMAL,
    DEBUG,
    DIAGNOSTIC
} Verbosity;


/**
 * Arguments for the 'build' sub-command.
 */
typedef struct {
    Verbosity verbosity;
    char* projectFilePath;
    char* outputDirPath;
    bool warnAsErr;
} BuildArgs;


/**
 * Arguments for the 'run' sub-command.
 */
typedef struct {
    Verbosity verbosity;
    char* projectFilePath;
    char* outputDirPath;
    bool warnAsErr;
} RunArgs;


/**
 * Arguments for the 'init' sub-command.
 */
typedef struct {
    Verbosity verbosity;
    char* initDirPath;
    char* projectName;
    bool initGit;
} InitArgs;


/**
 * Builds the specified project.
 * @param build_args The 'build' command arguments.
 * @return 0 if successful, other value otherwise.
 */
int
build_project(BuildArgs build_args);


/**
 * Build (if applicable) and run the specified project.
 * @param run_args The 'run' command arguments.
 * @return 0 if successful, other value otherwise.
 */
int
run_project(RunArgs run_args);


/**
 * Initializes a new project.
 * @param init_args The 'init' command arguments.
 * @param out_error Corresponding error message, if any.
 * @return 0 if successful, other value otherwise.
 */
bool
init_project(InitArgs init_args, char** out_error);

#endif
