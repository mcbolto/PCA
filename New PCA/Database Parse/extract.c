
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argv, char **argc)
{
	DIR 			*db, *dsub;
	struct dirent 	*dirb, *dirsub;
	char 			*basedir = "database/";
	char 			*destdir = "result/";
	char 			*testdir = "test/";
	char			subdir[100], fileold[100], filenew[100];
	char			cpycommand[250];
	int				count;
	
	db = opendir(basedir);
	if(db != NULL)
	{
		while((dirb = readdir(db)) != NULL)
		{
			//printf("%s\n", dir->d_name);
			strcpy(subdir, basedir);
			strcat(subdir, dirb->d_name);
			dsub = opendir(subdir);
			if(dsub != NULL)
			{
				count = 0;
				while((dirsub = readdir(dsub)) != NULL)
				{
					if(strlen(dirsub->d_name) >= 12)
					{
						//printf("%s\n", &(dirsub->d_name[strlen(dirsub->d_name)-10]));
						if(strcmp(&(dirsub->d_name[strlen(dirsub->d_name)-10]), "fa.ppm.bz2")   == 0 ||
						   strcmp(&(dirsub->d_name[strlen(dirsub->d_name)-10]), "fb.ppm.bz2")   == 0 ||
						   strcmp(&(dirsub->d_name[strlen(dirsub->d_name)-12]), "fa_a.ppm.bz2") == 0 ||
						   strcmp(&(dirsub->d_name[strlen(dirsub->d_name)-12]), "fb_a.ppm.bz2") == 0 )
						{
							strcpy(fileold, subdir);
							strcat(fileold, "/");
							strcat(fileold, dirsub->d_name);
							if(count++ == 0)
								strcpy(filenew, testdir);
							else
								strcpy(filenew, destdir);
							strcat(filenew, dirsub->d_name);
							strcpy(cpycommand, "cp ./");
							strcat(cpycommand, fileold);
							strcat(cpycommand, " ./");
							strcat(cpycommand, filenew);
							system(cpycommand);
						}
					}
				}
				if(count == 1)
					printf("File %s has no matches.\n", dirsub->d_name);
				closedir(dsub);
			}
			else
			{
				printf("Couldn't open subdirectory.");
				break;
			}
		}
		closedir(db);
	}
	else
		printf("Couldn't open database directory.");
	
	return 0;
}