/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: argharag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:27:13 by argharag          #+#    #+#             */
/*   Updated: 2025/01/25 20:48:46 by argharag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*void	my_f(void *lst)
{
	(void)lst;
}
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
int main()
{
	t_list	*node1 = ft_lstnew("Artur");
	t_list	*node2 = ft_lstnew("Kiril");
	t_list	*node3 = ft_lstnew("Samson");

	node1->next = node2;
	node2->next = node3;
	t_list *all = node1;
	ft_lstiter(node1,&my_f);
	while (all)
	{
		printf("%s\n",all->content);
		all = all->next;
	}
}*/
