/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 23:49:24 by aheitz            #+#    #+#             */
/*   Updated: 2026/01/20 00:00:27 by aheitz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../raylib/src/raylib.h"

/* ************************************************************************** */

int openGraphicsWindow() {
  InitWindow(1000, 1000, "AlCu.exe");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, World!", 200, 200, 20, LIGHTGRAY);
    EndDrawing();
  };

  CloseWindow();
  return 0;
};