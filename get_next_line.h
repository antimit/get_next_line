#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include "ft_printf/ft_printf.h"

char	*append_string(char *left_str, char *buff);
char * after_new_line(char * str);
char	*get_next_line(int fd);
int	str_len(char *str);
int newline(char *str);
char	*get_new_line(int fd,char * buffer);
char	*before_new_line(char *left_str);

#endif