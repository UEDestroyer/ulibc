#include "io/gnu.h"

size_t __fpending(struct FILE *stream){
    if (stream == NULL || !(stream->mode & PROT_WRITE)){
        return 0;
    }
    return stream->buffer_pos;
}
int __freading(struct FILE *stream){
    if (stream == NULL || !(stream->mode & PROT_READ)){
        return -1;
    }
    return stream->buffer_len;
}