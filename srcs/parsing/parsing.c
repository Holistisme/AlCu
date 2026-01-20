/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:15:07 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/20 15:29:02 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"
#include "get_next_line.h"

/**
 * @brief	Checks if the input arguments indicate sparse input.
 * 
 * This function determines whether the program should read from standard input
 * or from a specified file based on the command-line arguments.
 * 
 * @param	ac	Argument count from the command line.
 * @param	av	Argument vector from the command line.
 * @param	tab	Pointer to the game board vector.
 * @param	max	Pointer to the maximum number of matches in any line.
 * @return	True if sparse input handling is successful, false otherwise.
 */
bool	this_is_sparsing(int ac, char **av, t_vector *tab, int *max)
{
	if (ac < 2)
	{
		if (!ft_read_stdin(tab, 0, max))
			return (false);
	}
	else
	{
		for (int i = 1; i < ac; i++)
		{
			if (!ft_open(av[i], tab, max))
				return (false);
		}
	}
	return (true);
}

/**
 * @brief	Checks if the buffer contains a valid number.
 * 
 * This function verifies that the provided buffer consists solely of numeric
 * characters, optionally followed by a newline character.
 * 
 * @param	buf	The input buffer to check.
 * @return	True if the buffer is a valid number, false otherwise.
 */
bool	ft_buf_is_number(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		if (buf[i] < '0' || buf[i] > '9')
			return (false);
		i++;
	}
	if (buf[i] == '\n' && buf[i + 1] != '\0')
		return (false);
	return (true);
}

/**
 * @brief	Reads game board configuration from standard input.
 * 
 * This function reads lines from the specified file descriptor (typically
 * standard input) and populates the game board vector with the number of
 * matches for each line. It also updates the maximum number of matches found.
 * 
 * @param	tab	Pointer to the game board vector.
 * @param	fd	File descriptor to read from.
 * @param	max	Pointer to the maximum number of matches in any line.
 * @return	True if reading and parsing is successful, false otherwise.
 */
bool	ft_read_stdin(t_vector *tab, int fd, int *max)
{
	char	*buf;
	int		nbr;

	while ((buf = get_next_line(fd, 0)) != NULL)
	{
		if (buf[0] == '\n' || buf[0] == '\0')
		{
			free(buf);
			get_next_line(fd, 1);
			break ;
		}
		nbr = ft_atoi(buf);
		if (nbr < 1 || nbr > 10000 || !ft_buf_is_number(buf))
		{
			ft_error("ERROR\n");
			return (free(buf), false);
		}
		(*max)  = (nbr > *max) ? nbr : *max;
		if (!ft_add_char_vector(&nbr, tab, 1))
		{
			ft_error("ERROR\nCould't allocate memory\n");
			return (free(buf), false);
		}
		free(buf);
	}
	return (true);
}

/**
 * @brief	Opens a file and reads the game board configuration.
 * 
 * This function attempts to open the specified file, checks for read
 * permissions, and then reads the game board configuration using the
 * ft_read_stdin function.
 * 
 * @param	file	The name of the file to open.
 * @param	tab	Pointer to the game board vector.
 * @param	max	Pointer to the maximum number of matches in any line.
 * @return	True if the file is successfully opened and read, false otherwise.
 */
bool	ft_open(char *file, t_vector *tab, int *max)
{
	int		fd, test;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_error("ERROR\nCould't open file\n");
		return (false);
	}
	test = read(fd, NULL, 0);
	if (test < 0)
	{
		ft_error("ERROR\nCould't read file\n");
		close(fd);
		return (false);
	}
	if (!ft_read_stdin(tab, fd, max))
	{
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
