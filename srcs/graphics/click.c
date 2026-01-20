/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 07:17:17 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 09:56:29 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

void selectStick(t_game *game) {
  for (int i = 0; i < 3; i++) {
    if (game->clickedSticks[i] == NONE_SELECTED
      && (game->stickSelected != NONE_SELECTED
        && game->stickSelected != UNREACHABLE_STICK))
    {
      game->clickedSticks[i] = game->stickSelected;
      break;
    };
  };
};

/* ************************************************************************** */