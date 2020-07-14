#include "header.h"

/** 
 * Closing the application
 * @window: poiner to GtkWidget
 * @data: a smart pointer that can be of any type
 */
void my_close_app(GtkWidget *window, gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(window)); /* Destroys a widget */
    free(data);
    gtk_main_quit(); /* Makes the innermost invocation of the main loop return when it regains control */
}

/** 
 * Creating labels in the GTK interface(hostname, username, etc), initializing them to the window
 * @hbox: poiner to GtkWidget
 */
void label(GtkWidget *hbox)
{
    GtkWidget *vbox_lable;
    GtkWidget *label1, *label2, *label3, *label4, *label5, *label6, *label7;
    
    label1 = gtk_label_new("hostname: ");
    label2 = gtk_label_new("username: ");
    label3 = gtk_label_new("Uptime: ");
    label4 = gtk_label_new("CPU model: ");
    label5 = gtk_label_new("CPU MHz: ");
    label6 = gtk_label_new("Mem Available: ");
    label7 = gtk_label_new("Mem Active: ");

    vbox_lable = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);  

    /* gtk_box_pack_start - Adds child to box, packed with reference to the start of box. 
     * The child is packed after any other child packed with reference to the start of box */	 
    gtk_box_pack_start(GTK_BOX(vbox_lable), label1, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label2, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label3, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label4, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label5, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label6, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label7, TRUE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox), vbox_lable, TRUE, FALSE, 5);
}

/**
 * Creating values that match the characteristics of the computer
 * @hbox: poiner to GtkWidget
 */
void data(GtkWidget *hbox)
{
    t_system *system_info = (t_system *)malloc(sizeof(t_system));
    system_info->cpu_MHz = "";
    system_info->model_name = "";
    system_info->user_name = "";
    system_info->mem_avail = "";
    system_info->mem_active = "";
   
    readFiles(system_info);

    GtkWidget *vbox_data;
    GtkWidget *hostname, *username, *uptime, *cpuModel, *cpuMhz, *memAval, *memActive;
    
    hostname = gtk_label_new(system_info->host_name);
    username = gtk_label_new(system_info->user_name);
    uptime = gtk_label_new(system_info->uptime);
    cpuModel = gtk_label_new(system_info->model_name);
    cpuMhz = gtk_label_new(system_info->cpu_MHz);
    memAval = gtk_label_new(system_info->mem_avail);
    memActive = gtk_label_new(system_info->mem_active);

    vbox_data = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    gtk_box_pack_start(GTK_BOX(vbox_data), hostname, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_data), username, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_data), uptime, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_data), cpuModel, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_data), cpuMhz, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_data), memAval, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_data), memActive, TRUE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox), vbox_data, TRUE, FALSE, 5);
    free(system_info->model_name);
    free(system_info->cpu_MHz);
    free(system_info->mem_active);
    free(system_info->mem_avail);
    free(system_info);
}

/**
 * Filling the interface window
 * @user_data: a smart pointer that can be of any type
 *
 * Returns: bool value
 */
static gboolean fill_window(gpointer user_data)
{
    t_data *value = user_data;
    
    if (!value->firstLoop)
        gtk_widget_destroy(GTK_WIDGET(value->hbox));

    value->hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    label(value->hbox);
    data(value->hbox);

    gtk_container_add(GTK_CONTAINER(value->window), value->hbox); /* Adds hbox to  GTK container*/

    gtk_widget_show_all(value->window); /* Recursively shows a widget, and any child widgets */
    value->firstLoop = FALSE;
    return TRUE;
}

/**
 * Builds the program interface
 * @argc: the number of parameters passed to the program
 * @argv: an array of strings
 */
void interface(int argc, char* argv[])
{
    t_data *data = (t_data *)malloc(sizeof(t_data));

    gtk_init(&argc, &argv);
    data->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    data->firstLoop = TRUE;

    gtk_window_set_title(GTK_WINDOW(data->window), "System monitor");
    gtk_window_set_position(GTK_WINDOW(data->window), GTK_WIN_POS_NONE);
    gtk_window_set_default_size(GTK_WINDOW(data->window), 1000, 500);

    g_signal_connect(G_OBJECT(data->window), "destroy", G_CALLBACK(my_close_app), data); /* The function that causes the program to close */
    g_timeout_add (1000, fill_window, data); /* parameters: time between function starts, function to call, data for placement in function */

    gtk_main(); /* Runs the main loop until gtk_main_quit() is called */
}
