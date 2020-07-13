#include "header.h"
#include <strings.h>

void error(char* str_error)
{
    printf("%s\n", str_error);
    exit(EXIT_FAILURE);
}  

char *substr(char const *s, unsigned int start, size_t len)
{
    size_t i;
    size_t j;
    char *str;

    str = (char*)malloc(sizeof(*s) * (len + 1));
    if (!str)
	return (NULL);
    i = 0;
    j = 0;
    while (s[i]) {
	if (i >= start && j < len) {
	    str[j] = s[i];
	    j++;
	}
	i++;
    }
    str[j] = 0;
    return (str);
}

char *fullMem(int mem)
{
    char c_gb[20];
    char c_mb[20];
    char c_kb[20];
    int gb = (mem / 1024) / 1024;
    int mb = (mem - gb * 1024 * 1024) / 1024;
    int kb = (mem - (gb * 1024 * 1024 + mb * 1024));
    sprintf(c_gb, "%d", gb);
    sprintf(c_mb, "%d", mb);
    sprintf(c_kb, "%d", kb);
    char *str = (char*)calloc(255, 255 * sizeof(char));
    if (!str)
        error("No memory");
    if (gb > 0)
        strcat(str, strcat(c_gb, " Gb "));
    if (mb > 0)
        strcat(str, strcat(c_mb, " Mb "));
    if (kb > 0)
        strcat(str, strcat(c_kb, " Kb "));   
    return (str);
}

void checkHostname(char *str)
{
    int i = 0;
    while (str[i]) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break ;
        }
        i++;
    }
}

void printSystemInfo(t_system *system_info)
{
    printf("hostname: %s", system_info->host_name);
    printf("username: %s\n", system_info->user_name);
    printf("Uptime: %s\n", system_info->uptime);
    printf("CPU model: %s", system_info->model_name);
    printf("CPU MHz: %s", system_info->cpu_MHz);
    printf("Mem Available: %s\n", system_info->mem_avail);
    printf("Mem Active: %s\n", system_info->mem_active);
}
