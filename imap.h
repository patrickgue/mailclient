#ifndef IMAP_H
#define IMAP_H

#include <curl/curl.h>

#define STR_BUFF_LEN 128

struct imap_inbox_meta
{
    int exists;
    int recent;
};

struct imap_inbox_list
{
    char sender[STR_BUFF_LEN];
    char subject[STR_BUFF_LEN];
};

struct imap_login
{
    char username[STR_BUFF_LEN];
    char password[STR_BUFF_LEN];
};

int imap_init(char *, char *, char *);
void imap_inbox_fetch_meta(char *inbox, struct imap_inbox_meta*);
void imap_inbox_fetch(struct imap_inbox_list **);
void imap_cleanup();

#endif
