/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 10:50:44 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/09 11:30:42 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the size of the list												  */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		counter++;
		lst = lst-> next;
	}
	return (counter);
}
