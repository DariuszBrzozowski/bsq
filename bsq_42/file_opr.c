/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	skip_grid_header(int fd)
{
	char	c;

	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			return (0);
	}
	return (-1);
}

int	read_row(int fd, char *row, int cols)
{
	char	c;
	int		i;

	i = 0;
	while (i < cols)
	{
		if (read(fd, &c, 1) <= 0 || c == '\n')
			return (-3);
		row[i] = c;
		i++;
	}
	if (read(fd, &c, 1) <= 0 || c != '\n')
		return (-4);
	return (0);
}

int	open_grid_file(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (skip_grid_header(fd) < 0)
	{
		close(fd);
		return (-2);
	}
	return (fd);
}

int	read_grid(char *fname, char **grid, int rows, int cols)
{
	int	fd;
	int	i;

	fd = open_grid_file(fname);
	if (fd < 0)
		return (fd);
	i = 0;
	while (i < rows)
	{
		if (read_row(fd, grid[i], cols) != 0)
		{
			close(fd);
			return (-3);
		}
		i++;
	}
	close(fd);
	return (0);
}
