PROG=xmailclient
SRCS=imap_mock.c table.c
CFLAGS+=-Wall
LDFLAGS+=-lcurl -lXm -lXt -lX11
MAN=

.include <bsd.prog.mk>


