//mchek.h
#ifndef __MCHECK_H
#define __MCHECK_H

enum mcheck_status
{
  MCHECK_DISABLED, MCHECK_OK, MCHECK_FREE, MCHECK_HEAD, MCHECK_TAIL
};

int mcheck (void (*abortfunc)(enum mcheck_status mstatus));
int mcheck_pedantic (void (*abortfunc)(enum mcheck_status mstatus));
void mcheck_check_all ();
enum mcheck_status mprobe (void *ptr);

#endif