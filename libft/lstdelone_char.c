/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstdelone_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:50:27 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/16 15:50:41 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lstdelone_char(t_list_char *lst, void (*del)(void *))
{
	if (del)
		del(lst->content);
	free(lst);
}
