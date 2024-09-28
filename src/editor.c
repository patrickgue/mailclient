#include <Xm/DialogS.h>
#include <Xm/Form.h>
#include <Xm/TextF.h>
#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/PushB.h>
#include <Xm/PanedW.h>

#define OFFSET_LEFT 60

Widget to, cc, bcc, subject, editor;

void clb_send(Widget w, XtPointer client_data, XtPointer call_data)
{
    char *txt_subject, *txt_to, *txt_cc, *txt_bcc, *txt_content;
    XtVaGetValues(to,      XmNvalue, &txt_to, NULL);
    XtVaGetValues(cc,      XmNvalue, &txt_cc, NULL);
    XtVaGetValues(bcc,     XmNvalue, &txt_bcc, NULL);
    XtVaGetValues(subject, XmNvalue, &txt_subject, NULL);
    XtVaGetValues(editor,  XmNvalue, &txt_content, NULL);
    printf("To:\t\t\"%s\"\nCC:\t\t\"%s\"\nBCC:\t\t\"%s\"\nSubject:\t\"%s\"\nContent:\t\"%s\"\n", txt_to, txt_cc, txt_bcc, txt_subject, txt_content);
}

void clb_editor_dialog_dismiss(Widget w, XtPointer client_data, XtPointer call_data)
{
    Widget dialog = (Widget) client_data;
    XtPopdown(dialog);
}


void new_email_window(Widget toplevel)
{
    Widget dialog, pane, form, button_send, button_discard;
    Arg    args[11];
    int    n, i;


    char *labels[10] = {"To:", "CC:", "BCC:", "Subject:", NULL};

    dialog = XtVaCreatePopupShell ("New Email",
                                   xmDialogShellWidgetClass, toplevel,
                                   XmNdeleteResponse, XmDESTROY,
                                   XmNwidth, 400,
                                   XmNheight, 600,
                                   NULL);

    pane = XtVaCreateWidget ("pane", xmPanedWindowWidgetClass, dialog,
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

    for (i = 0; labels[i] != NULL; i++)
    {
        XtVaCreateManagedWidget (labels[i],
                                 xmLabelWidgetClass, form,
                                 XmNx, 4,
                                 XmNy, 12 + (i * 32),
                                 NULL);
    }

    to = XtVaCreateManagedWidget ("text_to",
                                  xmTextWidgetClass, form,
                                  XmNtopOffset, 4,
                                  XmNtopAttachment, XmATTACH_FORM,
                                  XmNrightOffset, 4,
                                  XmNrightAttachment, XmATTACH_FORM,
                                  XmNleftOffset, OFFSET_LEFT,
                                  XmNleftAttachment, XmATTACH_FORM,
                                  NULL);

    cc = XtVaCreateManagedWidget ("text_cc",
                                  xmTextWidgetClass, form,
                                  XmNtopOffset, 36,
                                  XmNtopAttachment, XmATTACH_FORM,
                                  XmNrightOffset, 4,
                                  XmNrightAttachment, XmATTACH_FORM,
                                  XmNleftOffset, OFFSET_LEFT,
                                  XmNleftAttachment, XmATTACH_FORM,
                                  NULL);

    bcc = XtVaCreateManagedWidget ("text_bcc",
                                   xmTextWidgetClass, form,
                                   XmNtopOffset, 70,
                                   XmNtopAttachment, XmATTACH_FORM,
                                   XmNrightOffset, 4,
                                   XmNrightAttachment, XmATTACH_FORM,
                                   XmNleftOffset, OFFSET_LEFT,
                                   XmNleftAttachment, XmATTACH_FORM,
                                   NULL);


    subject = XtVaCreateManagedWidget ("text_subject",
                                       xmTextWidgetClass, form,
                                       XmNtopOffset, 102,
                                       XmNtopAttachment, XmATTACH_FORM,
                                       XmNrightOffset, 4,
                                       XmNrightAttachment, XmATTACH_FORM,
                                       XmNleftOffset, OFFSET_LEFT,
                                       XmNleftAttachment, XmATTACH_FORM,
                                       NULL);


    n = 0;
    XtSetArg (args[n], XmNrows,             15); n++;
    XtSetArg (args[n], XmNcolumns,          80); n++;
    XtSetArg (args[n], XmNeditMode,         XmMULTI_LINE_EDIT); n++;

    XtSetArg (args[n], XmNbottomOffset, 32);  ++n;
    XtSetArg (args[n], XmNbottomAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNrightOffset, 4);  ++n;
    XtSetArg (args[n], XmNrightAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNleftOffset, 4);  ++n;
    XtSetArg (args[n], XmNleftAttachment, XmATTACH_FORM);  ++n;
    XtSetArg (args[n], XmNtopOffset, 134);  ++n;
    XtSetArg (args[n], XmNtopAttachment, XmATTACH_FORM);  ++n;

    editor = XmCreateScrolledText(form, "scrolled", args, n);
    XtManageChild(editor);

    button_send = XtVaCreateManagedWidget ("btn_editor_send", xmPushButtonWidgetClass,
                                           form,
                                           XmNbottomAttachment, XmATTACH_FORM,
                                           XmNbottomOffset, 4,
                                           XmNrightAttachment, XmATTACH_FORM,
                                           XmNrightOffset, 4,
                                           XmNwidth, 60,
                                           XmNlabelString, XmStringCreateSimple("Send"),
                                          NULL);

    XtAddCallback(button_send, XmNactivateCallback, clb_send, NULL);

    button_discard = XtVaCreateManagedWidget ("btn_editor_discard", xmPushButtonWidgetClass,
                                              form,
                                              XmNbottomAttachment, XmATTACH_FORM,
                                              XmNbottomOffset, 4,
                                              XmNleftAttachment, XmATTACH_FORM,
                                              XmNleftOffset, 4,
                                              XmNwidth, 60,
                                              XmNlabelString, XmStringCreateSimple("Discard"),
                                              NULL);
    XtAddCallback(button_discard, XmNactivateCallback, clb_editor_dialog_dismiss, dialog);

    XtManageChild(form);
    XtManageChild(pane);
    XtManageChild(dialog);

}
