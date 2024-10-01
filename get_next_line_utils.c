#include "get_next_line.h"

t_list	*find_last_node(t_list *list)
{
	if (NULL == list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}
void	polish_list(t_list **list)
{
	t_list	*last_node, *clean_node;
	char	*buf;
	int		i = 0, k = 0;

	if (!*list || !(last_node = find_last_node(*list)))
		return;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return;
	while (last_node->buf[i] && last_node->buf[i] != '\n')
		i++;
	while (last_node->buf[i] && last_node->buf[++i])
		buf[k++] = last_node->buf[i];
	buf[k] = '\0';
	clean_node->buf = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node);
}


void	dealloc(t_list **list, t_list *clean_node)
{
	t_list	*tmp;

	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->buf);
		free(*list);
		*list = tmp;
	}
	if (clean_node->buf[0])
		*list = clean_node;
	else
	{
		free(clean_node->buf);
		free(clean_node);
	}
}


// int	len_str_list(t_list *list)
// {
// 	int len;
// 	int i;

// 	len = 0;
// 	while (list)
// 	{
// 		if (list->buf)
// 		{
// 			i = 0;
// 			while (list->buf[i])
// 			{
// 				if (list->buf[i] == '\n')
// 				{
// 					len += i + 1;
// 					return (len);
// 				}
// 				i++;
// 			}
// 			len += i;
// 		}
// 		list = list->next;
// 	}
// 	return (len);
// }
int	len_str_list(t_list *list)
{
	int len = 0, i;

	while (list)
	{
		i = 0;
		while (list->buf[i])
		{
			if (list->buf[i] == '\n')
				return (len + i + 1);
			i++;
		}
		len += i;
		list = list->next;
	}
	return (len);
}