#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <parsing.h>
#include <file.h>

struct _file {
    int fd;
    long long unsigned int size;
    char *buff_ptr;
    char *buffer;
};

file_t *file_read(const char *fname) {
    file_t *file = (file_t *)malloc(sizeof(file_t));
    file->fd = open(fname, O_RDONLY, S_IRUSR | S_IWUSR);
    struct stat st;

    if (fstat(file->fd, &st) == -1)
        perror("Couldn't get file size\n");

    file->size = st.st_size;
    file->buffer = mmap(NULL, file->size, PROT_READ, MAP_PRIVATE, file->fd, 0);
    file->buff_ptr = file->buffer;

    return file;
}

slice_t file_slice(const file_t *file) {
    slice_t slice = {
        .ptr  = file->buffer,
        .size = file->size,
    };
    return slice;
}

bool file_eof(file_t *file) {
    return file->buff_ptr - file->buffer >= file->size;
}

void file_close(file_t *file) {
    close(file->fd);
    munmap(file->buffer, file->size);
    free(file);
}
