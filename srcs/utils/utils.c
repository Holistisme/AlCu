/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:34:13 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/19 18:49:35 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AiCu.h"

/**
 * @brief	Converts a string to an integer.
 * 
 * This function parses the string 'nbr' and converts it to an integer value.
 * It handles optional leading whitespace, an optional sign, and numeric
 * characters.
 * 
 * @param	nbr	The input string representing a number.
 * @return	The integer value represented by the string.
 */
int	ft_atoi(char *nbr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((nbr[i] >= 9 && nbr[i] <= 13) || nbr[i] == 32)
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
	{
		if (nbr[i] == '-')
			sign = -1;
		i++;
	}
	while (nbr[i] >= '0' && nbr[i] <= '9')
	{
		result = result * 10 + (nbr[i] - '0');
		i++;
	}
	return (result * sign);
}

/**
 * @brief	Calculates the length of a string.
 * 
 * This function computes the length of the string 's' by counting the number
 * of characters until the null terminator is encountered.
 * 
 * @param	s The input string.
 * @return	Length of the string.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

/**
 * @brief	Allocates memory for an array and initializes it to zero.
 * 
 * This function allocates memory for an array of 'nmemb' elements, each of
 * size 'size', and initializes all bytes in the allocated memory to zero.
 * 
 * @param	nmemb	Number of elements to allocate.
 * @param	size	Size of each element.
 * @return	Pointer to the allocated memory, or NULL if allocation fails.
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*r;

	if (nmemb < 1 || size < 1)
	{
		r = (void *)malloc(0);
		if (!r)
			return (NULL);
		return (r);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	r = (void *)malloc(size * nmemb);
	if (!r)
		return (NULL);
	ft_memset(r, 0, size * nmemb);
	return (r);
}

/**
 * @brief	Fills a block of memory with a specified byte value.
 * 
 * This function sets the first 'n' bytes of the memory area pointed to by 's'
 * to the specified byte value 'c'.
 * 
 * @param	s	Pointer to the memory area to be filled.
 * @param	c	Byte value to set (converted to unsigned char).
 * @param	n	Number of bytes to be set to the value.
 * @return	Pointer to the memory area 's'.
 */
void	*ft_memset(void *s, int c, size_t n)
{
	size_t		i;
	long long	c8;

	i = -1;
	c8 = 0;
	while (++i < sizeof(long long))
		c8 = c8 | (long long)(unsigned char)c << 8 * i;
	i = 0;
	while (n > sizeof(long long))
	{
		((long long *)s)[i] = c8;
		i++;
		n = n - sizeof(long long);
	}
	i = i * sizeof(long long);
	while (n > 0)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
		n--;
	}
	return (s);
}

/**
 * @brief	Outputs an integer to standard output.
 * 
 * This function converts the given integer to its string representation
 * and writes it to the standard output (file descriptor 1).
 * 
 * @param	nbr	The integer to be printed.
 */
void	ft_putnbr(int nbr)
{
	char	c;

	if (nbr == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
	}
	c = "0123456789"[nbr % 10];
	write(1, &c, 1);
}

/**
 * @brief	Outputs an error message to standard error.
 * 
 * This function writes the provided error message to the standard error
 * output (file descriptor 2).
 * 
 * @param	msg	The error message to be displayed.
 */
void	ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
}
