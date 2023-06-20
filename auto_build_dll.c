#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <Windows.h>
#include "HotDylibEx.h"

int main(int argc, const char* argv[])
{
	printf("Auto build DLL v1.0\n");
	printf("-------------------\n");

	int useGMake = 0;
	if (argc > 1 && strcmp(argv[1], "make") == 0)
	{
		printf("Select gmake alternative to build_dll.bat\n");
		useGMake = 1;
	}

	HotDylibFileTime files[] = {
		{ 0, "lib.c" },
		{ 0, "ui.h" },
		{ 0, "ui.c" },
	};
	const int32_t fileCount = sizeof(files) / sizeof(files[0]);
 	HotDylibWatchFiles(files, fileCount); // Initialize

	while (1)
	{
		if (HotDylibWatchFiles(files, fileCount))
		{	
			printf("Files changed, recompile dll...\n");
			if (useGMake)
			{
				system("make dll");
			}
			else
			{
				system("build_dll.bat");
			}

			// Ignore further changed
			HotDylibWatchFiles(files, fileCount); 
		}

		Sleep(16);
	}

	return 0;
}
