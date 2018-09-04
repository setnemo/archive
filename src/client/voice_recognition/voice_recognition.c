/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voice_recognition.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmulish <dmulish@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 19:04:02 by dmulish           #+#    #+#             */
/*   Updated: 2018/09/04 20:19:35 by dmulish          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "external/recognize_from_mic.h"

/*
** config param for model
** "-mllr", DICTDIR "mllr_matrix"
*/

char		*get_user_speech(void)
{
	char			*result;
	ps_decoder_t	*ps;
	cmd_ln_t		*config;

	config = cmd_ln_init(NULL, ps_args(), TRUE,
			"-hmm", DICTDIR "en-us-adapt",
			"-lm", MODELDIR "/en-us/en-us.lm.bin",
			"-dict", DICTDIR "dict2.dic",
			"-logfn", "/dev/null", NULL);
	if (config == NULL)
	{
		fprintf(stderr, "Failed to create config object\n");
		return (NULL);
	}
	ps = ps_init(config);
	if (ps == NULL)
	{
		fprintf(stderr, "Failed to create recognizer\n");
		return (NULL);
	}
	result = recognize_from_mic(config, ps);
	ps_free(ps);
	cmd_ln_free_r(config);
	return (result);
}
