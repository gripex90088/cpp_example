#ifndef  LINUX_UNIX_PROGRAMMING_MANUAL_LIB_ERROR_FUNCTIONS_H_
#define  LINUX_UNIX_PROGRAMMING_MANUAL_LIB_ERROR_FUNCTIONS_H_

void errMsg(const char * format,  ...);

#ifdef  __GNUC__

/*
* This macro stops 'gcc -Wall' complaining that "control reaches
*       end if non-void function" if we use the following functions to
*       terminate main() or some other non-void function. */
#define NORETURN __attribute__ ((__noreturn__))
#else
#define NORETURN
#endif

void errExit(const char *format, ...) NORETURN;

void err_exit(const char *format, ...) NORETURN;

void errExitEn(int errnum, const char *format, ...) NORETURN;

void fatal(const char *format, ...) NORETURN;

void usageErr(const char *format, ...) NORETURN;

void cmdLineErr(const char *format, ...) NORETURN;

#endif /*  LINUX_UNIX_PROGRAMMING_MANUAL_LIB_ERROR_FUNCTIONS_H_ */
