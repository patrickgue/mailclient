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
        strcpy((*list)[i].from,    "B=C3=B6b <bob@mail.com>");
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


void imap_inbox_fetch_body(char *inbox, int index, char **buff, int *s)
{
    char dummy[] = "The browse and single selection modes only allow the selection of a single item. The \
browsing mode is regarded as a simpler interface for the user. Interactively, browse \
selection allows the user to drag the selection over many items; the selection is not made \
till the mouse button is released. In the single selection mode, the selection is made as soon \
as the mouse button is pressed. For browse selection, the callback list associated with the \
XmNbrowseSelectionCallback is used, while the XmNsingleSelectionCallback \
is used for the single selection mode.\n";
    int size = (strlen(dummy) + 1) * sizeof(char);
    (*buff) = malloc(size);
    if (*buff == NULL)
    {
        fprintf(stderr, "Unable to allocate memory\n");
        exit(1);
    }
    strncpy(*buff, dummy, size);
    *s = size;
}
