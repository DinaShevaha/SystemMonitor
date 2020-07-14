#ifndef HEADER_H
#define HEADER_H

#include <sys/sysinfo.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>

/**
 * Structure which stores data for transmission via a pointer
 */
struct s_system
{
    char host_name[256];     
    char *user_name;       
    char *uptime;           
    char *model_name;       
    char *cpu_MHz;         
    char *mem_avail;         
    char *mem_active;       
    int memAvail;            /* how much memory is available now */
    int memActive;           /* how much memory is active now    */
};

/** Object implemented with :c:struct:`s_system` */
typedef struct s_system t_system;

/**
 * Structure which stores data for transmission via a pointer
 */
struct s_data
{
    GtkWidget *hbox;         
    GtkWidget *window;       
    gboolean  firstLoop;     
};

/** Object implemented with :c:struct:`s_data` */
typedef struct s_data t_data;

void readHostname(char* file_name, t_system *system_info);
void readCpuInfo(char* file_name, t_system *system_info);
void readMemInfo(char* file_name, t_system *system_info);
void readFiles(t_system *system_info);

void getUserInfo(t_system *system_info);
void getUptime(t_system *system_info);

void error(char* str_error);
char *substr(char const *s, unsigned int start, size_t len);
char *fullMem(int mem);
void checkHostname(char *str);
void printSystemInfo(t_system *system_info);

void interface(int argc, char* argv[]);

#endif
