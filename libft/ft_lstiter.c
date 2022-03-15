/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:12:10 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/12 15:10:18 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Iterate on the list and apply the function f on each element of the list   */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(*f)(lst->content);
		lst = lst->next;
	}
}
