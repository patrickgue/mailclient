/*** DTB_USER_CODE_START vvv Add file header below vvv ***/
/*** DTB_USER_CODE_END   ^^^ Add file header above ^^^ ***/

/*
 * File: maillist.c
 * Contains: main() and cross-module connections
 *
 * This file was generated by dtcodegen, from project maillist
 *
 * Any text may be added between the DTB_USER_CODE_START and
 * DTB_USER_CODE_END comments (even non-C code). Descriptive comments
 * are provided only as an aid.
 *
 *  ** EDIT ONLY WITHIN SECTIONS MARKED WITH DTB_USER_CODE COMMENTS.  **
 *  ** ALL OTHER MODIFICATIONS WILL BE OVERWRITTEN. DO NOT MODIFY OR  **
 *  ** DELETE THE GENERATED COMMENTS!                                 **
 */

#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/Protocols.h>
#include <Dt/Help.h>
#include <Dt/HelpQuickD.h>
#include <Dt/HelpDialog.h>
#include "module_ui.h"
#include "maillist.h"
#include "dtb_utils.h"


/**************************************************************************
 *** DTB_USER_CODE_START
 ***
 *** All necessary header files have been included.
 ***
 *** Add include files, types, macros, externs, and user functions here.
 ***/

/*** DTB_USER_CODE_END
 ***
 *** End of user code section
 ***
 **************************************************************************/



/*
 * command line options...
 */
static XrmOptionDescRec optionDescList[] = {
    {"-session", "*session", XrmoptionSepArg, (XPointer)NULL}
    
    /*** DTB_USER_CODE_START vvv Add structure fields below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add structure fields above ^^^ ***/
};

/*
 * Application Resources
 */
static XtResource resources[] = {
    {"session", "Session", XtRString, sizeof(String),
        XtOffsetOf(DtbAppResourceRec, session_file), XtRImmediate, (XtPointer)NULL}
    
    /*** DTB_USER_CODE_START vvv Add structure fields below vvv ***/
    /*** DTB_USER_CODE_END   ^^^ Add structure fields above ^^^ ***/
};

DtbAppResourceRec	dtb_app_resource_rec;


/*
 * main for application maillist
 */
int
main(int argc, char **argv)
{
    Widget		toplevel = (Widget)NULL;
    Display		*display = (Display*)NULL;
    XtAppContext	app = (XtAppContext)NULL;
    String		*fallback_resources = (String*)NULL;
    ArgList		init_args = (ArgList)NULL;
    Cardinal		num_init_args = (Cardinal)0;
    ArgList		get_resources_args = (ArgList)NULL;
    Cardinal		num_get_resources_args = (Cardinal)0;
    Atom		save_yourself_atom = (Atom)NULL;
    
    
    /**************************************************************************
     *** DTB_USER_CODE_START
     ***
     ***  No initialization has been done.
     ***
     *** Add local variables and code.
     ***/
    
    /*** DTB_USER_CODE_END
     ***
     *** End of user code section
     ***
     **************************************************************************/
    

    toplevel = XtAppInitialize(&app, "Maillist",
        optionDescList, XtNumber(optionDescList),
        &argc, argv, fallback_resources,
        init_args, num_init_args);

    /*
     * Get display and verify initialization was successful.
     */
    if (toplevel != NULL)
    {
        display = XtDisplayOfObject(toplevel);
    }
    if (display == NULL)
    {
        fprintf(stderr, "Could not open display.");
        exit(1);
    }
    
    /*
     * Save the toplevel widget so it can be fetched later as needed.
     */
    dtb_save_toplevel_widget(toplevel);
    
    /*
     * Save the command used to invoke the application.
     */
    dtb_save_command(argv[0]);
    
    XtGetApplicationResources(toplevel, (XtPointer)&dtb_app_resource_rec,
        resources, XtNumber(resources),
        get_resources_args, num_get_resources_args);
    
    
    /**************************************************************************
     *** DTB_USER_CODE_START
     ***
     ***      A connection to the X server has been established, and all
     *** initialization has been done.
     ***
     ***  Add extra initialization code after this comment.
     ***/
    
    /*** DTB_USER_CODE_END
     ***
     *** End of user code section
     ***
     **************************************************************************/
    

    
    /*
     * Initialize all global variables.
     */
    dtbModuleMainwindowInfo_clear(&dtb_module_mainwindow);
    
    /*
     * Set up the application's root window.
     */
    dtb_module_mainwindow.mainwindow = toplevel;

    XtVaSetValues(dtb_module_mainwindow.mainwindow,
        XmNallowShellResize, True,
        XmNtitle, "Main Window",
        XmNinitialState, NormalState,
        XmNbackground, dtb_cvt_string_to_pixel(dtb_module_mainwindow.mainwindow, "white"),
        NULL);
    
    dtb_module_mainwindow_initialize(&(dtb_module_mainwindow), dtb_get_toplevel_widget());
    
    /*
     * Map any initially-visible windows
     */
    
    save_yourself_atom = XmInternAtom(XtDisplay(toplevel),
    	"WM_SAVE_YOURSELF", False);
    
    XmAddWMProtocolCallback(toplevel, save_yourself_atom,
    	dtb_session_save, (XtPointer)NULL);
    
    
    /**************************************************************************
     *** DTB_USER_CODE_START
     ***
     ***      All initially-mapped widgets have been created, but not
     *** realized. Set resources on widgets, or perform other operations
     *** that must be completed before the toplevel widget is
     *** realized.
     ***/
    
    /*** DTB_USER_CODE_END
     ***
     *** End of user code section
     ***
     **************************************************************************/
    

    XtRealizeWidget(toplevel);

    
    /**************************************************************************
     *** DTB_USER_CODE_START
     ***
     ***      The initially-mapped widgets have all been realized, and
     *** the Xt main loop is about to be entered.
     ***/
    
    /*** DTB_USER_CODE_END
     ***
     *** End of user code section
     ***
     **************************************************************************/
    

    
    /*
     * Enter event loop
     */
    XtAppMainLoop(app);
    return 0;
}


/**************************************************************************
 *** DTB_USER_CODE_START
 ***
 *** All automatically-generated data and functions have been defined.
 ***
 *** Add new functions here, or at the top of the file.
 ***/

/*** DTB_USER_CODE_END
 ***
 *** End of user code section
 ***
 **************************************************************************/


