/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:26:39 by ysachiko          #+#    #+#             */
/*   Updated: 2021/11/22 19:07:17 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_read_from_fd(int fd, char *buf, char **line)
{
	int			rs;
	char		*tmp;

	if (!*line || !ft_strchr(*line, '\n'))
	{
		rs = read(fd, buf, BUFFER_SIZE);
		while (rs > 0)
		{
			buf[rs] = 0;
			if (!*line)
				*line = ft_substr(buf, 0, rs);
			else
			{
				tmp = *line;
				*line = ft_strjoin(*line, buf);
				free(tmp);
			}
			if (ft_strchr(buf, '\n'))
				break ;
			rs = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
}

static char	*ft_proc(char **line)
{
	char		*ost;
	char		*tmp;
	int			i;
	int			j;

	if (!ft_strchr(*line, '\n'))
	{
		ost = ft_substr(*line, 0, ft_strlen(*line));
		free(*line);
		*line = NULL;
		return (ost);
	}
	i = ft_strlen(*line);
	j = ft_strlen(ft_strchr(*line, '\n'));
	ost = ft_substr(*line, 0, i - j + 1);
	tmp = *line;
	*line = ft_substr(ft_strchr(*line, '\n'), 1, j);
	free(tmp);
	return (ost);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd == -1 || BUFFER_SIZE <= 0 || !buf || read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	ft_read_from_fd(fd, buf, &line);
	if (!line)
		return (NULL);
	return ((ft_proc(&line)));
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("file", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 		printf("%s", line);
// 	free(line);
// 	return (0);
// }
