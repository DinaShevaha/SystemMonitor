#include "header.h"

void getUserInfo(t_system *system_info)
{
    struct passwd* userinfo; //hello
    uid_t userid = 0;

    userinfo = getpwuid(userid);
    if (userinfo == NULL)
        error("Not found Userinfo!!!!");
    system_info->user_name = userinfo->pw_name;
}

void getUptime(t_system *system_info)
{
    struct sysinfo o;
    char c_hour[20];
    char c_min[20];
    char c_sec[20];
    sysinfo(&o);
    long up = o.uptime;
    int hour = up / 60 / 60;
    int min = (up - hour * 60 * 60) / 60;
    int sec =  ((up - hour * 60 * 60) - min * 60);
    sprintf(c_hour, "%d", hour);
    sprintf(c_min, "%d", min);
    sprintf(c_sec, "%d", sec);
    char* char_hour = strcat(c_hour, " h. ");
    char* char_min = strcat(c_min, " m. ");
    char* char_sec = strcat(c_sec, " s.");
    system_info->uptime = (char *)calloc(255, 255 * sizeof(char));
    strcpy(system_info->uptime, strcat(strcat(char_hour, char_min), char_sec));
}
