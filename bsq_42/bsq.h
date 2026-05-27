/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrzozow <dbrzozow@student.42warsaw.p      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:20:00 by dbrzozow          #+#    #+#             */
/*   Updated: 2026/05/27 08:20:00 by dbrzozow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		get_first_line_info(char *fname, char markers[3]);
int		ft_is_digit(char c);
void	init_header(char markers[3], int *len, int *rows);
int		update_header(char markers[3], char c, int len, int *rows);
int		validate_markers(char markers[3]);
int		get_columns_cnt(char *fname, int row_cnt);
int		read_grid(char *fname, char **grid, int rows, int cols);
int		validate_grid(char **grid, int rows, int cols, char markers[3]);
char	**ft_alloc_malloc(int row, int col);
void	ft_free_malloc(char **arr, int row);
int		process_map(char *fname);
int		process_stdin(void);
int		map_error(void);
void	print_map_info(int rows, char markers[3], int cols);
void	print_grid(char **grid, int rows, int cols);

#endif
