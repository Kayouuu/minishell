/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 09:03:48 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/10 11:52:59 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* At an element at the start of the list 									  */

#include "libft.h"

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	new->next = (*alst);
	(*alst) = new;
}
