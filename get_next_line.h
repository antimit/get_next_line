#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*buf;
	struct s_list	*next;
}					t_list;
char				*get_new_line(t_list *list);
void				add_buf(t_list **list, char *buf);
void				dealloc(t_list **list, t_list *clean_node);
void				polish_list(t_list **list);
char				*get_next_line(int fd);
t_list				*find_last_node(t_list *list);
int					len_str_list(t_list *list);
void				create_list(t_list **list, int fd);
int					found_newline(t_list *list);

#endif