#include "header.h"

void my_close_app(GtkWidget *window, gpointer data)
{
    gtk_widget_destroy(GTK_WIDGET(window));
    free(data);
    gtk_main_quit();
}

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

    gtk_box_pack_start(GTK_BOX(vbox_lable), label1, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label2, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label3, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label4, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label5, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label6, TRUE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox_lable), label7, TRUE, FALSE, 5);

    gtk_box_pack_start(GTK_BOX(hbox), vbox_lable, TRUE, FALSE, 5);
}

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

static gboolean fill_window(gpointer user_data)
{
    t_data *value = user_data;
    
    if (!value->firstLoop)
        gtk_widget_destroy(GTK_WIDGET(value->hbox));

    value->hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    label(value->hbox);
    data(value->hbox);

    gtk_container_add(GTK_CONTAINER(value->window), value->hbox);

    gtk_widget_show_all(value->window);
    value->firstLoop = FALSE;
    return TRUE;
}

void interface(int argc, char* argv[])
{
    t_data *data = (t_data *)malloc(sizeof(t_data));

    gtk_init(&argc, &argv);
    data->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    data->firstLoop = TRUE;

    gtk_window_set_title(GTK_WINDOW(data->window), "System monitor");
    gtk_window_set_position(GTK_WINDOW(data->window), GTK_WIN_POS_NONE);
    gtk_window_set_default_size(GTK_WINDOW(data->window), 1000, 500);

    g_signal_connect(G_OBJECT(data->window), "destroy", G_CALLBACK(my_close_app), data);
    g_timeout_add (1000, fill_window, data);

    gtk_main();
}
