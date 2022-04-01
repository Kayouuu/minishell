/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_back_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:46:14 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/17 09:42:57 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*lstadd_back_char(t_list_char **alst, t_list_char *new)
{
	t_list_char	*temp;

	if (!new)
		return (NULL);
	if (*alst == 0)
	{
		*alst = new;
		return ((void *) 1);
	}
	temp = lstlast_char(*alst);
	temp->next = new;
	return ((void *)1);
}
