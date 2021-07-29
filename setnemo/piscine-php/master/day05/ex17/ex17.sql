SELECT count(*) 'nb_susc', FLOOR(AVG(price)) 'av_susc', (SUM(duration_sub) % 42) 'ft' FROM subscription;
