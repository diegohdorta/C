#ifndef _LWIBHELPER_H_
#define _LWIBHELPER_H_

#define SIZE_DIRECTORY      10
#define DELIMITER           ","
#define SIZE_LINE           1024
#define SIZE_NUMBER         2
#define FORBIDDEN_DIRS_NAME "lwib-data/forbidden-dirs.lwib"

struct dict_forbidden_dirs {
	char dir[SIZE_DIRECTORY];
	char lenght[SIZE_NUMBER];	
};
typedef struct dict_forbidden_dirs dict_fdirs_t;

void check_forbidden_directories(char *dir);
void get_file_size(char *file, unsigned int *size);
void load_file_types(char *file, dict_ext_t *dext, unsigned int *ft_size);

#endif /* _LWIBHELPER_H_DEFINED_ */
