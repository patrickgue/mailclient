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
    char from[STR_BUFF_LEN];
    char to[STR_BUFF_LEN];
    char cc[STR_BUFF_LEN];
    char bcc[STR_BUFF_LEN];
    char subject[STR_BUFF_LEN];
};

struct imap_login
{
    char username[STR_BUFF_LEN];
    char password[STR_BUFF_LEN];
};

int imap_init(char *, char *, char *);
void imap_inbox_fetch_meta(char *inbox, struct imap_inbox_meta*);

int imap_inbox_fetch_list(char *, int, struct imap_inbox_list **);
void imap_inbox_fetch_body(char *, int, char **, int *);
void imap_cleanup();

#endif
