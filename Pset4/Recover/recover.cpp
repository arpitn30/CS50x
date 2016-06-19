#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>

typedef uint8_t  BYTE;

int main(int argc, char* argv[])

{

	FILE* file = fopen("card.raw", "r");

	if (file == NULL)

	{

		printf("Could not open card.raw.\n");

		return 1;
	}

	int cntr = 0;
	char fname[8];

	FILE* outptr;

	BYTE buff[512];

	fread(buff, sizeof(buff), 1, file);

	printf("yoyo1");

	while(!feof(file))

	{
	printf("yoyo4");

		if((buff[0] == 0xff) && (buff[1] == 0xd8) && (buff[2] == 0xff) && (buff[3] == 0xe0 || buff[3] == 0xe1))

		{

	printf("yoyo2");

			if(cntr > 0)

				fclose(outptr);
			(cntr < 10)?sprintf(fname, "00%d.jpg",cntr):(cntr < 100)?sprintf(fname, "0%d.jpg",cntr):sprintf(fname, "%d.jpg",cntr);
			outptr = fopen(fname, "a");
			cntr++;

		}
		if(cntr > 0)

		{
	printf("yoyo3");
			fwrite(buff, sizeof(buff), 1, outptr);

		}
		fread(buff, sizeof(buff), 1, file);
	}

	fclose(outptr);

	fclose(file);
	return 0;

}
