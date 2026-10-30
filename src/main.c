/* main.c - main */

#define	_USE_BSD
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/errno.h>
#include <netinet/in.h>

#include <server.h>
#include <http.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define	QLEN		  32	/* maximum connection queue length	*/
#define	BUFSIZE		4096

extern int	errno;

int	errexit(const char *format, ...);
int	passiveTCP(const char *service, int qlen);

/*------------------------------------------------------------------------
 * main - Concurrent TCP server for HTTP service
 *------------------------------------------------------------------------
 */
int
main(void)
{
    struct	sockaddr_in fsin;	/* the address of a client	*/
	unsigned int	alen;		/* length of client's address	*/
	int	sd;			/* master server socket		*/
	int	nsd;			/* slave server socket		*/
    char	buf[BUFSIZE];			/* "input" buffer; any size > 0	*/
    ssize_t n;
    const char *url;
    int fd;
    char    fbuf[BUFSIZE];
    size_t nf;
    ssize_t nr;

    sd = passiveTCP("http", QLEN);

    while (1){
        alen = sizeof(fsin);
        nsd = accept(sd, (struct sockaddr *)&fsin, &alen);
        if (nsd < 0)
			errexit("accept failed: %s\n", strerror(errno));
        n = recv(nsd, buf, n, 0); //
        url = parsing(buf);
        nf = sizeof(buf);
        fd = open(url, O_RDONLY);
            while(read(fd, fbuf, nf){
                nr = read(fd, fbuf, nf);
                send(nsd, fbuf, nr, 0);
            }
            close(fd);
            close(nsd);
    }

}