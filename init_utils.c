/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:17:41 by syakovle          #+#    #+#             */
/*   Updated: 2023/11/07 18:18:06 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	getstartangle(int view)
{
	if (view == 3)
		return (0.0f);
	if (view == 2)
		return (P2);
	if (view == 4)
		return (PI);
	if (view == 1)
		return (P3);
	else
		return (0.0f);
}