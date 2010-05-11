#ifndef KERNEL_H
#define KERNEL_H

#include "utils.h"
#include "pcb.h"

/*
 * ---------------------------------------------------------------------------
 * Functions.
 * ---------------------------------------------------------------------------
 */

void
save_process_state(pcb_t *pcb);

void
restore_process_state(const pcb_t *pcb);

uint32_t
kexec(user_prog_pointer program, uint32_t);

uint32_t
kgetpid(void);

uint32_t
getpid(void);

void
kkill_self(void);

void
kinit(void);

void
kexception(void);

void
ksleep(int time);

#endif
