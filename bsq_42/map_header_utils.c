/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	init_header(char markers[3], int *len, int *rows)
{
	markers[0] = 0;
	markers[1] = 0;
	markers[2] = 0;
	*len = 0;
	*rows = 0;
}

int	update_header(char markers[3], char c, int len, int *rows)
{
	if (len >= 3 && !ft_is_digit(markers[0]))
		return (-4);
	if (len >= 3)
		*rows = *rows * 10 + markers[0] - '0';
	markers[0] = markers[1];
	markers[1] = markers[2];
	markers[2] = c;
	return (0);
}

int	validate_markers(char markers[3])
{
	if (markers[0] == markers[1])
		return (1);
	if (markers[0] == markers[2])
		return (1);
	if (markers[1] == markers[2])
		return (1);
	return (0);
}
