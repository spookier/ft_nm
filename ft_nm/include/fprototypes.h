#ifndef FPROTOTYPES_H
# define FPROTOTYPES_H

int start_parsing(int argc, char **argv);

// ELF64 header parsing
int e_64hdr_parse(void *mapped_memory, size_t size);


// ----------------

// ELF32 HEADER PARSING;
int e_32hdr_parse(void *mapped_memory, size_t size);


#endif