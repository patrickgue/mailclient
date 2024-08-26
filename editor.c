#include <Xm/DialogS.h>
#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/Text.h>
#include <Xm/Label.h>

#define OFFSET_LEFT 50

void new_email_window(Widget toplevel)
{
    Widget dialog, pane, to, cc, bcc, subject, editor;
    Arg    args[11];
    int    n, i;

    char *labels[10] = {"To:", "CC:", "BCC:", "Subject", NULL};

    dialog = XtVaCreatePopupShell ("New Email",
                                   xmDialogShellWidgetClass, toplevel,
                                   XmNdeleteResponse, XmDESTROY,
                                   XmNwidth, 400,
                                   XmNheight, 600,
                                   NULL);

    pane = XtVaCreateWidget("mainwindow_form",
                            xmFormWidgetClass,
                            dialog,
                            XmNmarginHeight, 0,
                            XmNmarginWidth, 0,
                            XmNresizePolicy, XmRESIZE_GROW,
                            NULL);

    for (i = 0; labels[i] != NULL; i++)
    {
        XtVaCreateManagedWidget (labels[i],
                                 xmLabelWidgetClass, pane, XmNx, 4, XmNy, 8 + (i * 28), NULL);
    }
    
    to = XtVaCreateManagedWidget ("text_to",
                                  xmTextWidgetClass, pane,
                                  XmNtopOffset, 4,
                                  XmNtopAttachment, XmATTACH_FORM,
                                  XmNrightOffset, 4,
                                  XmNrightAttachment, XmATTACH_FORM,
                                  XmNleftOffset, OFFSET_LEFT,
                                  XmNleftAttachment, XmATTACH_FORM,
                                  NULL);

    cc = XtVaCreateManagedWidget ("text_cc",
                                  xmTextWidgetClass, pane,
                                  XmNtopOffset, 32,
                                  XmNtopAttachment, XmATTACH_FORM,
                                  XmNrightOffset, 4,
                                  XmNrightAttachment, XmATTACH_FORM,
                                  XmNleftOffset, OFFSET_LEFT,
                                  XmNleftAttachment, XmATTACH_FORM,
                                  NULL);

    bcc = XtVaCreateManagedWidget ("text_bcc",
                                   xmTextWidgetClass, pane,
                                   XmNtopOffset, 60,
                                   XmNtopAttachment, XmATTACH_FORM,
                                   XmNrightOffset, 4,
                                   XmNrightAttachment, XmATTACH_FORM,
                                   XmNleftOffset, OFFSET_LEFT,
                                   XmNleftAttachment, XmATTACH_FORM,
                                   NULL);

    subject = XtVaCreateManagedWidget ("text_subject",
                                       xmTextWidgetClass, pane,
                                       XmNtopOffset, 88,
                                       XmNtopAttachment, XmATTACH_FORM,
                                       XmNrightOffset, 4,
                                       XmNrightAttachment, XmATTACH_FORM,
                                       XmNleftOffset, OFFSET_LEFT,
                                       XmNleftAttachment, XmATTACH_FORM,
                                       NULL);

    
    
    n = 0;
    XtSetArg (args[n], XmNrows,             10); n++;
    XtSetArg (args[n], XmNcolumns,          80); n++;
    XtSetArg (args[n], XmNeditMode,         XmMULTI_LINE_EDIT); n++;


    XtSetArg (args[n], XmNbottomOffset, 4);  ++n;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNrightOffset, 4);  ++n;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNleftOffset, 4);  ++n;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNtopOffset, 116);  ++n;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);  ++n;
    

    editor = XmCreateScrolledText(pane, "scrolled", args, n);
    XtManageChild(editor);
    
    XtManageChild(pane);
    XtPopup (dialog, XtGrabNone);
}
