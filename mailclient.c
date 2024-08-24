#include <stdio.h>
#include <stdlib.h>

#include "imap.h"
#include "config.h"

int main()
{
    struct imap_inbox_list *list = malloc(0);
    

    imap_init(IMAP, USER, PASSWD);
    imap_inbox_fetch(&list);
    imap_inbox_fetch(&list);
    
    return 0;
}
