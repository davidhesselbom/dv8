#ifndef EXCEPTION_SYSCALL_H
#define EXCEPTION_SYSCALL_H

#include "utils.h"

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

void
execute_syscall(cause_reg_t cause);

#endif
