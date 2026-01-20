/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benpicar <benpicar@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 07:17:17 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 13:32:15 by benpicar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

// void selectStick(t_game *game) {
//   for (int i = 0; i < 3; i++) {
//     if (game->clickedSticks[i] == NONE_SELECTED
//       && (game->stickSelected != NONE_SELECTED
//         && game->stickSelected != UNREACHABLE_STICK))
//     {
//       game->clickedSticks[i] = game->stickSelected;
//       break;
//     };
//   };
// };

/* ************************************************************************** */

void selectStick(t_game *game) {
  if (game->stickSelected == NONE_SELECTED 
    || game->stickSelected == UNREACHABLE_STICK)
    return;

  for (int i = 0; i < 3; i++) {
    if (game->clickedSticks[i] == game->stickSelected) {
      game->clickedSticks[i] = NONE_SELECTED;
      return;
    }
  }

  for (int i = 0; i < 3; i++) {
    if (game->clickedSticks[i] == NONE_SELECTED) {
      game->clickedSticks[i] = game->stickSelected;
      break;
    }
  }
};

/* ************************************************************************** */