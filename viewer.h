#ifndef viewer_h
#define viewer_h

#include "imap.h"

void view_email_window(Widget toplevel, struct imap_inbox_list *item, char *content);

#endif
