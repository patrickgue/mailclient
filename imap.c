#include "imap.h"
#include <string.h>

CURL *curl;
struct imap_inbox_list *result;

#define DELIM "\n\r"

size_t imap_inbox_process_list(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    char *tok;
    
    tok = strtok(ptr, DELIM);
    do
    {
        printf("LINE: '%s'\n", tok);
    } while ((tok = strtok(NULL, DELIM)) != NULL);
    
    return 1;
}

int imap_init(char *uri, char *user, char *passwd)
{
    curl = curl_easy_init();
    
    curl_easy_setopt(curl, CURLOPT_USERNAME, user);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, passwd);
    curl_easy_setopt(curl, CURLOPT_URL, uri);

    return curl != 0;
}

void imap_cleanup()
{
    curl_easy_cleanup(curl);
}

void imap_inbox_fetch(struct imap_inbox_list **)
{
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, imap_inbox_process_list); 
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "SELECT INBOX");
    curl_easy_perform(curl);
}
