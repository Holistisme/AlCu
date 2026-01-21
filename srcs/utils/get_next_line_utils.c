/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:44:12 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/21 11:31:44 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "AiCu.h"

/**
 * @brief	Create a new vector
 * 
 * @param	nb_octect The size of each element in the vector
 */
t_vector	*ft_new_vector(size_t nb_octect)
{
	t_vector	*new;

	new = (t_vector *)ft_calloc(1, sizeof(t_vector));
	if (!new)
		return ((t_vector *) NULL);
	new->buf = (void *)ft_calloc(2, nb_octect);
	if (!(new->buf))
		return (free(new), (t_vector *) NULL);
	new->index = 0;
	new->max_len = 2;
	new->nb_octect = nb_octect;
	return (new);
}

/**
 * @brief	Add a data to the vector, if the vector is full, it will be resized
 * 
 * @param	s The data to add
 * @param	vector The vector to add the data to
 * @param	len The number of elements to add
 * @return	t_vector* The vector with the new data, or NULL if an error occured
 */
t_vector	*ft_add_char_vector(void *s, t_vector *vector, size_t len)
{
	void	*dbl;

	if (vector->index + len <= vector->max_len)
	{
		ft_memcpy(vector->buf + (vector->index * vector->nb_octect), s, \
		len * vector->nb_octect);
		vector->index = vector->index + len;
	}
	else
	{
		dbl = (void *)ft_calloc(vector->nb_octect,
				((vector->max_len * 2) + len));
		if (!(dbl))
			return ((t_vector *) NULL);
		ft_memcpy(dbl, vector->buf, vector->index * vector->nb_octect);
		vector->max_len = (vector->max_len * 2) + len;
		free(vector->buf);
		vector->buf = (void *)dbl;
		ft_memcpy(vector->buf + (vector->index * vector->nb_octect), s, \
		len * vector->nb_octect);
		vector->index = vector->index + len;
	}
	return (vector);
}

t_vector	*ft_copy_vector(t_vector *vector)
{
	t_vector	*new;

	new = ft_new_vector(vector->nb_octect);
	if (!new)
		return ((t_vector *) NULL);
	if (!ft_add_char_vector(vector->buf, new, vector->index))
	{
		ft_free_vector(&new);
		return ((t_vector *) NULL);
	}
	return (new);
}

/**
 * @brief	Free the memory allocated for the vector
 * 
 * @param	vector The vector to free
 */
void	ft_free_vector(t_vector **vector)
{
	free((*vector)->buf);
	free(*vector);
	*vector = NULL;
}

/**
 * @brief	Frees all allocated memory for the buffer structures
 * 
 * @param	start A pointer to the start of the buffer list
 * @param	tmp The buffer structure to free
 * @param	tmp2 A temporary buffer structure
 * @param	tmp3 A temporary buffer structure
 */
void	ft_free_all(t_buffer **start, t_buffer *tmp, t_buffer *tmp2, \
t_buffer *tmp3)
{
	bool		check;

	check = false;
	tmp3 = *start;
	if (tmp3 == tmp)
		check = true;
	else
		while (tmp3->next != tmp)
			tmp3 = tmp3->next;
	if (tmp != NULL)
	{
		tmp2 = tmp->next;
		free(tmp->vec->buf);
		free(tmp->vec);
		free(tmp);
	}
	tmp = *start;
	if (check)
		*start = tmp2;
	else
	{
		tmp3->next = tmp2;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest != NULL && src != NULL)
	{
		while (n >= sizeof(long long))
		{
			((long long *)dest)[i] = ((long long *)src)[i];
			i++;
			n = n - sizeof(long long);
		}
		i = i * sizeof(long long);
		while (n > 0)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			n--;
			i++;
		}
	}
	return (dest);
}

ssize_t	ft_memchar(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr = (const unsigned char *)s;

	i = 0;
	if (s != NULL)
	{
		while (i < n)
		{
			if (ptr[i] == (unsigned char)c)
				return (i);
			i++;
		}
	}
	return (-1);
}
