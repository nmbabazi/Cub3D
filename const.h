/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 17:42:00 by nmbabazi          #+#    #+#             */
/*   Updated: 2020/06/11 16:50:51 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CONST_H
# define CONST_H

#define TILE_S 50
#define MAP_ROWS 13
#define MAP_COLS 20
#define WIN_WIDTH (MAP_COLS * TILE_S)
#define WIN_HEIGHT (MAP_ROWS * TILE_S)
#define FOV 60 * (M_PI / 180)
#define COLS_S 100
#define NUM_RAYS (WIN_WIDTH / COLS_S)

#endif
