#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"


struct FILE {
    int fd;
    
    unsigned char* buffer;
    size_t buffer_size;
    size_t buffer_pos;
    size_t buffer_len;
    
    int flags;
    
    int error;
    int eof;

    int mode;
};

#define FILE_FL_CLOSE (1u << 0)