#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
	FILE* file = fopen("card.raw", "r");
	if (file == NULL)
		return 1;

	BYTE buffer[512];
	int  i = 0;
	FILE* newF;
	while (fread(buffer, sizeof(BYTE), 512, file))
	{
		char filename[8];
		sprintf(filename, "%03i.jpg",i);

		// If start of a new jpg
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
		{	
			if (i != 0)
				fclose(newF);
			newF = fopen(filename,"w");
			if (newF == NULL)
				return 1;

			i++;
		}

		// continue writing
		if (newF != NULL)
			fwrite(buffer, sizeof(BYTE), 512, newF);
	}

	fclose(file);
}
