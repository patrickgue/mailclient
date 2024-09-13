#include <Xm/DialogS.h>
#include <Xm/Form.h>
#include <Xm/List.h>
#include <Xm/PanedW.h>


#include "imap.h"

#include "inbox_folder_select.h"

void view_inbox_folder_select(Widget toplevel, struct imap_inbox_folder_item *items, size_t items_size)
{
    Widget        select_dialog, pane, form, list;
    XmStringTable str_list;
    int           i;
    Arg           args[13];

    select_dialog = XtVaCreatePopupShell("Select Inbox Folder",
                                         xmDialogShellWidgetClass, toplevel,
                                         XmNdeleteResponse, XmDESTROY,
                                         XmNwidth, 350,
                                         XmNheight, 400,
                                         NULL);

    pane = XtVaCreateWidget ("pane", xmPanedWindowWidgetClass, select_dialog,
                             XmNsashWidth,  1, /* PanedWindow won't let us set these to 0! */
                             XmNsashHeight, 1, /* Make small so user doesn't try to resize */
                             NULL);
    
    form = XtVaCreateWidget("mainwindow_form",
                            xmFormWidgetClass,
                            pane,
                            XmNmarginHeight, 0,
                            XmNmarginWidth, 0,
                            XmNresizePolicy, XmRESIZE_GROW,
                            NULL);

    str_list = (XmStringTable) XtMalloc (items_size * sizeof (XmString));
    
    /* convert items to XmStringTable format  */
    for (i = 0; i < items_size; i++)
        str_list[i] = XmStringCreateLocalized(items[i].item);

    i = 0;
    XtSetArg (args[i], XmNvisibleItemCount, items_size < 20 ? items_size : 20); i++;
    XtSetArg (args[i], XmNitemCount, items_size); i++;
    XtSetArg (args[i], XmNitems, str_list); i++;
    XtSetArg (args[i], XmNbottomOffset, 1);  ++i;
    XtSetArg (args[i], XmNbottomAttachment, XmATTACH_FORM);  ++i;
    XtSetArg (args[i], XmNrightOffset, 1);  ++i;
    XtSetArg (args[i], XmNrightAttachment, XmATTACH_FORM);  ++i;
    XtSetArg (args[i], XmNleftOffset, 1);  ++i;
    XtSetArg (args[i], XmNleftAttachment, XmATTACH_FORM);  ++i;
    XtSetArg (args[i], XmNtopOffset, 1);  ++i;
    XtSetArg (args[i], XmNtopAttachment, XmATTACH_FORM);  ++i;
    XtSetArg (args[i], XmNscrollBarDisplayPolicy, XmAUTOMATIC);  ++i;
    XtSetArg (args[i], XmNheight, 200); ++i;
    list = XmCreateScrolledList (form, "inbox_folder_list", args, i);
    for (i = 0; i < items_size; i++)
        XmStringFree (str_list[i]);
    XtFree ((char *) str_list);

    XtManageChild(list);
    XtManageChild(form);
    XtManageChild(pane);
    XtManageChild(select_dialog);
}
