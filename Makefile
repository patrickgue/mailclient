PROG=mailclient
SRCS=imap.c mailclient.c
LDFLAGS+=-lcurl -lXm -lXt -lX11
MAN=

.include <bsd.prog.mk>

