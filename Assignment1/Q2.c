#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h> //For sprintf only
#include <string.h> //For strcmp

void revstr(char *str, off_t size){
    char *startp=str;
    char *endp=str+size-1;
    while(startp<endp){
        char temp=*startp;
        *startp++=*endp;
        *endp--=temp;
    }
}

void load(float cur, float tot){
	fflush(stdout);
	float pcent = ((tot-cur)/tot)*100;
	char str[22];
        sprintf(str, "Checking %.2f/100.00\r", pcent);
       	write(1, str, 22);
}

int main(int argc, char *argv[])
{
    clock_t ti;
    ti = clock();
    int i=0, is_rev=1;
    off_t size=1000000;
    char obuff[size];
    char nbuff[size];

    char fsize[50];
    int flag[3] = {1, 1, 1};
    struct stat sb;
    /**
     * Error Checking
     *  -if the Folder Exists
     *  -if filename has been provided
     *  -if file exists
     *
     * Warning in case multiple arguments given
     */

    if(argc<2){
        write(1, "Error: Arguments not provided\n", 30);
        return -1;
    }else if(argc<4){
	write(1, "Error: Expected three Arguments\n", 32);
	return -1;
    }else if(argc>4)
        write(1, "Warning: More than three arguments provided, considering the first three arguments as: oldfilename newfilename directory\n", 121);
    int olfile = open(argv[1], O_RDONLY);
    if(olfile==-1){
        write(1, "Old File does Not Exists\n", 25);
	flag[0]=0;
    }
    int nefile = open(argv[2], O_RDONLY);
    if(nefile==-1){
        write(1, "New File does Not Exists\n", 25);
        flag[1]=0;
    }
    stat(argv[3], &sb);
    if(!(S_ISDIR(sb.st_mode))){
        write(1, "Warning: Issue with directory will be ignored\n", 46);
        flag[2]=0;
    }
    if( !flag[0] && !flag[1] && !flag[2] ){
	write(1, "Error: Invalid Arguments, Please check again\n", 45);
	return -1;
    }

    off_t oldtsize = lseek(olfile, 0, SEEK_END);
    off_t newtsize = lseek(nefile, 0, SEEK_END);
    if(oldtsize != newtsize)
	is_rev=0;
    off_t j=oldtsize;
    if(is_rev){
        while(is_rev){
            if(j>=size){
                lseek(olfile, j-size, SEEK_SET);
		lseek(nefile, i*size, SEEK_SET);
                read(olfile, obuff, size);
		read(nefile, nbuff, size);
                revstr(obuff, size);
		if(!strcmp(obuff, nbuff))
			is_rev=0;
                j-=size;
		i+=1;
            }else{
                lseek(olfile, 0, 0);
		lseek(nefile, oldtsize-size, SEEK_SET);
                read(olfile, obuff, j);
		read(nefile, nbuff, j);
                revstr(obuff, j);
                if(!strcmp(obuff, nbuff))
                        is_rev=0;
                break;
            }
	    load(j, oldtsize);
        }
    }
    if(is_rev) sprintf(obuff, "\rReversed File matches %.2f/100.00\n\r", 100.00);
    write(1, obuff, 37);
    if(flag[2])
        write(1, "\nDirectory is created: Yes\n", 28);
    else
        write(1, "\nDirectory is created: No\n", 26);
    sprintf(obuff, "Whether file contents are reversed in newfile: %s\n\r\n", is_rev?"Yes\0":"No \0");
    write(1, obuff, 54);
    char filedir[3][9]={"oldfile", "newfile", "directory"};

    // Printing Permissions for Old and New File
    for(i=0;i<=1;i++){
        if(!flag[i]) continue;
        stat(argv[i+1], &sb);
        sprintf(obuff, "User has read permissions on %s: %s\n\r", filedir[i], (sb.st_mode & S_IRUSR)?"Yes":"No ");
        write(1, obuff, 42);
        sprintf(obuff, "User has write permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IWUSR)?"Yes":"No ");
        write(1, obuff, 43);
        sprintf(obuff, "User has execute permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IXUSR)?"Yes":"No ");
        write(1, obuff, 44);
        sprintf(obuff, "Group has read permissions on %s: %s\n\r", filedir[i], (sb.st_mode & S_IRGRP)?"Yes":"No ");
        write(1, obuff, 43);
        sprintf(obuff, "Group has write permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IWGRP)?"Yes":"No ");
        write(1, obuff, 44);
        sprintf(obuff, "Group has execute permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IXGRP)?"Yes":"No ");
        write(1, obuff, 45);
        sprintf(obuff, "Others has read permissions on %s: %s\n\r", filedir[i], (sb.st_mode & S_IROTH)?"Yes":"No ");
        write(1, obuff, 44);
        sprintf(obuff, "Others has write permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IWOTH)?"Yes":"No ");
        write(1, obuff, 45);
        sprintf(obuff, "Others has execute permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IXOTH)?"Yes":"No ");
        write(1, obuff, 46);
        write(1, "\n", 1);
    }
    if(flag[i]){
        //Printing Permission for Directory
        stat(argv[i+1], &sb);
        sprintf(obuff, "User has read permissions on %s: %s\n\r", filedir[i], (sb.st_mode & S_IRUSR)?"Yes":"No ");
        write(1, obuff, 44);
        sprintf(obuff, "User has write permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IWUSR)?"Yes":"No ");
        write(1, obuff, 45);
        sprintf(obuff, "User has execute permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IXUSR)?"Yes":"No ");
        write(1, obuff, 46);
        sprintf(obuff, "Group has read permissions on %s: %s\n\r", filedir[i], (sb.st_mode & S_IRGRP)?"Yes":"No ");
        write(1, obuff, 45);
        sprintf(obuff, "Group has write permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IWGRP)?"Yes":"No ");
        write(1, obuff, 46);
        sprintf(obuff, "Group has execute permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IXGRP)?"Yes":"No ");
        write(1, obuff, 47);
        sprintf(obuff, "Others has read permissions on %s: %s\n\r", filedir[i], (sb.st_mode & S_IROTH)?"Yes":"No ");
        write(1, obuff, 46);
        sprintf(obuff, "Others has write permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IWOTH)?"Yes":"No ");
        write(1, obuff, 47);
        sprintf(obuff, "Others has execute permission on %s: %s\n\r", filedir[i], (sb.st_mode & S_IXOTH)?"Yes":"No ");
        write(1, obuff, 48);
        write(1, "\n", 1);
    }
    write(1, "\n[1/2] Closing Files\r", 21);
    close(olfile);
    write(1, "[2/2] Closing Files", 19);
    close(nefile);
    ti = clock() - ti;
    double time_taken = ((double)ti)/CLOCKS_PER_SEC; // calculate the elapsed time
    sprintf(obuff, "\nThe program took %.2f seconds to execute\n\r", time_taken);
    write(1, obuff, 44);
    return 0;
}
