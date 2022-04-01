/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstnew_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbattest <lbattest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:55:05 by lbattest          #+#    #+#             */
/*   Updated: 2022/03/16 15:33:10 by lbattest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_char	*lstnew_char(char *content)
{
	t_list_char	*list;

	list = malloc(sizeof(t_list_char));
	if (!list)
		return (0);
	list->content = content;
	list->next = 0;
	return (list);
}
