/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	read_header(int fd, char markers[3], int *rows)
{
	char	c;
	int		bytes;
	int		len;

	init_header(markers, &len, rows);
	bytes = read(fd, &c, 1);
	while (bytes > 0 && c != '\n')
	{
		if (update_header(markers, c, len, rows) < 0)
			return (-4);
		len++;
		bytes = read(fd, &c, 1);
	}
	if (bytes <= 0 || len < 4)
		return (-2);
	return (0);
}

int	get_first_line_info(char *fname, char markers[3])
{
	int	fd;
	int	rows;
	int	status;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
		return (-1);
	status = read_header(fd, markers, &rows);
	close(fd);
	if (status < 0)
		return (status);
	if (validate_markers(markers) != 0)
		return (-5);
	return (rows);
}
