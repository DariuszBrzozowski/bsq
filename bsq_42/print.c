/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	print_map_info(int rows, char markers[3], int cols)
{
	ft_putnbr(rows);
	write(1, markers, 3);
	ft_putnbr(cols);
	ft_putchar('\n');
}

void	print_grid(char **grid, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		write(1, grid[i], cols);
		ft_putchar('\n');
		i++;
	}
}

int	map_error(void)
{
	write(2, "map error\n", 10);
	return (1);
}
