#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("USAGE: ./recover [card.raw]");
		return 1;
	}

	FILE* file = fopen(argv[1], "r");
	if (file == NULL)
	{
		return 1;
	}

	BYTE buffer[512];
	int  i = 0;
	while (fread(buffer, sizeof(BYTE), 512, file))
	{
		char filename[8];
		sprintf(filename, "%03i.jpg",i);

		FILE* new = NULL;

		// If start of a new jpg
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
		{	
			if (i != 0)
				fclose(new);
			new = fopen(filename,"w");
			if (new == NULL)
				return 1;

			i++;
		}

		// continue writing
		fwrite(buffer, sizeof(BYTE), 512, new);
	}

	fclose(file);
}
