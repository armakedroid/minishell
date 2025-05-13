/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:08:39 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 21:25:02 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	my_f(unsigned int i,char *str)
{
		printf("%c",str);
}
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f (i, &s[i]);
		i++;
	}
}
/*
int main()
{
	char a[] = "Artur jan barev";
   ft_striteri(a, &my_f);
}*/
