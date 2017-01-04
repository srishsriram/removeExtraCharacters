#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int main (int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("Usage: removeNumbers <directory>");
		return 0;
	}	

	DIR *dp;
	struct dirent *ep;
	dp = opendir(argv[1]);

	if (dp != NULL)
	{
		while (ep = readdir(dp))
		{
			char *currentFile = ep->d_name;
			
			if (currentFile[0] >= 32 && currentFile[0] <= 64 && strcmp(currentFile,".") != 0 && strcmp(currentFile, "..") != 0) 
			{
				char newFile[strlen(currentFile)];

				int i=0;
				int j=0;
				
				for (; i<strlen(currentFile) && (currentFile[i] < 65 || currentFile[i] > 122); i++) {}			
				for (; i<strlen(currentFile); i++) {
					newFile[j++] = currentFile[i];				
				}

				newFile[j] = '\0';

				char newFileWithPath[1024] = "";
				strcat(newFileWithPath, argv[1]);
				strcat(newFileWithPath, "/");
				strcat(newFileWithPath, newFile);


				char currentFileWithPath[1024] = "";
				strcat(currentFileWithPath, argv[1]);
				strcat(currentFileWithPath, "/");
				strcat(currentFileWithPath, currentFile);

				rename(currentFileWithPath, newFileWithPath);
			}
		}

		(void) closedir(dp);	
	} else {
		perror("Couldn't open the directory");
	}

	return 0;
}
