/* Our own header, to be include *after* all standard system headers */

#ifndef LINUX_UNIX_PROGRAMMING_MANUAL_SRC_OURHDR_H_
#define LINUX_UNIX_PROGRAMMING_MANUAL_SRC_OURHDR_H_

#include <sys/types.h>	/* required for some of our prototypes */
#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */

#define MAXLINE	4069	/* max line length */

#define FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */

typedef void Sigfunc(int); /* for signal handlers */

				/* 4.3BSD Reno <signal.h> doesn't define SIG_ERR */
#if defined(SIG_IGN) && !defined(SIG_ERR)
#define SIG_ERR ((Sigfunc *)-1)
#endif

#define min(a, b)	((a) < (b) ? (a) : (b))
#define max(a, b)	((a) > (b) ? (a) : (b))

				/* prototypes for our own functions */
char	*path_alloc(int *);		/* Program 2.2 */
int 	open_max(void);			/* Program 2.3 */
void	clr_fl(int, int);		/* Program 3.5 */
void 	set_fl(int, int);		/* Program 3.5 */
void 	pr_exit(int);			/* Program 8.3 */
void 	pr_mask(const char *);	/* Program 10.10 */
Sigfunc *signal_intr(int, Sigfunc *);/* Program 10.13 */

int		tty_cbreak(int);		/* Program 11.10 */
int		tty_raw(int);			/* Program 11.10 */
int 	tty_reset(int);			/* Program 11.10 */
void	tty_atexit(void);		/* Program 11.10 */
#ifdef ECHO	/* only if <termios.h> has been included */
struct termios *tty_termios(void);	/* Program 11.10 */
#endif

void	 sleep_us(unsigned int);/* Exercise 12.6 */
ssize_t  readn(int, void *, size_t);/* Program 12.13 */
ssize_t	 writen(int, const void *, size_t);/* Program 12.12 */
int 	 daemon_init(void);		/* Program 13.1 */

int		 s_pipe(int *);			/* Program 15.2 and 15.3 */
int		 recv_fd(int, ssize_t (*func)(int, const void *, size_t));
								/* Program 15.6 and 15.8 */
int send_fd(int, int);			/* Program 15.5 and 15.7*/

#endif /* LINUX_UNIX_PROGRAMMING_MANUAL_SRC_OURHDR_H_ */
