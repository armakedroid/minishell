/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:33:58 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:24:34 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}
/*
int main()
{
	char str[] = "Artur barev dzez";
	char str1[] = "Artur barev dzez";
	memset(str, 'O', 5);
	printf("%s\n", str);
	ft_memset(str1, 'O', 5);
	printf("%s", str1);
}
*/
