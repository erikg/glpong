#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>

static char data_dir_path[MAX_PATH];
static int data_dir_initialized = 0;

const char* get_data_dir(void) {
    if (!data_dir_initialized) {
        char exe_path[MAX_PATH];
        char* last_slash;

        // Get the executable path
        if (GetModuleFileName(NULL, exe_path, MAX_PATH) != 0) {
            // Find the last backslash to get directory
            last_slash = strrchr(exe_path, '\\');
            if (last_slash != NULL) {
                *last_slash = '\0'; // Remove filename, keep directory
                // Construct the data directory path
                snprintf(data_dir_path, MAX_PATH, "%s\\%s", exe_path, DATADIR_RELATIVE);
            } else {
                // Fallback to relative path
                strcpy(data_dir_path, DATADIR_RELATIVE);
            }
        } else {
            // Fallback to relative path
            strcpy(data_dir_path, DATADIR_RELATIVE);
        }
        data_dir_initialized = 1;
    }
    return data_dir_path;
}
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#include <limits.h>

static char data_dir_path[PATH_MAX];
static int data_dir_initialized = 0;

const char* get_data_dir(void) {
    if (!data_dir_initialized) {
        char exe_path[PATH_MAX];
        char* last_slash;
        uint32_t size = sizeof(exe_path);

        // Get the executable path
        if (_NSGetExecutablePath(exe_path, &size) == 0) {
            // Find the last slash to get directory
            last_slash = strrchr(exe_path, '/');
            if (last_slash != NULL) {
                *last_slash = '\0'; // Remove filename, keep directory
                // Construct the data directory path
                snprintf(data_dir_path, PATH_MAX, "%s/%s", exe_path, DATADIR_RELATIVE);
            } else {
                // Fallback to relative path
                strcpy(data_dir_path, DATADIR_RELATIVE);
            }
        } else {
            // Fallback to relative path
            strcpy(data_dir_path, DATADIR_RELATIVE);
        }
        data_dir_initialized = 1;
    }
    return data_dir_path;
}
#endif