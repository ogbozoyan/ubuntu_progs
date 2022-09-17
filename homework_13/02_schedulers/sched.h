#ifndef __OS_SCHEDULER_H__
#define __OS_SCHEDULER_H__
#ifdef __cplusplus
#  define EXTERN extern "C"
#else
#  define EXTERN
#endif // __cplusplus

EXTERN int sched_init(void);
EXTERN void sched_clean(void);
EXTERN int add_proc(void);
EXTERN int sched(int time, int cont);
EXTERN int sched_fin(void);

#endif
