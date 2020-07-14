#include "header.h"

/** 
 * Reads from the file we transferred, data about hostname 
 * @file_name: the name of the file we pass to the function
 * @system_info: pointer to the structure :c:type:`t_system`
 */
void readHostname(char* file_name, t_system *system_info)
{
    FILE *openFile;
    openFile = fopen(file_name, "r");
    if (openFile == NULL)
        error(strcat("Not found or can`t opened file ", file_name));
    if (fgets(system_info->host_name, 255, openFile) == NULL)
        error("Can`t read hostname");
    checkHostname(system_info->host_name); /* takes the last "\n" and replaces it with "\0" */
    fclose(openFile);
}

/** 
 * Reads from the file we transferred, information about CPU
 * @file_name: the name of the file we pass to the function
 * @system_info: pointer to the structure :c:type:`t_system`
 */
void readCpuInfo(char* file_name, t_system *system_info)
{
    FILE *openFile;
    char buf[255];
    bool find_model = false;
    bool find_cpu = false;

    openFile = fopen(file_name, "r");
    if (openFile == NULL)
        error(strcat("Not found or can`t opened file ", file_name));
    
    while (fgets(buf, 255, openFile) != NULL) {
	/* strstr - returns a pointer to the first occurrence of "model name" in buf, 
	 * or a null pointer if "model name" is not part of buf */
        if (strstr(buf, "model name") && find_model == false) { 
            system_info->model_name = substr(buf, 13, 255); /* substr() returns the substring of given string between 2 given indices*/
            find_model = true;
        }
        if (strstr(buf, "cpu MHz") && find_cpu == false) {
            system_info->cpu_MHz = substr(buf, 11, 255); 
            find_cpu = true;
        }
        if (find_model == true && find_cpu == true)
            break ;
    }
    fclose(openFile);
}

/** 
 * Reads from the file we transferred, information about RAM
 * @file_name: the name of the file we pass to the function
 * @system_info: pointer to the structure :c:type:`t_system`
 */
void readMemInfo(char* file_name, t_system *system_info)
{
    FILE *openFile;
    char buf[255];
    bool find_memAvail = false;
    bool find_memActive = false;

    openFile = fopen(file_name, "r");
    if (openFile == NULL)
        error(strcat("Not found or can`t opened file ", file_name));
    
    while (fgets(buf, 255, openFile) != NULL) {
        if (strstr(buf, "MemAvailable") && find_memAvail == false) {
            system_info->memAvail = atoi(substr(buf, 17, 255));
            system_info->mem_avail = fullMem(atoi(substr(buf, 17, 255)));
            find_memAvail = true;
        }
        if (strstr(buf, "Active") && find_memActive == false) {
            system_info->memActive = atoi(substr(buf, 17, 255));
            system_info->mem_active = fullMem(atoi(substr(buf, 17, 255))); 
            find_memActive = true;
        }
        if (find_memAvail == true && find_memActive == true)
            break ;
    }
    fclose(openFile);
}


/** 
 * Reads files
 * @system_info: pointer to the structure :c:type:`t_system`
 */
void readFiles(t_system *system_info)
{
    readHostname("/proc/sys/kernel/hostname", system_info);
    getUserInfo(system_info);
    readCpuInfo("/proc/cpuinfo", system_info);
    getUptime(system_info);
    readMemInfo("/proc/meminfo", system_info);
}
