#include <stdio.h>
#include <stdlib.h>

#include "imap.h"
#include "config.h"

int main()
{
    struct imap_inbox_meta meta;
    struct imap_inbox_list **list;

    list = malloc(sizeof(struct imap_inbox_list*));


    imap_init(IMAP, USER, PASSWD);
    imap_inbox_fetch_meta("INBOX", &meta);
    imap_inbox_fetch_list("INBOX", meta.exists, list);

    imap_cleanup();
    return 0;
}
