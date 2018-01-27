#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static const char b64_table[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
  'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
  'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
  'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
  'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
  'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
  'w', 'x', 'y', 'z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', '+', '/'
};

int			ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *ss1;
	unsigned char *ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	while (*ss1 && *ss1 == *ss2)
	{
		ss1++;
		ss2++;
	}
	return (*ss1 - *ss2);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}


void		ft_putstr(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while (i[str] != '\0')
		{
			ft_putchar(i[str]);
			++i;
		}
	}
}


char *b64_encode (const unsigned char *src, size_t len) {
	int i = 0;
	int j = 0;
	char *enc = NULL;
	size_t size = 0;
	unsigned char buf[4];
	unsigned char tmp[3];

	// alloc
	enc = (char *) malloc(1);
	if (NULL == enc) { return NULL; }

	// parse until end of source
	while (len--) {
		// read up to 3 bytes at a time into `tmp'
		tmp[i++] = *(src++);

		// if 3 bytes read then encode into `buf'
		if (3 == i) {
			buf[0] = (tmp[0] & 0xfc) >> 2;
			buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
			buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
			buf[3] = tmp[2] & 0x3f;

			// allocate 4 new byts for `enc` and
			// then translate each encoded buffer
			// part by index from the base 64 index table
			// into `enc' unsigned char array
			enc = (char *) realloc(enc, size + 4);
			for (i = 0; i < 4; ++i) {
				enc[size++] = b64_table[buf[i]];
			}

			// reset index
			i = 0;
		}
	}

	// remainder
	if (i > 0) {
		// fill `tmp' with `\0' at most 3 times
		for (j = i; j < 3; ++j) {
			tmp[j] = '\0';
		}

		// perform same codec as above
		buf[0] = (tmp[0] & 0xfc) >> 2;
		buf[1] = ((tmp[0] & 0x03) << 4) + ((tmp[1] & 0xf0) >> 4);
		buf[2] = ((tmp[1] & 0x0f) << 2) + ((tmp[2] & 0xc0) >> 6);
		buf[3] = tmp[2] & 0x3f;

		// perform same write to `enc` with new allocation
		for (j = 0; (j < i + 1); ++j) {
			enc = (char *) realloc(enc, size + 1);
			enc[size++] = b64_table[buf[j]];
		}

		// while there is still a remainder
		// append `=' to `enc'
		while ((i++ < 3)) {
			enc = (char *) realloc(enc, size + 1);
			enc[size++] = '=';
		}
	}

	// Make sure we have enough space to add '\0' character at end.
	enc = (char *) realloc(enc, size + 1);
	enc[size] = '\0';

	return enc;
}


unsigned char *b64_decode_ex (const char *src, size_t len, size_t *decsize) {
	int i = 0;
	int j = 0;
	int l = 0;
	size_t size = 0;
	unsigned char *dec = NULL;
	unsigned char buf[3];
	unsigned char tmp[4];

	// alloc
	dec = (unsigned char *) malloc(1);
	if (NULL == dec) { return NULL; }

	// parse until end of source
	while (len--) {
		// break if char is `=' or not base64 char
		if ('=' == src[j]) { break; }
		if (!(isalnum(src[j]) || '+' == src[j] || '/' == src[j])) { break; }

		// read up to 4 bytes at a time into `tmp'
		tmp[i++] = src[j++];

		// if 4 bytes read then decode into `buf'
		if (4 == i) {
			// translate values in `tmp' from table
			for (i = 0; i < 4; ++i) {
				// find translation char in `b64_table'
				for (l = 0; l < 64; ++l) {
					if (tmp[i] == b64_table[l]) {
						tmp[i] = l;
						break;
					}
				}
			}

			// decode
			buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
			buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
			buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

			// write decoded buffer to `dec'
			dec = (unsigned char *) realloc(dec, size + 3);
			if (dec != NULL){
				for (i = 0; i < 3; ++i) {
					dec[size++] = buf[i];
				}
			} else {
				return NULL;
			}

			// reset
			i = 0;
		}
	}

	// remainder
	if (i > 0) {
		// fill `tmp' with `\0' at most 4 times
		for (j = i; j < 4; ++j) {
			tmp[j] = '\0';
		}

		// translate remainder
		for (j = 0; j < 4; ++j) {
				// find translation char in `b64_table'
				for (l = 0; l < 64; ++l) {
					if (tmp[j] == b64_table[l]) {
						tmp[j] = l;
						break;
					}
				}
		}

		// decode remainder
		buf[0] = (tmp[0] << 2) + ((tmp[1] & 0x30) >> 4);
		buf[1] = ((tmp[1] & 0xf) << 4) + ((tmp[2] & 0x3c) >> 2);
		buf[2] = ((tmp[2] & 0x3) << 6) + tmp[3];

		// write remainer decoded buffer to `dec'
		dec = (unsigned char *) realloc(dec, size + (i - 1));
		if (dec != NULL){
			for (j = 0; (j < i - 1); ++j) {
				dec[size++] = buf[j];
			}
		} else {
			return NULL;
		}
	}

	// Make sure we have enough space to add '\0' character at end.
	dec = (unsigned char *) realloc(dec, size + 1);
	if (dec != NULL){
		dec[size] = '\0';
	} else {
		return NULL;
	}

	// Return back the size of decoded string if demanded.
	if (decsize != NULL) {
		*decsize = size;
	}

	return dec;
}

unsigned char *b64_decode (const char *src, size_t len) {
	return (b64_decode_ex(src, len, NULL));
}

void		start_base64(int argc, char **argv)
{
	ft_putstr("start base64\n");
	unsigned char *str = "brian the monkey and bradley the kinkajou are friends";
	char *enc = b64_encode(str, strlen(str));

	printf("%s\n", enc); // YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=
	if (ft_strcmp(enc, "YnJpYW4gdGhlIG1vbmtleSBhbmQgYnJhZGxleSB0aGUga2lua2Fqb3UgYXJlIGZyaWVuZHM=") == 0)
		ft_putstr("OK\n");
	char *dec = b64_decode(enc, strlen(enc));

	printf("%s\n", dec); // brian the monkey and bradley the kinkajou are friends
	if (ft_strcmp(dec, "brian the monkey and bradley the kinkajou are friends") == 0)
		ft_putstr("OK\n");
	free(enc);
	free(dec);
}

void		start_des_ecb(int argc, char **argv)
{
	ft_putstr("start des-ecb\n");
}

void		start_des_cbc(int argc, char **argv)
{
	ft_putstr("start des-cbc\n");
}

int			main(int argc, char **argv)
{

	if (argc > 1)
	{
		if (ft_strcmp(argv[1], "base64") == 0)
			start_base64(argc, argv);
		else if ((ft_strcmp(argv[1], "des") == 0) || (ft_strcmp(argv[1], "des-ecb") == 0))
			start_des_ecb(argc, argv);
		else if (ft_strcmp(argv[1], "des-cbc") == 0)
			start_des_cbc(argc, argv);
		else 
		{
			ft_putstr("ft_ssl: Error: ");
			ft_putstr(argv[1]);
			ft_putstr(" is an invalid command.\n\nStandard commands:\n\nMessage Digest commands:\n\nCipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\ndes3\ndes3-ecb\ndes3-cbc\n");
		}
	}
	else
		ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
	return (0);
}
