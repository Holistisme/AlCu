/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:33:32 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/19 16:48:23 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_vector
{
	char	*buf;
	size_t	index;
	size_t	max_len;
	size_t	nb_octect;
}	t_vector;

typedef struct s_buffer
{
	t_vector		*vec;
	int				fd;
	struct s_buffer	*next;
	bool			end;
}	t_buffer;

/*Get_next_line*/

char		*get_next_line(int fd, int end);

/*Get_next_line_utils*/

t_vector	*ft_new_vector(size_t nb_octect);
t_vector	*ft_add_char_vector(void *s, t_vector *vector, size_t len);
void		ft_free_vector(t_vector **vector);
void		ft_free_all(t_buffer **start, t_buffer *tmp, t_buffer *tmp2, \
t_buffer *tmp3);
void		*ft_memcpy(void *dest, const void *src, size_t n);
ssize_t		ft_memchar(const void *s, int c, size_t n);

#endif