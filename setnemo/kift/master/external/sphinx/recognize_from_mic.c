#include "recognize_from_mic.h"

static void	sleep_msec(int32 ms)
{
	struct timeval tmo;

	tmo.tv_sec = 0;
	tmo.tv_usec = ms * 1000;
	select(0, NULL, NULL, NULL, &tmo);
}

char		*recognize_from_mic(cmd_ln_t *config, ps_decoder_t *ps)
{
	ad_rec_t	*ad;
	uint8		utt_started;
	uint8		in_speech;
	int16		adbuf[2048];
	int32		k;
	char const	*hyp;

	utt_started = FALSE;
	ad = ad_open_sps((int)cmd_ln_float32_r(config, "-samprate"));
	if (ad_start_rec(ad) < 0)
		E_FATAL("Failed to start recording\n");
	if (ps_start_utt(ps) < 0)
		E_FATAL("Failed to start utterance\n");
	while (1)
	{
		k = ad_read(ad, adbuf, 2048);
		if (k < 0)
			E_FATAL("Failed to read audio\n");
		ps_process_raw(ps, adbuf, k, FALSE, FALSE);
		in_speech = ps_get_in_speech(ps);
		if (in_speech && !utt_started)
		{
			puts("Listening...");
			utt_started = TRUE;
		}
		sleep_msec(100);
		if (!in_speech && utt_started)
		{
			ps_end_utt(ps);
			hyp = ps_get_hyp(ps, NULL);
			if (hyp && hyp[0])
			{
				puts(hyp);
				break ;
			}
			if (ps_start_utt(ps) < 0)
				E_FATAL("Failed to start utterance\n");
			utt_started = FALSE;
		}
	}
	ad_close(ad);
	return (strdup(hyp));
}
