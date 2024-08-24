#include <Xm/Xm.h>
#include <Xm/List.h>


void list_callback(Widget, XtPointer, void*);

String items[] = {"Abc", "Def", "Ghi"};

Display *display;
Colormap cmap;




int main(int argc, char **argv)
{
    Widget         top_wid, list;
    XtAppContext   app;
    int            i, n = XtNumber(items);
    XColor         back, fore, spare;
    XmStringTable  str_list;
    Arg            args[4];

    top_wid = XtVaAppInitialize(&app, "List Top", NULL, 0, &argc, argv, NULL, NULL);

    str_list = (XmStringTable) XtMalloc(n * sizeof(XmString *));
    
    for (i = 0; i < n; i++)
    {
        str_list[i] = XmStringCreateSimple(items[i]);
    }

    list = XtVaCreateManagedWidget("List",
                                   xmListWidgetClass, top_wid,
                                   XmNvisibleItemCount, n,
                                   XmNitemCount, n,
                                   XmNwidth, 300,
                                   XmNheight, 300,
                                   NULL);

    for (i = 0; i < n; i++)
    {
        XmStringFree(str_list[i]);
    }
    //XtFree(str_list);

    display = XtDisplay(list);

    n = 0;
    XtSetArg(args[n],XmNbackground, back.pixel);      
    ++n;
    XtSetArg(args[n],XmNforeground, fore.pixel);      
    ++n;
    XtSetValues(list, args, n);
    
    XtAddCallback(list, XmNdefaultActionCallback, list_callback, 
                  NULL);

    XtRealizeWidget(top_wid);
    XtAppMainLoop(app);
    
    return 0;
}


void list_callback(Widget w, XtPointer data, 
         void *cbs)

{   int n =0;
    Arg args[1];
    String selection;
    XColor xcolour, spare; /* xlib color struct */
    XmListCallbackStruct *list_cbs = (XmListCallbackStruct*)cbs;
        
    /* list->cbs holds XmString of selected list item */
    /* map this to "ordinary" string */
   
    XmStringGetLtoR(list_cbs->item, XmSTRING_DEFAULT_CHARSET, 
                    &selection);
       
    if (XAllocNamedColor(display, cmap, selection, 
                         &xcolour, &spare) == 0)
       return;
           
    XtSetArg(args[n],XmNbackground, xcolour.pixel);      
    ++n;
    /* w id of list widget passed in */
    XtSetValues(w, args, n); 
  
}
