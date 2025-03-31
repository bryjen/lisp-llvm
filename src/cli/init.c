#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "actions.h"


const char *toml_config_template =
    "# Project metadata\n"
    "name = \"%s\"\n"
    "version = \"0.1.0\"\n"
    "description = \"A sample app\"\n"
    "\n"
    "[author]\n"
    "name = \"author\"\n"
    "email = \"author@example.com\"\n"
    "\n"
    "[build]\n"
    "optimize = true\n"
    "target = \"arm64-windows\"\n"
    "\n"
    "[dependencies]\n"
    "llvm = \"3.2.1\"\n";


char*
get_abs_dir_path(const char *const dir_path, char** out_error) {
#ifdef _WIN32
    char *abs_dir_path = malloc(_MAX_PATH);

    if (_fullpath(abs_dir_path, dir_path, _MAX_PATH) == NULL) {
        const size_t buf_size = 100 * sizeof(char);
        char *buf = malloc(buf_size);
        sprintf_s(buf, buf_size, "\"%s\" is not a valid directory.", dir_path);
        *out_error = buf;

        free(abs_dir_path);
        return NULL;
    }

    return abs_dir_path;
#else
    *out_error = "Could not get 'get_abs_dir', an unknown error occurred.";
    return NULL;
#endif
}


bool
does_directory_exists(const char *const abs_dir_path) {
#ifdef _WIN32
    DWORD attrs = GetFileAttributesA(abs_dir_path);
    return (attrs != INVALID_FILE_ATTRIBUTES) && (attrs & FILE_ATTRIBUTE_DIRECTORY);
#else
    return false;
#endif
}


bool
does_directory_contain_files(const char *const abs_dir_path) {
    char search_path[MAX_PATH];
    snprintf(search_path, MAX_PATH, "%s\\*", abs_dir_path);

    WIN32_FIND_DATAA data;
    HANDLE h = FindFirstFileA(search_path, &data);
    if (h == INVALID_HANDLE_VALUE) return false;

    bool found = false;
    do {
        if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            found = true;
            break;
        }
    } while (FindNextFileA(h, &data));

    FindClose(h);
    return found;
}


bool
assert_directory_contains_no_files(const char *const abs_dir_path, char** out_error) {
    if (does_directory_contain_files(abs_dir_path)) {
        const size_t buf_size = 100 * sizeof(char);
        char *buf = malloc(buf_size);
        sprintf_s(buf, buf_size, "Cannot create a project at \"%s\", it is not empty.", abs_dir_path);
        *out_error = buf;

        return true;
    }

    return false;
}


bool
setup_dir(const char *const abs_dir_path, char** out_error) {
    if (does_directory_exists(abs_dir_path)) {
        char *assertion_error = NULL;
        if (assert_directory_contains_no_files(abs_dir_path, &assertion_error)) {
            *out_error = assertion_error;
            return false;
        }
    } else {
        if (!CreateDirectoryA(abs_dir_path, NULL)) {
            const size_t buf_size = 100 * sizeof(char);
            char *buf = malloc(buf_size);
            sprintf_s(buf, buf_size, "Cannot the directory \"%s\" with error code '%d'.", abs_dir_path, GetLastError());
            *out_error = buf;
            return false;
        }
    }

    return true;
}


bool
generate_sample_file(const char* const abs_dir_path, const char *const project_name, char** out_error) {
    const size_t buf_size = 100 * sizeof(char);
    char *file_contents = malloc(buf_size);
    sprintf_s(file_contents, buf_size, "(let [name \"World\"]\n(println (str \"Hello from \" %s \"!\")))", project_name);

    char *file_path = malloc(buf_size);
    sprintf_s(file_path, buf_size, "%s\\%s.clj", abs_dir_path, project_name);


    FILE *f = NULL;
    const errno_t err = fopen_s(&f, file_path, "w");

    if (err != 0 || !f) {
        char *file_open_err = malloc(buf_size);
        sprintf_s(file_open_err, buf_size, "Failed to generate the template file \"%s.clj\"", project_name);
        *out_error = file_open_err;

        free(file_contents);
        free(file_path);
        return false;
    }

    fprintf(f, "%s", file_contents);
    fclose(f);

    free(file_contents);
    free(file_path);
    return true;
}


bool
generate_sample_config_file(const char* const abs_dir_path, const char *const project_name, char** out_error) {
    const size_t buf_size = 400 * sizeof(char);
    char *file_contents = malloc(buf_size);
    sprintf_s(file_contents, buf_size, toml_config_template, project_name);

    char *file_path = malloc(buf_size);
    sprintf_s(file_path, buf_size, "%s\\%s.toml", abs_dir_path, project_name);


    FILE *f = NULL;
    const errno_t err = fopen_s(&f, file_path, "w");

    if (err != 0 || !f) {
        char *file_open_err = malloc(buf_size);
        sprintf_s(file_open_err, buf_size, "Failed to generate the template file \"%s.toml\"", project_name);
        *out_error = file_open_err;

        free(file_contents);
        free(file_path);
        return false;
    }

    fprintf(f, "%s", file_contents);
    fclose(f);

    free(file_contents);
    free(file_path);
    return true;
}


bool
init_project(const InitArgs init_args, char** out_error) {
    char* default_err_msg = "An unexpected error occurred.";

    char *get_abs_dir_err = NULL;
    char *abs_dir_path = get_abs_dir_path(init_args.initDirPath, &get_abs_dir_err);
    if (!abs_dir_path) {
        *out_error = get_abs_dir_err;
        return false;
    }

    char *setup_dir_err = NULL;
    if (!setup_dir(abs_dir_path, &setup_dir_err)) {
        *out_error = setup_dir_err ? setup_dir_err : default_err_msg;
        free(abs_dir_path);
        return false;
    }

    char *template_file_gen_err = NULL;
    if (!generate_sample_file(abs_dir_path, init_args.projectName, &template_file_gen_err)) {
        *out_error = template_file_gen_err ? template_file_gen_err : default_err_msg;
        free(abs_dir_path);
        return false;
    }

    char *template_config_file_gen_err = NULL;
    if (!generate_sample_config_file(abs_dir_path, init_args.projectName, &template_config_file_gen_err)) {
        *out_error = template_config_file_gen_err ? template_config_file_gen_err : default_err_msg;
        free(abs_dir_path);
        return false;
    }

    free(abs_dir_path);
    return true;
}
