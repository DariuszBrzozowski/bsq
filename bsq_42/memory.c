/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	ft_free_malloc(char **arr, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**ft_alloc_malloc(int row, int col)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * row);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < row)
	{
		arr[i] = malloc(sizeof(char) * col);
		if (!arr[i])
		{
			ft_free_malloc(arr, i);
			return (NULL);
		}
		i++;
	}
	return (arr);
}
