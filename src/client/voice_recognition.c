#include <unistd.h>
#include <stdio.h>
#include <sphinxbase/ad.h>
#include <sphinxbase/err.h>
#include "pocketsphinx.h"

static void	recognize_from_mic(cmd_ln_t *config, ps_decoder_t *ps)
{
	ad_rec_t	*ad;
	uint8		utt_started;
	uint8		in_speech;
	int16		adbuf[2048];
	int32		k;
	char const	*hyp;

	utt_started = FALSE;
	ad = ad_open_dev("sysdefault", (int)cmd_ln_float32_r(config, "-samprate"));
	ad_start_rec(ad);
	ps_start_utt(ps);
	for(;;)
	{
		k = ad_read(ad, adbuf, 2048);
		ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
		if (in_speech && !utt_started)
		{
			printf("Listen...\n");
			utt_started = TRUE;
		}
		if (!in_speech && utt_started)
		{
			ps_end_utt(ps);
			hyp = ps_get_hyp(ps, NULL);
			if (hyp)
				printf("%s\n", hyp);
			ps_start_utt(ps);
			utt_started = FALSE;
			printf("Ready\n");
		}
		sleep(1);
	}
	ad_close(ad);
}

int		main(int argc, char **argv)
{
	ps_decoder_t	*ps;
	cmd_ln_t		*config;

	config = cmd_ln_init(NULL, ps_args(), TRUE,		// Load the configuration structure - ps_args() passes the default values
	"-hmm", MODELDIR "/en-us/en-us",				// path to the standard english language model
	"-lm", MODELDIR "/en-us/en-us.lm.bin",			// custom language model (file must be present)
	"-dict", MODELDIR "/en-us/cmudict-en-us.dict",	// custom dictionary (file must be present)
	//"-logfn", "/dev/null",							// suppress log info from being sent to screen
	NULL);
	if (config == NULL)
	{
		fprintf(stderr, "Failed to create config object\n");
		return (-1);
	}
	ps = ps_init(config);
	if (ps == NULL)
	{
		fprintf(stderr, "Failed to create recognizer\n");
		return (-1);
	}
	recognize_from_mic(config, ps);
	ps_free(ps);
	cmd_ln_free_r(config);
	return (0);
}
