#include <stdlib.h>

#include <Xm/DialogS.h>
#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/PanedW.h>

#include "imap.h"

Widget viewer_dialog;

void view_email_window(Widget toplevel, struct imap_inbox_list *item, char *content)
{
    Widget pane, form, text_view, from_cc;
    Arg    args[15];
    int    n;
    char   from_cc_str[STR_BUFF_LEN];

    snprintf(from_cc_str, STR_BUFF_LEN, "From: %s", item->from);

    viewer_dialog = XtVaCreatePopupShell (item->subject,
                                          xmDialogShellWidgetClass, toplevel,
                                          XmNdeleteResponse, XmDESTROY,
                                          XmNwidth, 400,
                                          XmNheight, 600,
                                          NULL);

    pane = XtVaCreateWidget ("pane", xmPanedWindowWidgetClass, viewer_dialog,
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

    from_cc = XtVaCreateManagedWidget ("text_to_cc_bcc",
                                     xmTextWidgetClass, form,
                                     XmNtopOffset, 4,
                                     XmNtopAttachment, XmATTACH_FORM,
                                     XmNrightOffset, 4,
                                     XmNrightAttachment, XmATTACH_FORM,
                                     XmNleftOffset, 4,
                                     XmNleftAttachment, XmATTACH_FORM,
                                     XmNeditable, False,
                                     XmNvalue, from_cc_str,
                                     NULL);


    n = 0;
    XtSetArg (args[n], XmNrows,             15); n++;
    XtSetArg (args[n], XmNcolumns,          80); n++;
    XtSetArg (args[n], XmNeditMode,         XmMULTI_LINE_EDIT); n++;

    XtSetArg (args[n], XmNbottomOffset, 4);  ++n;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNrightOffset, 4);  ++n;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNleftOffset, 4);  ++n;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNtopOffset, 36);  ++n;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNeditable, False); ++n;
    XtSetArg (args[n], XmNwrap, True); ++n;
    XtSetArg (args[n], XmNwordWrap, True); ++n;
    XtSetArg (args[n], XmNvalue, content); ++n;


    text_view = XmCreateScrolledText(form, "text_view", args, n);
    XtManageChild(text_view);
    XtManageChild(form);
    XtManageChild(pane);
    XtManageChild(viewer_dialog);
    free(content);
}
