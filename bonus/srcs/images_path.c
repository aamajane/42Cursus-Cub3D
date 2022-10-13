/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 00:03:19 by aamajane          #+#    #+#             */
/*   Updated: 2022/10/12 23:19:36 by aamajane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	images_path(t_data *data)
{
	data->walls[0].path = "./bonus/assets/wall_00.xpm";
	data->walls[1].path = "./bonus/assets/wall_01.xpm";
	data->walls[2].path = "./bonus/assets/wall_02.xpm";
	data->walls[3].path = "./bonus/assets/wall_03.xpm";
	data->walls[4].path = "./bonus/assets/wall_04.xpm";
	data->walls[5].path = "./bonus/assets/wall_05.xpm";
	data->walls[6].path = "./bonus/assets/wall_06.xpm";
	data->walls[7].path = "./bonus/assets/wall_07.xpm";
	data->walls[8].path = "./bonus/assets/wall_08.xpm";
	data->walls[9].path = "./bonus/assets/wall_09.xpm";
	data->walls[10].path = "./bonus/assets/wall_10.xpm";
	data->walls[11].path = "./bonus/assets/wall_11.xpm";
	data->walls[12].path = "./bonus/assets/wall_12.xpm";
	data->walls[13].path = "./bonus/assets/wall_13.xpm";
	data->walls[14].path = "./bonus/assets/wall_14.xpm";
	data->walls[15].path = "./bonus/assets/wall_15.xpm";
	data->walls[16].path = "./bonus/assets/wall_16.xpm";
	data->walls[17].path = "./bonus/assets/wall_17.xpm";
	data->walls[18].path = "./bonus/assets/wall_18.xpm";
	data->walls[19].path = "./bonus/assets/wall_19.xpm";
	data->walls[20].path = "./bonus/assets/wall_20.xpm";
	data->walls[21].path = "./bonus/assets/wall_21.xpm";
	data->walls[22].path = "./bonus/assets/wall_22.xpm";
	data->walls[23].path = "./bonus/assets/wall_23.xpm";
	images_path_extra_1(data);
}

void	images_path_extra_1(t_data *data)
{
	data->walls[24].path = "./bonus/assets/wall_24.xpm";
	data->walls[25].path = "./bonus/assets/wall_25.xpm";
	data->walls[26].path = "./bonus/assets/wall_26.xpm";
	data->walls[27].path = "./bonus/assets/wall_27.xpm";
	data->walls[28].path = "./bonus/assets/wall_28.xpm";
	data->walls[29].path = "./bonus/assets/wall_29.xpm";
	data->walls[30].path = "./bonus/assets/wall_30.xpm";
	data->walls[31].path = "./bonus/assets/wall_31.xpm";
	data->lights[0].imgs[0].path = "./bonus/assets/light_0_0.xpm";
	data->lights[0].imgs[1].path = "./bonus/assets/light_0_1.xpm";
	data->lights[1].imgs[0].path = "./bonus/assets/light_1_0.xpm";
	data->lights[1].imgs[1].path = "./bonus/assets/light_1_1.xpm";
	data->lights[2].imgs[0].path = "./bonus/assets/light_2_0.xpm";
	data->lights[2].imgs[1].path = "./bonus/assets/light_2_1.xpm";
	data->lights[3].imgs[0].path = "./bonus/assets/light_3_0.xpm";
	data->lights[3].imgs[1].path = "./bonus/assets/light_3_1.xpm";
	data->letters[letter_n].path = "./bonus/assets/letter_n.xpm";
	data->letters[letter_s].path = "./bonus/assets/letter_s.xpm";
	data->letters[letter_e].path = "./bonus/assets/letter_e.xpm";
	data->letters[letter_w].path = "./bonus/assets/letter_w.xpm";
	data->sprite.img.path = "./bonus/assets/sprite.xpm";
	data->door.img.path = "./bonus/assets/door.xpm";
	images_path_extra_2(data);
}

void	images_path_extra_2(t_data *data)
{	
	data->door.op_imgs[0].path = "./bonus/assets/door_opening_0.xpm";
	data->door.op_imgs[1].path = "./bonus/assets/door_opening_1.xpm";
	data->door.op_imgs[2].path = "./bonus/assets/door_opening_2.xpm";
	data->door.op_imgs[3].path = "./bonus/assets/door_opening_3.xpm";
	data->door.op_imgs[4].path = "./bonus/assets/door_opening_4.xpm";
	data->door.op_imgs[5].path = "./bonus/assets/door_opening_5.xpm";
	data->door.op_imgs[6].path = "./bonus/assets/door_opening_6.xpm";
	data->weapon.holding.path = "./bonus/assets/weapon_holding.xpm";
	data->weapon.reloading[0].path = "./bonus/assets/weapon_reloading_00.xpm";
	data->weapon.reloading[1].path = "./bonus/assets/weapon_reloading_01.xpm";
	data->weapon.reloading[2].path = "./bonus/assets/weapon_reloading_02.xpm";
	data->weapon.reloading[3].path = "./bonus/assets/weapon_reloading_03.xpm";
	data->weapon.reloading[4].path = "./bonus/assets/weapon_reloading_04.xpm";
	data->weapon.reloading[5].path = "./bonus/assets/weapon_reloading_05.xpm";
	data->weapon.reloading[6].path = "./bonus/assets/weapon_reloading_06.xpm";
	data->weapon.reloading[7].path = "./bonus/assets/weapon_reloading_07.xpm";
	data->weapon.reloading[8].path = "./bonus/assets/weapon_reloading_08.xpm";
	data->weapon.reloading[9].path = "./bonus/assets/weapon_reloading_09.xpm";
	data->weapon.reloading[10].path = "./bonus/assets/weapon_reloading_10.xpm";
	data->weapon.reloading[11].path = "./bonus/assets/weapon_reloading_11.xpm";
	data->weapon.reloading[12].path = "./bonus/assets/weapon_reloading_12.xpm";
	data->weapon.reloading[13].path = "./bonus/assets/weapon_reloading_13.xpm";
	data->weapon.reloading[14].path = "./bonus/assets/weapon_reloading_14.xpm";
	data->weapon.reloading[15].path = "./bonus/assets/weapon_reloading_15.xpm";
	images_path_extra_3(data);
}

void	images_path_extra_3(t_data *data)
{
	data->weapon.shooting[0].path = "./bonus/assets/weapon_shooting_0.xpm";
	data->weapon.shooting[1].path = "./bonus/assets/weapon_shooting_1.xpm";
	data->weapon.shooting[2].path = "./bonus/assets/weapon_shooting_2.xpm";
	data->weapon.shooting[3].path = "./bonus/assets/weapon_shooting_3.xpm";
	data->weapon.shooting[4].path = "./bonus/assets/weapon_shooting_4.xpm";
	data->weapon.shooting[5].path = "./bonus/assets/weapon_shooting_5.xpm";
	data->weapon.shooting[6].path = "./bonus/assets/weapon_shooting_6.xpm";
	data->weapon.shooting[7].path = "./bonus/assets/weapon_shooting_7.xpm";
	data->weapon.shooting[8].path = "./bonus/assets/weapon_shooting_8.xpm";
}
