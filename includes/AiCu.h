/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AiCu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:26:47 by benpicar          #+#    #+#             */
/*   Updated: 2026/01/20 06:55:43 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <stdint.h>
#include "get_next_line.h"

/** paring.c */

bool	ft_read_stdin(t_vector *tab, int fd, int *max);
bool	ft_open(char *file, t_vector *tab, int *max);
bool	this_is_sparsing(int ac, char **av, t_vector *tab, int *max);

/** Ai.c */

void	ft_run(t_vector *tab, int max);
void	ft_player_move(t_vector *tab);
int		ft_ai_move(t_vector *tab);

/** print.c */

void	ft_print_board(t_vector *tab, int max);


/** utils.c */

void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	ft_error(char *msg);
size_t	ft_strlen(const char *s);
int		ft_atoi(char *nbr);
void	ft_putnbr(int nbr);
