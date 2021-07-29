/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_callbacks.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 21:26:40 by vrybalko          #+#    #+#             */
/*   Updated: 2018/09/04 21:26:45 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_CALLBACKS_H
# define COMMAND_CALLBACKS_H

char		*hello_test_callback(void *arg);
char		*sound_callback(void *arg);
char		*screen_lock_callback(void *arg);
char		*run_program(void *arg);
char		*screen_shot_callback(void *arg);
char		*show_screen_shots_callback(void *arg);
char		*weather_callback(void *arg);
char		*backlight_callback(void *arg);
char		*play_music_callback(void *arg);
char		*history_callback(void *arg);

#endif
