#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int get_first_line_info(char *fname, char markers[3])
{
	char c;
	int descr;
	int fl_cnt;
	int i;
	int out;

	out = 0;
	descr = open(fname, O_RDONLY);
	if (descr == -1)
		return -1;
	c = read(descr, &c, 1);
	if (c == '\n')
		return -2;
	fl_cnt = 0;
	while (c != '\n')
	{
		fl_cnt++;
		read(descr, &c, 1);
		
	}	
	close(descr);
	descr = open(fname, O_RDONLY);
	if (descr == -1)
		return -3;
	i = 0;
	while (i < fl_cnt)
	{
		read(descr, &c, 1);
		if (i < fl_cnt - 3)
		{
			if (!(c >= '0' && c <= '9'))
				return (-4);
			out = out * 10 + c  - '0';
		}
		else
			markers[-(fl_cnt - i - 3)] = c;

		i++;
	}
	close (descr);
	return (out);
}

int get_columns_cnt(char *fname, int row_cnt, char markers[3])
{
	char c;
	int descr;
	int col_cnt_per_row[row_cnt];
        int bytes_read;
	int i;
	int j;

	(void)markers;
	j = 0;
	/*col_cnt_per_row = {0};*/
        descr = open(fname, O_RDONLY);
        if (descr == -1)
                return -1;
        i = 0;
	bytes_read = read(descr, &c, 1);
	while (bytes_read  > 0)
	{
		if (i > row_cnt)
			return (-3);
        	j ++;	
                if (c == '\n')
		{
			col_cnt_per_row[i] = j;
			j = 0;	
			i++;
		}

		bytes_read = read(descr, &c, 1);
        }
        close(descr);
        
	i = 1;
	while (i < row_cnt -1)
	{
		j = i+1;
		while (j < row_cnt)
		{
			if (col_cnt_per_row[i] != col_cnt_per_row[j])
				return (-4);
			j++;
		}
		i++;
	}


	return (col_cnt_per_row[1] - 1);
}


int	read_grid(char *fname, char **grid, int rows, int cols)
{
	char	c;
	int		descr;
	int		i;
	int		j;

	descr = open(fname, O_RDONLY);
	if (descr == -1)
		return (-1);
	if (!grid)
	{
		close(descr);
		return (-2);
	}
	i = 0;
	while (i < rows)
	{
		grid[i] = malloc(sizeof(char) * (cols + 1));
		if (!grid[i])
		{
			close(descr);
			return (-2);
		}
		i++;
	}
	while (read(descr, &c, 1) > 0 && c != '\n');
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (read(descr, &c, 1) <= 0)
				return (-3);
			if (c == '\n')
				return (-4);
			grid[i][j] = c;
			j++;
		}
		grid[i][j] = '\0';
		read(descr, &c, 1);
		i++;
	}
	close(descr);
	return (0);
}

int main(int argc, char *argv[])
{
	int row;
	int col;
	int status;
	int i;
	char markers[3];
	char **arr;

	if (argc != 2)
		return (1);
	row = get_first_line_info(argv[1], markers);
	col = get_columns_cnt(argv[1], row, markers);
	printf("%d", row);
	printf("%c", markers[0]);
	printf("%c", markers[1]);
	printf("%c", markers[2]);
	printf("%d", col);
	if (row <= 0 || col <= 0)
		return (1);
	arr = malloc(sizeof(char *) * row);
	if (!arr)
		return (1);
	status = read_grid(argv[1], arr, row, col);
	if (status != 0)
	{
		free(arr);
		return (1);
	}
	i = 0;
	while (i < row)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}
