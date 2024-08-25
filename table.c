/* rendered_list.c: illustrates all the features of
** render tables and renditions by creating a 
** multi-column, multi-font, multi-color List widget.
*/

#include <stdlib.h>

#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/List.h>

#include "config.h"
#include "imap.h"


#define MAX_COLUMNS    2
#define HELVETICA "-*-helvetica-bold-r-normal--12-*-*-*-*-*-iso8859-1"

/*
** CreateListData(): routine to convert the
** poem into an array of compound strings
*/
XmStringTable CreateListData (int *count)
{
    XmStringTable            table = (XmStringTable) 0;
    XmString                 row = (XmString) 0;
    XmString                 tmp = (XmString) 0;
    XmString                 tab;
    struct imap_inbox_list **entries;
    int                      entries_count, i;
    struct imap_inbox_meta   meta;

    tab = XmStringComponentCreate (XmSTRING_COMPONENT_TAB, 0, NULL);

    imap_init(IMAP, USER, PASSWD);
    imap_inbox_fetch_meta("INBOX", &meta);
    entries = malloc(sizeof(struct imap_inbox_list*));
    entries_count = imap_inbox_fetch_list("INBOX", meta.exists, entries);

    table = (XmStringTable) XtMalloc(sizeof(XmString) * entries_count);
    
    for (i = 0; i < entries_count; i++)
    {
        row = XmStringGenerate((XtPointer) (*entries)[i].from, NULL, XmCHARSET_TEXT, "");
        tmp = XmStringConcat(row, tab);
        row = XmStringConcatAndFree(tmp, XmStringGenerate((XtPointer) (*entries)[i].subject, NULL, XmCHARSET_TEXT, ""));
        table[i] = row;
            
    }
    
    XmStringFree (tab);

    table[entries_count] = (XmString) 0;

    *count = entries_count;
    return table;
}

int main (int argc, char *argv[])
{
    Widget             toplevel, rowcol, list;
    XtAppContext       app;
    Arg                args[10];
    XmTab              tabs[MAX_COLUMNS];
    XmTabList          tablist;
    XmRendition        renditions[MAX_COLUMNS];
    XmRenderTable      rendertable;
    XmStringTable      xmstring_table;
    int                xmstring_count;
    int                n, i;

    XtSetLanguageProc (NULL, NULL, NULL);
    toplevel = XtVaOpenApplication (&app, "Demos", NULL, 0, &argc, argv, NULL, 
                                    sessionShellWidgetClass, NULL);
    rowcol = XmCreateRowColumn (toplevel, "rowcol", NULL, 0);

   

    /* Create tab stops for columnar output */
    for (i = 0; i < MAX_COLUMNS; i++) {
        tabs[i] = XmTabCreate ((float) 4, 
                                XmINCHES, 
                                ((i == 0) ? XmABSOLUTE : XmRELATIVE),
                                XmALIGNMENT_BEGINNING, 
                                ".");
    }

    /* Create a tablist table which contains the tabs */
    tablist = XmTabListInsertTabs (NULL, tabs, XtNumber (tabs), 0);

    /* Create some multi-font/color renditions, and use the tablist */
    /* This will be inherited if we use it on the first rendition */
    for (i = 0; i < MAX_COLUMNS; i++) {
        n = 0;

        if (i == 0) {
            XtSetArg (args[n], XmNtabList, tablist); n++;
        }


        XtSetArg (args[n], XmNfontName, HELVETICA); n++;
        XtSetArg (args[n], XmNfontType, XmFONT_IS_FONT);         n++;
        renditions[i] = XmRenditionCreate (toplevel,
                                           "",
                                           args, n);
    }

    /* Create the Render Table */
    rendertable = XmRenderTableAddRenditions ( NULL,
                                               renditions,
                                               XtNumber (renditions),
                                               XmMERGE_NEW);

    /* Create the multi-column data for the list */

    xmstring_table = CreateListData (&xmstring_count);

    /* Create the List, using the render table */
    n = 0;
    XtSetArg (args[n], XmNrenderTable, rendertable);             n++;
    XtSetArg (args[n], XmNitems, xmstring_table);                n++;
    XtSetArg (args[n], XmNitemCount, xmstring_count);            n++;
    XtSetArg (args[n], XmNwidth, 500);                           n++;
    XtSetArg (args[n], XmNvisibleItemCount, xmstring_count + 1); n++;
    list = XmCreateScrolledList (rowcol, "list", args, n);
    XtManageChild (list);

    /* Free the memory now the widget has the data */
    /* First, the compound strings */
    for (i = 0; i < xmstring_count; i++)
        XmStringFree (xmstring_table[i]);
    XtFree ((char *) xmstring_table);

    /* Secondly, the XmTab objects */
    for (i = 0; i < XtNumber (tabs); i++)
        XmTabFree (tabs[i]);

    /* Thirdly, the XmTabList object */
        XmTabListFree (tablist);

    /* Fourthly, the XmRendition objects */
    for (i = 0; i < XtNumber (renditions); i++)
        XmRenditionFree (renditions[i]);

    /* Lastly, the XmRenderTable object */
    XmRenderTableFree (rendertable);

    XtManageChild (rowcol);
    XtRealizeWidget (toplevel);
    XtAppMainLoop (app);
}
