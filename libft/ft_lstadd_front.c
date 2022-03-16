/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:03:48 by psaulnie          #+#    #+#             */
/*   Updated: 2022/03/16 15:57:09 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* At an element at the start of the list 									  */

#include "libft.h"

void	*ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!new)
		return (NULL);
	new->next = (*alst);
	(*alst) = new;
	return ((void *)1);
}
