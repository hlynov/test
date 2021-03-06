#include <gtk/gtk.h>
#include "hl_d3d.h"
#include "hl_usb.h"

//***********************************************************************
//MAIN
//***********************************************************************
//
int main(int argc, char *argv[])

{
    /* Declare variables */
    int var[3]={100, 200, 300};
    char textForLabel[]="My var works";

    int ExitLoop = 0;
    int *ptrExitLoop;
    ptrExitLoop = & ExitLoop;

    int rx[8];

    /* END of Declare variables */



    // instantiate structure, allocating memory for it
    app_widgets        *widgets = g_slice_new(app_widgets);
    TestStruct         *status = g_slice_new(TestStruct);
    Data data;

    //data.check[10] = "fuck off\n";


    /* запускаем GTK+ */
    gtk_init(&argc, &argv);


    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "window_main(1).glade", NULL);




    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    // get pointers to label widgets
    widgets->w_lbl_time  = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time"));
    widgets->w_lbl_count = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_count"));
    buttonf2 = GTK_WIDGET(gtk_builder_get_object(builder, "btn2"));
    lblConnectionStatus = GTK_WIDGET(gtk_builder_get_object(builder, "lblConnectionStatus"));
    btnExit = GTK_WIDGET(gtk_builder_get_object(builder, "btnExit"));
    btnExitLoop = GTK_WIDGET(gtk_builder_get_object(builder, "btnExitLoop"));


    // widgets pointer will be passed to all widget handler functions as the user_data parameter


    gtk_builder_connect_signals(builder, widgets);    // note: second parameter is not NULL
    //gtk_builder_connect_signals(builder, status);    // note: second parameter is not NULL
    g_signal_connect (buttonf2, "clicked", G_CALLBACK (my_func), &data);
    g_signal_connect (btnExit, "clicked", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (btnExitLoop, "clicked", G_CALLBACK (exitLoop), ptrExitLoop);


    g_object_unref(builder);


    // USB INIT
    libusb_init(NULL);   // инициализация
    libusb_set_debug(NULL, USB_DEBUG_LEVEL);  // уровень вывода отладочных сообщений
    libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, VID, PID);

    concheck(handle, lblConnectionStatus);

    g_print ("%p\n" , ptrExitLoop);

    testRead (handle);

    gtk_widget_show(window);
    // while (gtk_events_pending()) gtk_main_iteration_do(FALSE);
    //gtk_main();
    // free up memory used by widget structure, probably not necessary as OS will
    // reclaim memory from application after it exits

    while (ExitLoop==0)
    {
        //        myTestFunc();

        gtk_main_iteration();

        interrupt_transfer_loop(handle, rx);

    }

    g_slice_free(app_widgets, widgets);
    //libusb_attach_kernel_driver(handle, DEV_INTF);
    //libusb_close(handle);
    //libusb_exit(NULL);


    return 0;
}


//****************************************************************************************
//Callback Functions
//****************************************************************************************



// callback function for button clicked signal
void on_btn_update_clicked(GtkButton *button, app_widgets *app_wdgts)
{
    GDateTime   *time;            // for storing current time and date
    gchar       *time_str;        // current time and date as a string
    static gint count = 0;        // stores number of times button was clicked
    gchar       *count_str;       // button clicked count as a string

    time     = g_date_time_new_now_local();             // get the current time
    time_str = g_date_time_format(time, "%H:%M:%S");    // convert current time to string
    count++;                                            // number of times button clicked
    count_str = g_strdup_printf("%d", count);           // convert count to string

    // update time and count in label widgets
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_time), time_str);
    gtk_label_set_text(GTK_LABEL(app_wdgts->w_lbl_count), count_str);

    // free memory used by glib functions
    g_free(time_str);
    g_date_time_unref(time);
    g_free(count_str);
}



//Test Function. For any experiments
static void my_func (GtkWidget* w , Data *data)
{
    int a = data->check;
    g_print ("sssssss");
}


//Function for exit from main Loop. ExitLoop variable make equal 1.
static void exitLoop (GtkWidget* w , gpointer ptrExitLoop)
{
    //    int a = *ptrExitLoop;
    g_print ("%p\n" , ptrExitLoop);
    (*(int*)ptrExitLoop) = 1;
}
//*****************************************************************





// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}
