/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_columns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	skip_column_header(int fd)
{
	char	c;

	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			return (0);
	}
	return (-1);
}

int	check_column(int *cols, int col)
{
	if (*cols == -1)
		*cols = col;
	else if (*cols != col)
		return (-4);
	return (0);
}

int	open_map_file(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (skip_column_header(fd) < 0)
	{
		close(fd);
		return (-2);
	}
	return (fd);
}

int	update_columns(char c, int *col, int *cols, int *row)
{
	if (c != '\n')
	{
		(*col)++;
		return (0);
	}
	if (check_column(cols, *col) < 0)
		return (-4);
	*col = 0;
	(*row)++;
	return (0);
}

int	get_columns_cnt(char *fname, int row_cnt)
{
	char	c;
	int		fd;
	int		row;
	int		col;
	int		cols;

	fd = open_map_file(fname);
	if (fd < 0)
		return (fd);
	row = 0;
	col = 0;
	cols = -1;
	while (read(fd, &c, 1) > 0)
	{
		if (update_columns(c, &col, &cols, &row) < 0)
		{
			close(fd);
			return (-4);
		}
	}
	close(fd);
	if (row != row_cnt || cols < 1)
		return (-3);
	return (cols);
}
