// #include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define USAGE "Usage: %s [-vg]\n"
#define VERSION 1.0

enum str_mode
{
	ASCII    = 0,
	ALPHA    = 1,
	NUM      = 2
};

static enum str_mode mode = ASCII;

static int min = 0,
	   max = 0;

void determine_range()
{
	switch(mode)
	{
		case ASCII:
			min = 0x20;
			max = 0x7e;
			
			break;

		case ALPHA:
			min = 0x40;
			max = 0x7a;

			break;

		case NUM:
			min = 0x30;
			max = 0x39;

			break;
	}
}

static struct option long_options[] =
{
	{"help", no_argument, 0, 255},
	{"version", no_argument, 0, 'v'},
	{"generate", required_argument, 0, 'g'},
	{"ascii", no_argument, 0, 254},
	{"alpha", no_argument, 0, 253},
	{"num", no_argument, 0, 252}
};

int main(int argc, char **argv)
{
	srand(time(NULL));

	int opt = 0;

	if(argc < 2)
	{
		fprintf(stderr, USAGE, argv[0]);

		return 1;
	}

	while((opt = getopt_long(argc, argv, "vg:", long_options, 0)) != -1)
	{
		switch(opt)
		{
			case 'v':
				printf("%s-%.1f\n", argv[0], VERSION);

				return 0;

				break;

			case 'g':
				determine_range();

				int c = strtol(optarg, 0, 10);

				if(c <= 0)
				{
					fprintf(stderr, "%s: cannot generate a random string with a length of %d\n", argv[0], c);

					return 1;
				}

				for(int i = 0; i < c; i++)
				{
					fputc(rand() % (max - min + 1) + min, stdout);
				}

				fputc('\n', stdout);

				break;

			case 255:
				printf("Usage: %s [OPTION...]\nGenerate random strings\n\n      --help     display this help and exit\n  -v, --version  output version information and exit\n\n      --ascii    generate random strings with all printable ascii characters\n      --alpha    generate random strings with just alphabet characters\n      --num      generate random strings with just numbers\n  -g, --generate Generate a random string\n\nReport bugs to https://github.com/garan3160/rands/issues\n", argv[0]);

				return 0;

				break;

			case 254:
				mode = ASCII;

				break;

			case 253:
				mode = ALPHA;

				break;

			case 252:
				mode = NUM;

				break;

			default:
				fprintf(stderr, USAGE, argv[0]);

				return 1;

				break;
		}
	}

	return 0;
}

