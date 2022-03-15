/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:57:29 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 14:01:04 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the last element of the list										  */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == 0)
		return (0);
	while (lst)
	{
		last = lst;
		lst = lst->next;
	}
	return (last);
}
