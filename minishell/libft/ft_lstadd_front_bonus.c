/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 21:31:32 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 20:45:22 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new ->next = *lst;
	*lst = new;
}
/*
int main(void) 
{
	t_list *node1 = ft_lstnew("Artur");
	t_list *node2 = ft_lstnew("jan");
	t_list *node3 = ft_lstnew("barev");

	node1->next = node2;
	t_list *all = node1;
	ft_lstadd_front(&all, node3);

	t_list *i = all;
	while (i)
	{
		printf("%s\n", (char *)i->content);
		i = i->next;
	}
}*/
