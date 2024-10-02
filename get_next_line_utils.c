/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onosul <onosul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:04:16 by onosul            #+#    #+#             */
/*   Updated: 2024/10/02 17:04:34 by onosul           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	polish_list(t_list **list)
{
	char	*buf;
	int		i;
	int		k;
	t_list	*last_node;
	t_list	*clean_node;

	i = 0;
	k = 0;
	last_node = *list;
	if (!*list)
		return ;
	while (last_node->next)
		last_node = last_node->next;
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!buf || !clean_node)
		return ;
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

int	len_str_list(t_list *list)
{
	int	len;
	int	i;

	len = 0;
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

char	*parse_list(t_list *list, char *result)
{
	int	i;
	int	j;

	j = 0;
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
		return ;
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
