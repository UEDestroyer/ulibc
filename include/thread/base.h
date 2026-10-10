#include "low-access-UEDestroyer/defines/x86_64/linux.h"
#include "low-access-UEDestroyer/funcs/linux.h"
#include "types/base.h"
#include "mem/Fheap.h"
#include "defines/fcntl.h"
#include "asm/prctl.h"

int set_current_tls(struct ulibc_tls *tls);
struct ulibc_tls* get_current_tls();
struct ulibc_tls *tls_create(void);
void tls_destroy(struct ulibc_tls *tls);
int thread_init(void);