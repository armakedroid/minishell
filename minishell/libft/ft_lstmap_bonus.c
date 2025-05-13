/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:19:15 by argharag          #+#    #+#             */
/*   Updated: 2025/01/27 20:34:01 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	*my_f(void *c)
{
	int i = 0;
	char *str;

	str = ft_strdup((char *)c);
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (i % 2)
			str[i] -= 32;
		i++;
	}
	
	return (str);
}

void	my_del(void *c)
{
	free(c);
}
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*back;
	t_list	*second;
	void	*cont;

	back = NULL;
	while (lst)
	{
		cont = f(lst->content);
		if (!cont)
		{
			ft_lstclear(&back, del);
			return (NULL);
		}
		second = ft_lstnew(cont);
		if (!second)
		{
			del(cont);
			ft_lstclear(&back, del);
			return (NULL);
		}
		ft_lstadd_back(&back, second);
		lst = lst->next;
	}
	return (back);
}
/*
int	main()
{
	t_list *node1 = ft_lstnew(ft_strdup("Artur"));
	t_list *node2 = ft_lstnew(ft_strdup("jan"));
	t_list *node3 = ft_lstnew(ft_strdup("hajox"));

	node1->next = node2;
	node2->next = node3;
	t_list *all = node1;

	t_list *map = ft_lstmap(all,&my_f,&my_del);
	t_list *cur = map;
	
	
	while (cur)
	{
		printf("%s\n",(char *)cur->content);
		cur = cur->next;
	}
}
*/
