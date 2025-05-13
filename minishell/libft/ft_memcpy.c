/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:15:14 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 23:15:16 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	const unsigned char	*src2;
	unsigned char		*dst2;

	if (!dst && !src)
		return (NULL);
	src2 = (const unsigned char *) src;
	dst2 = (unsigned char *) dst;
	i = 0;
	while (i < n)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
/*
int main() {
	char *str1 = NULL;
	char *dst1 = NULL;
	char *str2 = NULL;
	char *dst2 = NULL;
	memcpy(dst1, str1, 4);
	ft_memcpy(dst2, str2, 4);
	printf("%s\n%s\n", dst1, dst2);
	printf("%s\n%s", str1, str2);
 
}
*/
