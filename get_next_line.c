/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:46:42 by ahunt             #+#    #+#             */
/*   Updated: 2016/10/31 12:04:58 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdlib.h"
#include "stdio.h"


static int	read_memory(char **mem, char **line, int endl)
{
	char	*nl_ptr;

	if ((nl_ptr = ft_strchr(*mem, '\n')))
	{
		*nl_ptr = '\0';
		*line = ft_strdup(*mem);
		free(*mem);
		*mem = ft_strdup(nl_ptr + 1);
		return (1);
	}
	else if (endl)
	{
		*line = ft_strdup(*mem);
		ft_strdel(mem);
		return (1);
	}
	return (0);
}

static int	parse_newline(char **mem, char *buffer, char **line)
{
	char	*nl_ptr;

	if ((nl_ptr = ft_strchr(buffer, '\n')))
	{
		*nl_ptr = '\0';
		if (*mem)
		{
			*line = ft_strjoin(*mem, buffer);
			free(*mem);
		}
		else
			*line = ft_strdup(buffer);
		*mem = ft_strdup(nl_ptr + 1);
		free(buffer);
		return (1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	static char *mem = NULL;
	char		*buffer;
	int			size_read;

	buffer = ft_strnew(BUFF_SIZE);
	if (line == NULL || fd < 0)
		return (-1);
	if (mem && read_memory(&mem, line, 0))
		return (1);
	while ((size_read = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[size_read] = '\0';
		if (parse_newline(&mem, buffer, line))
			return (1);
		mem = mem != NULL ? ft_strjoin(mem, buffer) : ft_strdup(buffer);
	}
	free(buffer);
	if (size_read == -1)
		return (-1);
	if (mem && *mem && read_memory(&mem, line, 1))
		return (1);
	return (0);
}

int	main(void)
{
	char *line;
	int	ret;
	int fd;

	if ((fd = open("test.text", O_RDONLY, 06000)) == -1)
		return (0);
	ret = get_next_line(fd, &line);
	ft_putstr("Return: ");
	ft_putnbr(ret);
	ft_putstr("   Line: ");
	if (line == NULL || *line == '\0')
		ft_putendl("NULL");
	else
		ft_putendl(line);
	return (0);
}
