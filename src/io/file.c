#include "io/file.h"

static unsigned char stdout_buffer[4096];

static struct FILE stdout_file = {
    .fd = 1,

    .buffer = stdout_buffer,
    .buffer_size = sizeof(stdout_buffer),
    .buffer_pos = 0,
    .buffer_len = 0,

    .flags = 0,

    .error = 0,
    .eof = 0,

    .mode = PROT_READ | PROT_WRITE,
};

static struct FILE stderr_file = {
    .fd = 2,

    .buffer = NULL,
    .buffer_size = 0,
    .buffer_pos = 0,
    .buffer_len = 0,

    .flags = 0,

    .error = 0,
    .eof = 0,

    .mode = PROT_READ | PROT_WRITE,
};



struct FILE* stdout = &stdout_file;
struct FILE *stderr = &stderr_file;
// FILE constants ended

int fileno(struct FILE *stream){
    if (stream == NULL || (stream->flags & FILE_FL_CLOSE) == FILE_FL_CLOSE){
        __set_errno(EBADF);
        return -1;
    }
    return stream->fd;
}


static int __stdio_write_buffer(struct FILE *stream){
    if (stream == NULL ){
        __set_errno(EINVAL);
        return -1;
    }if ((stream->flags & FILE_FL_CLOSE) == FILE_FL_CLOSE || (stream->mode & PROT_WRITE) == PROT_WRITE ){
        __set_errno(EBADF);
        return stream->eof;
    }if (stream->buffer == NULL || stream->buffer_pos > stream->buffer_size){
        __set_errno(EINVAL);
        return stream->eof;
    }if (stream->buffer_pos==0) return 0;

    size_t written = 0;
    
    while (written < stream->buffer_pos){
        ssize_t res = ue_write(stream->fd,stream->buffer + written,stream->buffer_pos - written);
        if (res > 0){
            written+=res;
        } else {
            if (res == EINTR){
                continue;
            }else{
                if (res != 0){
                    stream->error = -res;
                }
                break;
            }
        }
        if (written < stream->buffer_pos){
            memmove(stream->buffer, stream->buffer + written, stream->buffer_pos - written);
            written=stream->buffer_pos;
        }

        if (written==stream->buffer_pos){
            stream->buffer_pos = 0;
            return 0;
        }


    }

}

int fflush_unlocked(struct FILE *stream){
    
}