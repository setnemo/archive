#include "pocketsphinx.h"

static void	recognize_from_mic(cmd_ln_t *config, ps_decoder_t *ps)
{
	ad_rec_t	*ad;
	uint8		utt_started;
	uint8		in_speech;
	int16		adbuf[2048];
	int32		k;

	utt_started = FALSE;
	ad = ad_open_dev(cmd_ln_str_r(config, "-adcdev"), (int)cmd_ln_float32_r(config, "-samprate"));
	while()
	{
		k = ad_read(ad, adbuf, 2048);
		ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
	}
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
