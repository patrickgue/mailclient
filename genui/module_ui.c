/*
 * File: module_ui.c
 * Contains: user module object initialize and create functions
 *
 * This file was generated by dtcodegen, from module module
 *
 *    ** DO NOT MODIFY BY HAND - ALL MODIFICATIONS WILL BE LOST **
 */


#include <stdlib.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <Xm/PanedW.h>
#include <Xm/MainW.h>
#include <Xm/Form.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeB.h>
#include <Xm/ScrollBar.h>
#include <Xm/ScrolledW.h>
#include <Xm/List.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include "dtb_utils.h"
#include "maillist.h"
#include "module_ui.h"


DtbModuleMainwindowInfoRec	dtb_module_mainwindow = 
{
    False	 /* initialized */
};

/*
 * Widget create procedure decls
 */
static int dtb_module_mainwindow_create(
    DtbModuleMainwindowInfo	instance,
    Widget	parent
);
static int dtb_module_menubar_create(
    DtbModuleMainwindowInfo	instance,
    Widget	parent
);
static int dtb_module_controlpane_create(
    DtbModuleMainwindowInfo	instance,
    Widget	parent
);
static int dtb_module_list_create(
    DtbModuleMainwindowInfo	instance,
    Widget	parent
);
static int dtb_module_button_create(
    DtbModuleMainwindowInfo	instance,
    Widget	parent
);

int 
dtbModuleMainwindowInfo_clear(DtbModuleMainwindowInfo instance)
{
    memset((void *)(instance), 0, sizeof(*instance));
    return 0;
}

int 
dtb_module_mainwindow_initialize(
    DtbModuleMainwindowInfo instance,
    Widget parent
)
{
    WidgetList	children = NULL;
    int		numChildren = 0;
    if (instance->initialized)
    {
        return 0;
    }
    instance->initialized = True;

    dtb_module_mainwindow_create(instance,
        parent);
    dtb_module_menubar_create(instance,
        instance->mainwindow_mainwin);
    dtb_module_controlpane_create(instance,
        instance->mainwindow_form);
    dtb_module_list_create(instance,
        instance->controlpane);
    dtb_module_button_create(instance,
        instance->controlpane);
    
    /*
     * Add widget-reference resources.
     */
    
    XtVaSetValues(instance->mainwindow_mainwin,
        XmNmenuBar, instance->menubar,
        XmNworkWindow, instance->mainwindow_form,
        NULL);
    
    XtVaSetValues(instance->menubar,
        XmNmenuHelpWidget, instance->menubar_items.Help_item,
        NULL);
    
    /*
     * Call utility functions to do group layout
     */
    
    XmMainWindowSetAreas(instance->mainwindow_mainwin,
        instance->menubar,
        NULL,
        NULL,
        NULL,
        instance->mainwindow_form);
    
    /*
     * Manage the tree, from the bottom up.
     */
    XtVaGetValues(instance->menubar,
        XmNchildren, &children, XmNnumChildren, &numChildren, NULL);
    XtManageChildren(children, numChildren);
    XtManageChild(instance->list);
    XtVaGetValues(instance->controlpane,
        XmNchildren, &children, XmNnumChildren, &numChildren, NULL);
    XtManageChildren(children, numChildren);
    XtVaGetValues(instance->mainwindow_form,
        XmNchildren, &children, XmNnumChildren, &numChildren, NULL);
    XtManageChildren(children, numChildren);
    XtManageChild(instance->menubar);
    XtManageChild(instance->mainwindow_form);
    XtVaGetValues(instance->mainwindow,
        XmNchildren, &children, XmNnumChildren, &numChildren, NULL);
    XtManageChildren(children, numChildren);
    
    /*
     * Add User and Connection callbacks
     */
    return 0;
}



static int 
dtb_module_mainwindow_create(
    DtbModuleMainwindowInfo instance,
    Widget parent
)
{
    XmString	label_xmstring = NULL;
    Display	*display= (parent == NULL? NULL:XtDisplay(parent));
    
    if (instance->mainwindow == NULL) {
        instance->mainwindow =
            XtVaCreatePopupShell("mainwindow",
                topLevelShellWidgetClass,
                parent,
                XmNallowShellResize, True,
                XmNtitle, "Main Window",
                XmNinitialState, NormalState,
                XmNbackground, dtb_cvt_string_to_pixel(parent, "white"),
                NULL);
    }
    if (instance->mainwindow == NULL)
        return -1;

    if (instance->mainwindow_mainwin == NULL) {
        instance->mainwindow_mainwin =
            XtVaCreateWidget("dtb_module_mainwindow_mainwin",
                xmMainWindowWidgetClass,
                instance->mainwindow,
                XmNbackground, dtb_cvt_string_to_pixel(instance->mainwindow, "white"),
                NULL);
    }
    if (instance->mainwindow_mainwin == NULL)
        return -1;

    if (instance->mainwindow_form == NULL) {
        instance->mainwindow_form =
            XtVaCreateWidget("mainwindow_form",
                xmFormWidgetClass,
                instance->mainwindow_mainwin,
                XmNmarginHeight, 0,
                XmNmarginWidth, 0,
                XmNresizePolicy, XmRESIZE_GROW,
                XmNheight, 175,
                XmNwidth, 401,
                XmNbackground, dtb_cvt_string_to_pixel(instance->mainwindow_mainwin, "white"),
                NULL);
    }
    if (instance->mainwindow_form == NULL)
        return -1;

    return 0;
}



