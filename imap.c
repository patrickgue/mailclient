
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "imap.h"

CURL *curl;
struct imap_inbox_meta *meta;
struct imap_inbox_list **list;
int list_index = 0;


#define DELIM "\n\r"

size_t memory_callback(char *contents, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb;
    struct s_memory *mem = (struct s_memory *)userdata;

    char *ptr = realloc(mem->buff, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
    mem->buff = ptr;
    memcpy(&(mem->buff[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->buff[mem->size] = 0;

    return realsize;
}

size_t imap_inbox_process_meta(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    char *tok, buff[STR_BUFF_LEN];
    int i, exists, recent;

    tok = strtok(ptr, DELIM);
    while (tok != NULL)
    {
        exists = strstr(tok, "EXISTS") != NULL;
        recent = strstr(tok, "RECENT") != NULL;
        if (exists || recent)
        {
            strncpy(buff, tok, STR_BUFF_LEN);
            /* skip '* ' -> start at index 2 */
            for (i = 2; i < strlen(buff) && i < STR_BUFF_LEN; i++)
            {
                if (buff[i] == ' ')
                {
                    buff[i] = 0;
                    break;
                }
            }
            if (exists)
                meta->exists = atoi(buff + 2);
            else if (recent)
                meta->recent = atoi(buff + 2);
        }
        tok = strtok(NULL, DELIM);
    }

    return size * nmemb;
}

size_t imap_inbox_process_header(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    int subject, from, to, cc, bcc;
    char *tok;

    tok = strtok(ptr, DELIM);

    while (tok != NULL)
    {
        subject = strstr(tok, "Subject") != NULL;
        from = strstr(tok, "From:") != NULL;
        to = strstr(tok, "To:") != NULL;
        cc = strstr(tok, "CC:") != NULL;
        bcc = strstr(tok, "BCC:") != NULL;

        if (subject || from || to || cc || bcc)
        {
            if (subject)
                strncpy((*list)[list_index].subject, tok + strlen("Subject: "), STR_BUFF_LEN);
            else if (to)
                strncpy((*list)[list_index].to, tok + strlen("To: "), STR_BUFF_LEN);
            else if (from)
                strncpy((*list)[list_index].from, tok + strlen("From: "), STR_BUFF_LEN);
            else if (cc)
                strncpy((*list)[list_index].cc, tok + strlen("CC: "), STR_BUFF_LEN);
            else if (bcc)
                strncpy((*list)[list_index].bcc, tok + strlen("BCC: "), STR_BUFF_LEN);
        }
        tok = strtok(NULL, DELIM);
    }

    return size * nmemb;
}

int imap_init(char *uri, char *user, char *passwd)
{
    curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_USERNAME, user);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, passwd);
    curl_easy_setopt(curl, CURLOPT_URL, uri);
    // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    return curl != 0;
}

void imap_cleanup()
{
    curl_easy_reset(curl);
    curl_easy_cleanup(curl);
}

void imap_inbox_fetch_meta(char *inbox, struct imap_inbox_meta *m)
{
    meta = m;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, imap_inbox_process_meta);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SELECT INBOX");

    curl_easy_perform(curl);
    printf("Exists: %d\nRecent: %d\n", meta->exists, meta->recent);
}


int imap_inbox_fetch_list(char *inbox, int n, struct imap_inbox_list **l)
{
    char request[128];
    int i;

    list = l;
    (*list) = malloc(n * sizeof(struct imap_inbox_list));

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, imap_inbox_process_header);

    for (i = 1; i <= n; i++)
    {
        sprintf(request, "FETCH %d BODY[HEADER.FIELDS (SUBJECT TO FROM CC BCC)]", i);
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request);
        list_index  = i - 1;
        curl_easy_perform(curl);
    }

    return list_index;
}


void imap_inbox_fetch_body(char *inbox, int index, char **buff, int *s)
{
    char request[128];
    struct s_memory mem, header;
    mem.buff = malloc(0);
    mem.size = 0;
    header.buff = malloc(0);
    header.size = 0;
    sprintf(request, "FETCH %d BODY[TEXT]", index);

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, request);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, memory_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &mem);
    curl_easy_perform(curl);

    /* for some reason body is stored in header:
       https://stackoverflow.com/questions/63661473/c-libcurl-responses-only-show-first-line-of-response
    */
    *buff = header.buff;
    *s = mem.size;
}

struct imap_inbox_folder_item **inbox_list;
size_t inbox_list_size;

size_t imap_inbox_process_list(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    char *tok, buff_arr[STR_BUFF_LEN], *buff;
    int i;
    buff = buff_arr;

    tok = strtok(ptr, DELIM);
    i = 0;

    while (tok != NULL)
    {
        strncpy(buff_arr, tok, STR_BUFF_LEN);
        buff = buff_arr;
        while (strstr(buff, " \".\" ") != buff && i < STR_BUFF_LEN - 5)
        {
            buff++; i++;
        }
        buff += 5;
        *inbox_list = realloc(*inbox_list, (inbox_list_size + 1) * sizeof(struct imap_inbox_folder_item));
        strncpy((*inbox_list)[inbox_list_size].item, buff, STR_BUFF_LEN);
        inbox_list_size++;
        tok = strtok(NULL, DELIM);
    }

    return nmemb * size;
}

void imap_inbox_fetch_folder_list(struct imap_inbox_folder_item **list, size_t *s)
{
    struct s_memory mem;
    char *tok, buff_arr[STR_BUFF_LEN], *buff;
    int i;
    mem.buff = malloc(0);
    mem.size = 0;

    inbox_list_size = 0;
    inbox_list = list;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&mem);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "LSUB \"\" *");
    curl_easy_perform(curl);

    buff = buff_arr;

    tok = strtok(mem.buff, DELIM);
    i = 0;

    while (tok != NULL)
    {
        strncpy(buff_arr, tok, STR_BUFF_LEN);

        i = 0;
        buff = buff_arr;
        while (strstr(buff, " \".\" ") != buff && i < STR_BUFF_LEN - 5)
        {
            buff++; i++;
        }
        buff += 5;
        *inbox_list = realloc(*inbox_list, (inbox_list_size + 1) * sizeof(struct imap_inbox_folder_item));
        strncpy((*inbox_list)[inbox_list_size].item, buff, STR_BUFF_LEN);
        inbox_list_size++;
        tok = strtok(NULL, DELIM);
    }

    *s = inbox_list_size;
    printf("Inbox List Size: %ld\n", inbox_list_size);
}
