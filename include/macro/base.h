#define DEF_SYSCALL_ERR(type, name, params, call) \
type name params {                               \
    long res = (long) ue_##name call;                   \
    if (res < 0) { __set_errno(-res); return (type) -1; } \
    return (type) res;                                  \
}

#define DEF_SYSCALL_FREE(type, name, params, call) \
type name params {                               \
    return (type) ue_##name call;                                  \
}



#if ERRNO_MACRO
#define DEF_SYSCALL(type, name, params, call) DEF_SYSCALL_ERR(type, name, params, call)
#else
#define DEF_SYSCALL(type, name, params, call) DEF_SYSCALL_FREE(type, name, params, call)
#endif