static int 
dtb_module_menubar_create(
    DtbModuleMainwindowInfo instance,
    Widget parent
)
{
    XmString	label_xmstring = NULL;
    Arg	args[7];	/* need 2 args (add 5 to be safe) */
    int	n = 0;
    static String	menubar_names[] =
    {
        "File_item", "Edit_item", "Help_item"
    };
    static String	menubar_strings[] =
    {
        "File", "Edit", "Help"
    };
    int	i = 0;
    Widget	menubar_items[3];
    
    if (instance->menubar == NULL) {
        n = 0;
        XtSetArg(args[n], XmNrowColumnType, XmMENU_BAR);  ++n;
        instance->menubar =
            XmCreateMenuBar(parent,
                "menubar", args, n);
    }
    if (instance->menubar == NULL)
        return -1;

    for (i = 0; i < XtNumber(menubar_strings); i++)
    {
        label_xmstring = XmStringCreateLocalized(menubar_strings[i]);
        menubar_items[i] = XtVaCreateWidget(menubar_names[i],
            xmCascadeButtonWidgetClass,
            instance->menubar,
            XmNlabelString, label_xmstring,
            NULL);
        XmStringFree(label_xmstring);
        label_xmstring = NULL;
    }
    instance->menubar_items.File_item = menubar_items[0];
    instance->menubar_items.Edit_item = menubar_items[1];
    instance->menubar_items.Help_item = menubar_items[2];
    return 0;
}



static int 
dtb_module_controlpane_create(
    DtbModuleMainwindowInfo instance,
    Widget parent
)
{
    
    if (instance->controlpane == NULL) {
        instance->controlpane =
            XtVaCreateWidget("controlpane",
                xmFormWidgetClass,
                parent,
                XmNbottomOffset, 0,
                XmNbottomAttachment, XmATTACH_FORM,
                XmNrightOffset, 0,
                XmNrightAttachment, XmATTACH_FORM,
                XmNleftOffset, 0,
                XmNleftAttachment, XmATTACH_FORM,
                XmNtopOffset, 0,
                XmNtopAttachment, XmATTACH_FORM,
                XmNresizePolicy, XmRESIZE_ANY,
                XmNmarginHeight, 0,
                XmNmarginWidth, 0,
                XmNy, 0,
                XmNx, 0,
                NULL);
    }
    if (instance->controlpane == NULL)
        return -1;

    return 0;
}



static int 
dtb_module_list_create(
    DtbModuleMainwindowInfo instance,
    Widget parent
)
{
    XmString	label_xmstring = NULL;
    Arg	args[21];	/* need 16 args (add 5 to be safe) */
    int	n = 0;
    int	i = 0;
    static String	list_list_names[] =
    {
        "list_itemA_item", "list_itemB_item"
    };
    static String	list_list_strings[] =
    {
        "itemA", "itemB"
    };
    XmString list_list_xmstrings[2];
    
    
    /*
     * Convert char* strings to XmStrings
     */
    for (i = 0; i < 2; ++i)
    {
        list_list_xmstrings[i] = 
            XmStringCreateLocalized(
                list_list_strings[i]);
    }
    if (instance->list == NULL) {
        n = 0;
        XtSetArg(args[n], XmNscrollBarDisplayPolicy, XmAUTOMATIC);  ++n;
        XtSetArg(args[n], XmNlistSizePolicy, XmCONSTANT);  ++n;
        XtSetArg(args[n], XmNselectionPolicy, XmBROWSE_SELECT);  ++n;
        XtSetArg(args[n], XmNbottomOffset, 4);  ++n;
        XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM);  ++n;
        XtSetArg(args[n], XmNrightOffset, 4);  ++n;
        XtSetArg(args[n], XmNrightAttachment, XmATTACH_FORM);  ++n;
        XtSetArg(args[n], XmNleftOffset, 4);  ++n;
        XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM);  ++n;
        XtSetArg(args[n], XmNtopOffset, 28);  ++n;
        XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM);  ++n;
        XtSetArg(args[n], XmNheight, 143);  ++n;
        XtSetArg(args[n], XmNwidth, 393);  ++n;
        XtSetArg(args[n], XmNy, 28);  ++n;
        XtSetArg(args[n], XmNx, 4);  ++n;
        XtSetArg(args[n], XmNitems, (XtArgVal)list_list_xmstrings); n++;
        XtSetArg(args[n], XmNitemCount, (XtArgVal)2); n++;
        instance->list =
            XmCreateScrolledList(parent,
                "list", args, n);
    }
    instance->list_scrolledwin = XtParent(instance->list);
    /*
     * Free XmStrings (widget makes private copy of StringList)
     */
    for (i = 0; i < 2; i++)
        XmStringFree(list_list_xmstrings[i]);

    if (instance->list == NULL)
        return -1;

    return 0;
}



static int 
dtb_module_button_create(
    DtbModuleMainwindowInfo instance,
    Widget parent
)
{
    XmString	label_xmstring = NULL;
    
    label_xmstring = XmStringCreateLocalized("Button");
    if (instance->button == NULL) {
        instance->button =
            XtVaCreateWidget("button",
                xmPushButtonWidgetClass,
                parent,
                XmNbottomAttachment, XmATTACH_NONE,
                XmNrightAttachment, XmATTACH_NONE,
                XmNleftOffset, 4,
                XmNleftAttachment, XmATTACH_FORM,
                XmNtopOffset, 4,
                XmNtopAttachment, XmATTACH_FORM,
                XmNrecomputeSize, True,
                XmNalignment, XmALIGNMENT_CENTER,
                XmNy, 0,
                XmNx, 3,
                XmNlabelString, label_xmstring,
                NULL);
        XmStringFree(label_xmstring);
        label_xmstring = NULL;
    }
    if (instance->button == NULL)
        return -1;

    return 0;
}

