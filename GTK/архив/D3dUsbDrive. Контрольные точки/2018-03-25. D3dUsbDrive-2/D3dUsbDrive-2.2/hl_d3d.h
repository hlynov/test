#ifndef HL_D3D_H
#define HL_D3D_H

#include <gtk/gtk.h>


/* Widgets */
GtkBuilder      *builder;
GtkWidget       *window;
GtkWidget       *buttonf2;
GtkWidget       *lblConnectionStatus;
GtkWidget       *btnExit;
GtkWidget       *btnExitLoop;

//****************************************************
//
//****************************************************


typedef struct
{
    int x;
    int y;
} TestStruct;


// custom structure that will hold pointers to widgets and / or user variables
typedef struct {
    GtkWidget *w_lbl_time;
    GtkWidget *w_lbl_count;
    int x;
} app_widgets;


typedef struct
{
    int check;
    int i;
} Data;

//******************************************************
//Function prototipe
//******************************************************

static void my_func (GtkWidget* w , Data *data);
static void exitLoop (GtkWidget* w , gpointer ptrExitLoop);



#endif //  HL_D3D_H



