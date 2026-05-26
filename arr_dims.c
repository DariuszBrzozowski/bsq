/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_dims.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 13:08:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/26 21:36:14 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	get_header_cnt(char *fname)
{
	char	c;
	int		descr;
	int		header_cnt;

	descr = open(fname, O_RDONLY);
	if (descr == -1)
		return (-1);
	c = read(descr, &c, 1);
	if (c == '\n')
		return (-2);
	header_cnt = 0;
	while (c != '\n')
	{
		header_cnt++;
		read(descr, &c, 1);
	}
	close(descr);
	return (header_cnt);
}

int	get_first_line_info(char *fname, char markers[3])
{
	char	c;
	int		descr;
	int		header_cnt;
	int		i;
	int		row_cnt;

	row_cnt = 0;
	i = 0;
	descr = open(fname, O_RDONLY);
	if (descr == -1)
		return (-1);
	c = read(descr, &c, 1);
	if (c == '\n')
		return (-2);
	header_cnt = get_header_cnt(fname);
	while (i < header_cnt)
	{
		read(descr, &c, 1);
		if (i < header_cnt - 3)
		{
			if (!(c >= '0' && c <= '9'))
				return (-3);
			row_cnt = row_cnt * 10 + c - '0';
		}
		else
			markers[-(header_cnt - i - 3)] = c;
		i++;
	}
	close (descr);
	return (row_cnt);
}

int	get_columns_cnt(char *fname, int row_cnt, int min, int max)
{
	char	c;
	int		i;
	int		j;
	int		descr;

	descr = open(fname, O_RDONLY);
	if (descr == -1)
		return (-1);
	i = 0;
	j = 0;
	while (read(descr, &c, 1) > 0)
	{
		if (i > row_cnt)
			return (-4);
		j ++;
		if (c == '\n')
		{
			if (j > max)
				max = j;
			if (j < min)
				min = j;
			j = 0;
			i++;
		}
	}
	close(descr);
	if (max == min)
		return (max);
	else
		return (-5);
}
