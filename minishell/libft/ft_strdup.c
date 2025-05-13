/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 22:04:54 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:24:58 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str1;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1) + 1;
	str1 = (char *) malloc (sizeof(char) * size);
	if (!str1)
		return (NULL);
	i = 0;
	while (i < size)
	{
		str1[i] = s1[i];
		i++;
	}
	return (str1);
}
/*
int main() {
	char str[] = "Artur";
	char *str2 = ft_strdup(str);
	printf("%s", str2);
	
}
*/
