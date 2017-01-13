/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahunt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 15:46:42 by ahunt             #+#    #+#             */
/*   Updated: 2016/12/07 19:09:10 by ahunt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_memory(char **mem, char **line, int endl)
{
	char	*nl_ptr;
	char	*temp;

	if (!endl)
		temp = ft_strdup(*mem);
	if (!endl && (nl_ptr = ft_strchr(temp, '\n')))
	{
		*nl_ptr = '\0';
		*line = ft_strdup(temp);
		ft_strdel(mem);
		*mem = ft_strdup((const char*)(nl_ptr + 1));
		ft_strdel(&temp);
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

static int	parse_newline(char **mem, char **buffer, char **line)
{
	char	*nl_ptr;

	if ((nl_ptr = ft_strchr(*buffer, '\n')))
	{
		*nl_ptr = '\0';
		if (*mem)
		{
			*line = ft_strjoin(*mem, *buffer);
			ft_strdel(mem);
		}
		else
			*line = ft_strdup(*buffer);
		*mem = ft_strdup(nl_ptr + 1);
		ft_strdel(buffer);
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
		if (parse_newline(&mem, &buffer, line))
			return (1);
		mem = mem != NULL ? ft_strjoin(mem, buffer) : ft_strdup(buffer);
	}
	ft_strdel(&buffer);
	if (size_read == -1)
		return (-1);
	if (mem && *mem && read_memory(&mem, line, 1))
		return (1);
	return (0);
}
