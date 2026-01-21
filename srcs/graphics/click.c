/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 07:17:17 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/21 04:01:48 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

void selectStick(t_game *game) {
  if (game->stickSelected == NONE_SELECTED
    || game->stickSelected == UNREACHABLE_STICK)
    return;

  for (int i = 0; i < 3; i++) {
    if (game->clickedSticks[i] == game->stickSelected) {
      playAudio(game, game->deselectSound);
      game->clickedSticks[i] = NONE_SELECTED;
      return;
    };
  };

  for (int i = 0; i < 3; i++) {
    if (game->clickedSticks[i] == NONE_SELECTED) {
      playAudio(game, game->selectSound);
      game->clickedSticks[i] = game->stickSelected;
      return;
    };
  };
};

/* ************************************************************************** */