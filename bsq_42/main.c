/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	init_grid(char *fname, char markers[3], int *rows, int *cols)
{
	*rows = get_first_line_info(fname, markers);
	*cols = get_columns_cnt(fname, *rows);
	if (*rows < 1 || *cols < 1)
		return (1);
	return (0);
}

int	read_map(char *fname, char ***grid, int rows, int cols)
{
	*grid = ft_alloc_malloc(rows, cols);
	if (!*grid)
		return (1);
	if (read_grid(fname, *grid, rows, cols) != 0)
	{
		ft_free_malloc(*grid, rows);
		return (1);
	}
	return (0);
}

int	load_map(char *fname, char markers[3], char ***grid, int *rows)
{
	int	cols;

	if (init_grid(fname, markers, rows, &cols) != 0)
		return (1);
	if (read_map(fname, grid, *rows, cols) != 0)
		return (1);
	if (validate_grid(*grid, *rows, cols, markers) != 0)
	{
		ft_free_malloc(*grid, *rows);
		return (1);
	}
	print_map_info(*rows, markers, cols);
	print_grid(*grid, *rows, cols);
	return (0);
}

int	process_map(char *fname)
{
	int		rows;
	char	markers[3];
	char	**grid;

	if (load_map(fname, markers, &grid, &rows) != 0)
		return (map_error());
	ft_free_malloc(grid, rows);
	return (0);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	status;

	if (argc == 1)
		return (process_stdin());
	i = 1;
	status = 0;
	while (i < argc)
	{
		if (process_map(argv[i]) != 0)
			status = 1;
		if (i + 1 < argc)
			write(1, "\n", 1);
		i++;
	}
	return (status);
}
