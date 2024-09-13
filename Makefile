PROG=xmailclient
SRCS=imap_mock.c table.c editor.c viewer.c encoding.c inbox_folder_select.c
CFLAGS+=-Wall
LDFLAGS+=-lcurl -lXm -lXt -lX11
MAN=

.include <bsd.prog.mk>
