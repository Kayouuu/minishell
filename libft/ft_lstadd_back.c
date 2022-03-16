/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:08:06 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/16 16:18:43 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Add an element at the end of the list */

#include "libft.h"

void	*ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	tmp = *alst;
	if (!new)
		return (NULL);
	if (*alst)
	{
		tmp = ft_lstlast(*alst);
		tmp->next = new;
	}
	else
		*alst = new;
	return ((void *)1);
}
