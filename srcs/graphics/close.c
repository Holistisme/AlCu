/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 06:21:54 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 06:39:04 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* ************************************************************************** */

// ! Please note: this function is not intended to be called before the render loop has started */
void stopRender(t_game *game) {
  UnloadTexture(game->stickTexture);
  UnloadTexture(game->backgroundTexture);
  UnloadModel(game->stickModel);
  UnloadModel(game->selectedStickModel);
  CloseWindow();
};

/* ************************************************************************** */