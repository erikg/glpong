#ifndef UTILS_H
#define UTILS_H

#ifdef _WIN32
const char* get_data_dir(void);
#else
#define get_data_dir() DATADIR
#endif

#endif /* UTILS_H */