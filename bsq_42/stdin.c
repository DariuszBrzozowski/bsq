/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	copy_stdin_to_file(char *fname)
{
	char	buffer[4096];
	int		fd;
	int		bytes;

	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (1);
	bytes = read(0, buffer, 4096);
	while (bytes > 0)
	{
		if (write(fd, buffer, bytes) != bytes)
		{
			close(fd);
			return (1);
		}
		bytes = read(0, buffer, 4096);
	}
	close(fd);
	if (bytes < 0)
		return (1);
	return (0);
}

int	process_stdin(void)
{
	char	*fname;
	int		status;

	fname = "/tmp/bsq_stdin_map";
	if (copy_stdin_to_file(fname) != 0)
		return (map_error());
	status = process_map(fname);
	unlink(fname);
	return (status);
}
