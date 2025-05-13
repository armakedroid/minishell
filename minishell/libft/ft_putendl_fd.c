/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:03:30 by argharag          #+#    #+#             */
/*   Updated: 2025/01/18 22:03:32 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
/*
int main()
{
	int	fd;
	char c[] = "Artur";

	fd = open("./test2.txt",O_WRONLY | O_CREAT, 0644);
	ft_putendl_fd(c,fd);	
}*/
