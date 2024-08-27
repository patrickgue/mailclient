/* rendered_list.c: illustrates all the features of
** render tables and renditions by creating a 
** multi-column, multi-font, multi-color List widget.
*/

#include <stdlib.h>

#include <Xm/Xm.h>
#include <Xm/RowColumn.h>
#include <Xm/List.h>
#include <Xm/MainW.h>
#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushBG.h>
#include <Xm/Form.h>
#include <Xm/PushB.h>



#include "config.h"
#include "editor.h"
#include "viewer.h"
#include "imap.h"


Widget                   toplevel;
struct imap_inbox_list **entries;

#define MAX_COLUMNS    2
#define HELVETICA "-*-helvetica-medium-r-normal--12-*-*-*-*-*-iso8859-1"


void clb_exit(Widget w, XtPointer client_data, XtPointer call_data)
{
    printf("Exit normally");
    exit(0);
}

void clb_list_select(Widget w, XtPointer client_data, XtPointer call_data)
{
    XmListCallbackStruct *cbs = (XmListCallbackStruct *) call_data;
    int size, pos = cbs->item_position;
    char **content = malloc(sizeof(char*));
    imap_inbox_fetch_body("INBOX", pos, content, &size);
    view_email_window(toplevel, &((*entries)[pos - 1]), *content);
    free(content);
}

/*
** CreateListData(): routine to convert the
** poem into an array of compound strings
*/
XmStringTable CreateListData (int *count)
{
    XmStringTable            table = (XmStringTable) 0;
    XmString                 row = (XmString) 0;
    XmString                 tmp = (XmString) 0;
    XmString                 tmp2 = (XmString) 0;
    XmString                 tab;
    int                      entries_count, i;
    struct imap_inbox_meta   meta;

    tab = XmStringComponentCreate (XmSTRING_COMPONENT_TAB, 0, NULL);

    imap_init(IMAP, USER, PASSWD);
    imap_inbox_fetch_meta("INBOX", &meta);
    entries = malloc(sizeof(struct imap_inbox_list*));
    entries_count = meta.exists;
    imap_inbox_fetch_list("INBOX", entries_count, entries);

    table = (XmStringTable) XtMalloc(sizeof(XmString) * (entries_count + 1));
    
    for (i = 0; i < entries_count; i++)
    {
        tmp2 = XmStringGenerate((XtPointer) (*entries)[i].subject, NULL, XmCHARSET_TEXT, "");
        row = XmStringGenerate((XtPointer) (*entries)[i].from, NULL, XmCHARSET_TEXT, "");
        tmp = XmStringConcat(row, tab);
        row = XmStringConcat(tmp, tmp2);
        table[i] = row;
        XtFree((XtPointer) tmp);
        XtFree((XtPointer) tmp2);
    }
    
    XmStringFree (tab);

    table[entries_count] = (XmString) 0;

    *count = entries_count;
    /*
      TODO: Prevent memory leaks
      free(*entries);
      free(entries);
    */
    return table;
}

void setup_menu_bar(Widget menu_bar);
void setup_table(Widget main_w, Widget toplevel);
void setup_toolbar(Widget parent);



void clb_new(Widget w, XtPointer client_data, XtPointer call_data)
{
    new_email_window(toplevel);
}

int main(int argc, char **argv)
{
    Widget main_w, menu_bar, main_form;
    XtAppContext app;

    XtSetLanguageProc (NULL, NULL, NULL);

    toplevel = XtVaAppInitialize (&app, "Demos", NULL, 0,
                                  &argc, argv, NULL, NULL);

    main_w = XtVaCreateManagedWidget ("main_w",
                                      xmMainWindowWidgetClass, toplevel,
                                      XmNallowShellResize, True,
                                      XmNtitle, "Main Window",
                                      XmNinitialState, NormalState,
                                      XmNheight, 480,
                                      XmNwidth, 640,
                                      NULL);

    main_form = XtVaCreateWidget("mainwindow_form",
                                 xmFormWidgetClass,
                                 main_w,
                                 XmNmarginHeight, 0,
                                 XmNmarginWidth, 0,
                                 XmNresizePolicy, XmRESIZE_GROW,
                                 NULL);

    

    menu_bar = XmCreateMenuBar (main_w, "MenuBar", NULL, 0);
    setup_menu_bar(menu_bar);
    XtManageChild (menu_bar);

    setup_table(main_form, toplevel);

    setup_toolbar(main_form);
    
    XtManageChild(main_form);
    XtRealizeWidget (toplevel);
    XtAppMainLoop (app);
    return 0;
}

