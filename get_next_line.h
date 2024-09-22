#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

void				clear_list(t_list **list);
int					len_str_list(t_list *list);
char				*get_line(t_list *list);
int					found_newline(t_list **list);
void				append(t_list **list, char *buf);
void				create_list(t_list **list, int fd);
char				*get_next_line(int fd);

#endif