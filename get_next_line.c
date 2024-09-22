
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*get_line(t_list *list)
{
	t_list	*temp;
	char	*str;
	char	*str_ptr;
	int		i;

	str = (char *)malloc(len_str_list(list) + 1);
	str_ptr = str;
	temp = list;
	while (temp)
	{
		i = 0;
		if (temp->str_buf)
		{
			while (temp->str_buf[i])
			{
				*str_ptr = temp->str_buf[i];
				str_ptr++;
				i++;
			}
		}
		temp = temp->next;
	}
	*str_ptr = '\0';
	return (str);
}

int	found_newline(t_list **list)
{
	t_list	*temp;
	int		i;

	temp = *list;
	while (temp)
	{
		i = 0;
		if (temp->str_buf)
		{
			while (temp->str_buf[i])
			{
				if (temp->str_buf[i] == '\n')
					return (1);
				i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(list))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	// if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, next_line, 0) < 0)
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	clear_list(&list);
	return (next_line);
}

// int	main(void)
// {
// 	int fd;
// 	fd = open("sample.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	write(fd, "Hello WorldThis\n is a test\n", 27);  // Write test data
// 	lseek(fd, 0, SEEK_SET);  // Rewind file descriptor to the beginning

// 	char *result;
// 	while ((result = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", result);  // Print each line read
// 		free(result);  // Free the allocated line buffer
// 	}

// 	close(fd);  // Close the file descriptor
// 	return (0);
// }