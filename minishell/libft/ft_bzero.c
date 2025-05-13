/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:27:48 by argharag          #+#    #+#             */
/*   Updated: 2025/01/18 21:28:05 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*str;

	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
#include <string.h>

int main() {
	char str[] = "Artur Barev dzez";
	char str1[] = "Artur Barev dzez";
	bzero(str + 5, 2);
	ft_bzero(str1 + 5, 2);
	printf("%s\n", str);
	printf("%s", str1);
}
*/
