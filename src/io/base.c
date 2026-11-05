#include "io/base.h"


DEF_SYSCALL(ssize_t,read,(int fd, void *buf, size_t count),(fd,buf,count))
DEF_SYSCALL(ssize_t,write,(int fd,const void *buf, size_t count),(fd,buf,count))
DEF_SYSCALL(int,close,(int fd),(fd))


int open(const char *pathname, int flags, ...)
{
    mode_t mode = 0;

    if ((flags & O_CREAT) || ((flags & O_TMPFILE) == O_TMPFILE)) {
        va_list va;
        va_start(va, flags);
        mode = va_arg(va, mode_t);
        va_end(va);
    }

    
    int res = ue_open(pathname, flags, mode);
    if (res < 0) {
        __set_errno(-res);
        return -1;
    }

    return res;
}

int creat(const char *pathname, mode_t mode){
    return ue_open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);
}


DEF_SYSCALL(off_t,lseek,(int fd, off_t offset, int whence),(fd,offset,whence))

DEF_SYSCALL(int,dup,(int oldfd),(oldfd))

DEF_SYSCALL(int,dup2,(int oldfd,int newfd),(oldfd,newfd))

DEF_SYSCALL(int,pipe,(int pipefd[2]),(pipefd))

DEF_SYSCALL(ssize_t,pread,(int fd, void *buf, size_t count, off_t offset),(fd,buf,count,offset))

DEF_SYSCALL(ssize_t,pwrite,(int fd,const void *buf, size_t count, off_t offset),(fd,buf,count,offset))

DEF_SYSCALL(int,ftruncate,(int fd, off_t lenght),(fd,lenght))

DEF_SYSCALL(int,fsync,(int fd),(fd))
DEF_SYSCALL(int, fdatasync,(int fd), (fd))

int fcntl(int fd, int cmd, ...){
    unsigned long arg = 0;
    switch (cmd) {
        case F_GETFD:
        case F_GETFL:
        case F_GETOWN:
            break;
        case F_DUPFD:
        case F_SETFD:
        case F_SETFL:
        case F_DUPFD_CLOEXEC:
        case F_SETOWN:
        case F_SETSIG:
        {
            va_list ap;
            va_start(ap,cmd);
            arg = (unsigned long)va_arg(ap,int);
            va_end(ap);
            break;
        }
        case F_GETLK:
        case F_SETLK:
        case F_SETLKW:
        case F_OFD_GETLK:
        case F_OFD_SETLK:
        case F_OFD_SETLKW:
        {
            va_list ap;
            va_start(ap,cmd);
            arg = (unsigned long)va_arg(ap,struct flock*);
            va_end(ap);
            break;
        }
        case F_GETOWN_EX:
        case F_SETOWN_EX:
        {
            va_list ap;
            va_start(ap,cmd);
            arg = (unsigned long)va_arg(ap,struct f_owner_ex*);
            va_end(ap);
            break;
        }
        default:
            __set_errno(EINVAL);
            return -1;
    } 

    int res = ue_fcntl(fd,cmd,arg);
    if (res < 0 && !(cmd == F_GETOWN && res>-4096 && res < 0)){
        __set_errno(-res);
        return -1;
    }return res;
}