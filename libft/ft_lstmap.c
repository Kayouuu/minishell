/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:58:43 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/14 10:42:11 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Clear if necessary with del the element of the list 						  */
/* to create a new one using f												  */

#include "libft.h"

static void	delete(t_list **init, void (*del)(void *))
{
	t_list	*next;

	while (*init)
	{
		next = (*init)->next;
		if (*init)
			del((*init));
		*init = next;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*tmp;
	t_list	*init;

	if (lst == 0)
		return (0);
	new_lst = ft_lstnew((*f)(lst->content));
	init = new_lst;
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew((*f)(lst->content));
		if (!tmp)
		{
			delete(&init, (*del));
			return (0);
		}
		ft_lstadd_back(&new_lst, tmp);
		lst = lst->next;
		new_lst = new_lst->next;
	}
	new_lst->next = NULL;
	return (init);
}
