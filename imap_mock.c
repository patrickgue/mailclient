#include <string.h>
#include <stdlib.h>

#include "imap.h"

int imap_init(char *uri, char *user, char *passwd)
{
    /* Nothing */
    return 1;
}

void imap_inbox_fetch_meta(char *inbox, struct imap_inbox_meta *meta)
{
    meta->exists = 3;
    meta->recent = 0;
}

int imap_inbox_fetch_list(char *inbox, int items, struct imap_inbox_list **list)
{
    int i;
    (*list) = malloc(sizeof(struct imap_inbox_list) * items);

    strcpy((*list)[0].subject, "Re: Letter");
    strcpy((*list)[0].from,    "Alice <alice@mail.com>");
    strcpy((*list)[0].to,      "Me <me@mail.com>");
    strcpy((*list)[0].cc,      "");
    strcpy((*list)[0].bcc,     "");
    
    strcpy((*list)[1].subject, "Newsletter about XYZ");
    strcpy((*list)[1].from,    "News <news@xyz.com>");
    strcpy((*list)[1].to,      "Me <me@mail.com>");
    strcpy((*list)[1].cc,      "");
    strcpy((*list)[1].bcc,     "");


    for (i = 2; i < items; i++)
    {
        sprintf((*list)[i].subject, "Fwd: blabla %d", i);
        strcpy((*list)[i].from,    "Bob <bob@mail.com>");
        strcpy((*list)[i].to,      "Me <me@mail.com>");
        strcpy((*list)[i].cc,      "");
        strcpy((*list)[i].bcc,     "");
    }
    return items;
}

void imap_cleanup()
{
    /* Nothing */
}
