/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apetoyan <apetoyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:32:28 by apetoyan          #+#    #+#             */
/*   Updated: 2025/04/23 22:07:59 by apetoyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_calmalloc(char **a)
{
	if (*a == NULL)
	{
		*a = (char *)malloc(sizeof(char));
		if (!*a)
			return (NULL);
		**a = '\0';
	}
	return (*a);
}

char	*ft_merge(char *a, char *b)
{
	char	*back;
	int		i;
	int		k;

	if (!ft_calmalloc(&a))
		return (NULL);
	back = (char *)malloc(ft_strlen(a) + ft_strlen(b) + 1);
	if (!back)
	{
		free(a);
		return (NULL);
	}
	i = -1;
	while (a[++i])
		back[i] = a[i];
	k = 0;
	while (b[k])
		back[i++] = b[k++];
	back[i] = '\0';
	free(a);
	if (back[0] == '\0')
		return (free(back), NULL);
	return (back);
}

static char	*nonstr(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		buf[BUFFER_SIZE + 1];
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 1;
	while (!ft_sep(str[fd], '\n') && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			if (str[fd])
				free(str[fd]);
			str[fd] = NULL;
			return (NULL);
		}
		buf[i] = '\0';
		str[fd] = ft_merge(str[fd], buf);
	}
	if (!str[fd] || !*str[fd])
		return (nonstr(&str[fd]));
	return (ft_fill(&str[fd]));
}
/*
int main()
{
	int fd = open("test.txt", O_RDONLY);
	get_next_line(fd);
	get_next_line(fd);
	get_next_line(fd);
}*/
