PROG=xmailclient
SRCS=imap.c table.c
CFLAGS+=-Wall
LDFLAGS+=-lcurl -lXm -lXt -lX11
MAN=

.include <bsd.prog.mk>

