#include<fcntl.h>
#include<errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h> //For sprintf only

// For finding the lenth of string
off_t strlen(char *str){
    const char *temp = str;
    while (*temp)
        temp+=1;
    return temp - str;
}

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
	char str[40];
	if(pcent<8.3)
	    sprintf(str, "[Hello World!] %.2f/100.00\r", pcent);
	else if(pcent<(8.3*2))
            sprintf(str, "[!Hello World] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*3))
            sprintf(str, "[!dHello Worl] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*4))
            sprintf(str, "[!dlHello Wor] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*5))
            sprintf(str, "[!dlrHello Wo] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*6))
            sprintf(str, "[!dlroHello W] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*7))
            sprintf(str, "[!dlroWHello ] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*8))
            sprintf(str, "[!dlroW Hello] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*9))
            sprintf(str, "[!dlroW oHell] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*10))
            sprintf(str, "[!dlroW olHel] %.2f/100.00\r", pcent);
        else if(pcent<(8.3*11))
            sprintf(str, "[!dlroW ollHe] %.2f/100.00\r", pcent);
        else
            sprintf(str, "\r[!dlroW olleH] %.2f/100.00", pcent);
	write(1, str, 31);
}

int main(int argc, char *argv[])
{
    clock_t ti;
    ti = clock();

    int i=0;
    off_t size=1000000;
    char buff[size];
    char fol[]="Assignment/";
    char fsize[50];
    /**
     * Error Checking 
     *  -if the Folder Exists
     *  -if filename has been provided
     *  -if file exists
     * 
     * Warning in case multiple arguments given
     */
    
    if(argc<2){
        write(1, "Error: Filename not provided\n", 29);
        return -1;
    }else if(argc>2)
        write(1, "Warning: More than one argument provided, considering the first argument as filename\n", 84);        

    int input = open(argv[1], O_RDONLY);
    if(input==-1){
        write(1, "\nFile Not Exists\n", 17);
        return -1;
    }

    if(mkdir(fol,  S_IRWXU) && errno!=EEXIST){
        write(1, "Error while creating directory\n", 31);
        return -1;
    } else if(errno==EEXIST) {
        if( open(fol, O_DIRECTORY) && errno==ENOTDIR){
            write(1, "Error: Assignment exists and is not a directory\n", 49);
            return -1;
        }
        write(1, "Directory Already exists, continuing\n", 37);
    }
    
    // Opening Assignment/filename
    char opath[11+strlen(argv[1])];
    for(i=0;i<11;i++)
        opath[i]=fol[i];
    i=0;
    while(argv[1][i]){
        opath[11+i]=argv[1][i];
        i++;
    }
    opath[11+i]='\0';
 
    int output =  open(opath, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    off_t tsize = lseek(input, 0, SEEK_END);
    off_t j=tsize;
	sprintf(fsize, "File Size: %ld Bytes\n", tsize);
	write(1, fsize, 50);
	write(1, "\r", 1); //If file size gets larger, due to static buffer size provided above nextline charecter isn't peoperly printed
    while(1){
        if(j>=size){
            lseek(input, j-size, SEEK_SET);
            read(input, buff, size);
            revstr(buff, size);
            j-=size;
            write(output, buff, size);
        }else{
            lseek(input, 0, 0);
            read(input, buff, j);
            revstr(buff, j);
            write(output, buff, j);
            break;
        }
        load(j, tsize);
    }
    sprintf(buff, "\rReversed Successfully %.2f/100.00\n", 100.00);
    write(1, buff, 36);
    write(1, "\n[1/2] Closing Files\r", 21);
    close(input);
    write(1, "[2/2] Closing Files", 19);
    close(output);
    ti = clock() - ti;
    double time_taken = ((double)ti)/CLOCKS_PER_SEC; // calculate the elapsed time
    sprintf(buff, "\nThe program took %.2f seconds to execute\n\r", time_taken);
    write(1, buff, 44);
    return 0;
}
