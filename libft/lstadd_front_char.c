/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_front_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:26:46 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/17 09:37:04 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*lstadd_front_char(t_list_char **alst, t_list_char *new)
{	
	if (!new)
		return (NULL);
	if (alst == 0)
		alst[0] = new;
	else
	{
		new->next = *alst;
		*alst = new;
	}
	return ((void *) 1);
}
