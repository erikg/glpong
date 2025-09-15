#ifndef UTILS_H
#define UTILS_H

#if defined(_WIN32) || defined(__APPLE__)
const char* get_data_dir(void);
#else
#define get_data_dir() DATADIR
#endif

#endif /* UTILS_H */