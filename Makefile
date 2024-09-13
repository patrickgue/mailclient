PROG=xmailclient
SRCS=xmailclient.c imap_mock.c editor.c viewer.c encoding.c inbox_folder_select.c
CFLAGS+=-Wall
LDFLAGS+=-lcurl -lXm -lXt -lX11
MAN=

.include <bsd.prog.mk>
