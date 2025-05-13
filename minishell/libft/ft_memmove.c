/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 23:15:00 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 23:15:01 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*src2;
	unsigned char		*dst2;

	if (!dst && !src)
		return (NULL);
	src2 = (const unsigned char *) src;
	dst2 = (unsigned char *) dst;
	if (dst2 > src2 && dst2 < src2 + len)
	{
		while (len > 0)
		{
			dst2[len - 1] = src2[len - 1];
			len--;
		}
		return (dst);
	}
	i = 0;
	while (i < len)
	{
		dst2[i] = src2[i];
		i++;
	}
	return (dst);
}
/*
int main() {
	char str1[] = "abcdef";
	char str2[] = "abcdef";
	memmove(str1 + 2, str1, 4);
	ft_memmove(str2 + 2, str2, 4);
	//printf("Or dst1 = %s\nMy dst2 = %s\n", dst1, dst2);
	printf("Or str1 = %s\nMy str2 = %s", str1, str2);

}
*/