void setup_menu_bar(Widget menu_bar)
{
    XmString    label_str;
    Widget      file_pull_down, exit;

    file_pull_down = XmCreatePulldownMenu (menu_bar, "file_pull_down", NULL, 0);
    label_str = XmStringCreateLocalized ("File");
    XtVaCreateManagedWidget ("File",
                             xmCascadeButtonWidgetClass, menu_bar,
                             XmNlabelString,  label_str,
                             XmNmnemonic,    'F',
                             XmNsubMenuId,    file_pull_down,
                             NULL);
    XmStringFree (label_str);

    XtVaCreateManagedWidget ("Open",xmPushButtonGadgetClass, file_pull_down, NULL);
    XtVaCreateManagedWidget ("Save", xmPushButtonGadgetClass, file_pull_down, NULL);
    XtVaCreateManagedWidget ("separator", xmSeparatorGadgetClass, file_pull_down, NULL);
    exit = XtVaCreateManagedWidget ("Exit", xmPushButtonGadgetClass, file_pull_down, NULL);

    XtAddCallback(exit, XmNactivateCallback, clb_exit, NULL);

}

void setup_table(Widget parent, Widget toplevel)
{
    Arg                args[20];
    XmTab              tabs[MAX_COLUMNS];
    XmTabList          tablist;
    XmRendition        renditions[MAX_COLUMNS];
    XmRenderTable      rendertable;
    Widget             list;
    XmStringTable      xmstring_table;
    int                i, n;
    int                xmstring_count;

    /* Create tab stops for columnar output */
    for (i = 0; i < MAX_COLUMNS; i++) {
        tabs[i] = XmTabCreate ((float) 4, XmINCHES, 
                               ((i == 0) ? XmABSOLUTE : XmRELATIVE),
                               XmALIGNMENT_BEGINNING, 
                               ".");
    }

    /* Create a tablist table which contains the tabs */
    tablist = XmTabListInsertTabs (NULL, tabs, XtNumber (tabs), 0);

    for (i = 0; i < MAX_COLUMNS; i++) {
        n = 0;

        if (i == 0) {
            XtSetArg (args[n], XmNtabList, tablist); n++;
        }

        XtSetArg (args[n], XmNfontName, HELVETICA); n++;
        XtSetArg (args[n], XmNfontType, XmFONT_IS_FONT);         n++;
        renditions[i] = XmRenditionCreate (toplevel, "", args, n);
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
    XtSetArg (args[n], XmNscrollBarDisplayPolicy, XmAUTOMATIC);  ++n;
    XtSetArg (args[n], XmNrenderTable, rendertable);             n++;
    XtSetArg (args[n], XmNitems, xmstring_table);                n++;
    XtSetArg (args[n], XmNitemCount, xmstring_count);            n++;
    XtSetArg (args[n], XmNbottomOffset, 4);  ++n;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNrightOffset, 4);  ++n;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNleftOffset, 4);  ++n;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNtopOffset, 32);  ++n;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNheight, 143);  ++n;
    XtSetArg (args[n], XmNwidth, 393);  ++n;
    XtSetArg (args[n], XmNx, 4);  ++n;

    list = XmCreateScrolledList (parent, "list", args, n);
    XtAddCallback(list, XmNdefaultActionCallback, clb_list_select, NULL);
    XtManageChild (list);

    /* Free the memory now the widget has the data */
    /* First, the compound strings */
    for (i = 0; i < xmstring_count; i++)
    {
        XmStringFree (xmstring_table[i]);
    }
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
}


void setup_toolbar(Widget parent)
{
    Widget button_new, button_refresh;

    button_new = XtVaCreateManagedWidget ("btn_new", xmPushButtonWidgetClass,
                                          parent,
                                          XmNy, 4,
                                          XmNx, 4,
                                          XmNwidth, 60,
                                          XmNlabelString, XmStringCreateSimple("New"),
                                          NULL);

    button_refresh = XtVaCreateManagedWidget ("btn_refresh", xmPushButtonWidgetClass,
                                          parent,
                                          XmNy, 4,
                                          XmNx, 68,
                                          XmNwidth, 60,
                                          XmNlabelString, XmStringCreateSimple("Refresh"),
                                          NULL);

    XtAddCallback(button_new, XmNactivateCallback, clb_new, NULL);
    
    XtManageChild(button_refresh);
    XtManageChild(button_new);
}
