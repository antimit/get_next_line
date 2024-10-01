#include "get_next_line.h"


// char * parse_list(t_list * list, char * result)
// {
//     int		i, j = 0;

//     while (list)
// 	{
// 		i = 0;
// 		while (list->buf[i])
// 		{
// 			result[j] = list->buf[i];
// 			if (list->buf[i] == '\n')
// 			{
// 				result[++j] = '\0';
// 				return (result);
// 			}
// 			i++;
// 			j++;
// 		}
// 		list = list->next;
// 	}
// 	result[j] = '\0';
// 	return (result);

// }
char	*get_new_line(t_list *list)
{
	char	*result;
	int		i, j = 0;

	if (list == NULL)
		return (NULL);

	result = (char *)malloc(len_str_list(list) + 1);
	if (!result)
		return (NULL);

	while (list)
	{
		i = 0;
		while (list->buf[i])
		{
			result[j] = list->buf[i];
			if (list->buf[i] == '\n')
			{
				result[++j] = '\0';
				return (result);
			}
			i++;
			j++;
		}
		list = list->next;
	}
	result[j] = '\0';
	return (result);
}



void	add_buf(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return;

	new_node->buf = buf;
	new_node->next = NULL;

	if (*list == NULL)
		*list = new_node;
	else
	{
		temp = *list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	found_newline(t_list *list)
{
	int	i;

	while (list)
	{
		i = 0;
		while (list->buf[i] && i < BUFFER_SIZE)
		{
			if (list->buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

void	clear_list(t_list **list)
{
	t_list *temp;

	while (*list)
	{
		temp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = temp;
	}
}

void	create_list(t_list **list, int fd)
{
	char	*buf;
	int		char_read;

	while (!found_newline(*list))
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return;
		
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read < 0)
		{
			// Free the buffer in case of read error
			free(buf);
			clear_list(list); // Clear the static list on read error
			return;
		}
		if (char_read == 0)
		{
			free(buf);
			return;
		}
		buf[char_read] = '\0';
		add_buf(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	create_list(&list, fd);

	if (!list)
		return (NULL);

	result = get_new_line(list);

	polish_list(&list);

	return (result);
}
