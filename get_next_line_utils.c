#include "get_next_line.h"

void	clear_list(t_list **list)
{
	t_list	*temp;
	t_list	*to_be_deleted;

	temp = *list;
	if (!temp)
		return ;
	while (temp)
	{
		to_be_deleted = temp;
		temp = temp->next;
		free(to_be_deleted->str_buf);
		free(to_be_deleted);
	}
	*list = NULL;
}

int	len_str_list(t_list *list)
{
	t_list	*temp;
	int		len;
	int		i;

	len = 0;
	temp = list;
	if (!temp)
	{
		return (len);
	}
	while (temp)
	{
		if (temp->str_buf)
		{
			i = 0;
			while (temp->str_buf[i])
			{
				i++;
			}
			len += i;
		}
		temp = temp->next;
	}
	return (len);
}

void	append(t_list **list, char *buf)
{
	t_list	*temp;
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	new->str_buf = buf;
	new->next = NULL;
	if (*list == NULL)
	{
		*list = new;
	}
	else
	{
		temp = *list;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
}
