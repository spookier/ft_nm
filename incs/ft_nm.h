#ifndef FT_NM_H
#define FT_NM_H

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

void *init_file_mapping(char *filename, size_t *filesize);

#endif
