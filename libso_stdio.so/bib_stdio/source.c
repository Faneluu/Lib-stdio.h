#include "so_stdio.h"

//#include <stdio.h>

SO_FILE *so_fopen(const char *pathname, const char *mode){

    SO_FILE *file=(SO_FILE*)malloc(sizeof(SO_FILE));

    //initialise file
    file->flags=0;
    file->permissions=0;
    file->error_flag=false;

    //take every case
    if(strcmp(mode,"r")==0){
        file->fd=open(pathname, O_RDONLY);

        if(file->fd==-1){
            file->error_flag=true;
            return NULL;
        }

        if(file->error_flag)
            file->error_flag=false;
    }

    else if(strcmp(mode,"r+")==0){
        file->fd=open(pathname, O_RDWR);

        if(file->fd==-1){
            file->error_flag=true;
            return NULL;
        }

        if(file->error_flag)
            file->error_flag=false;
    }

    else if(strcmp(mode,"w")==0){
        file->fd=open(pathname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    else if(strcmp(mode,"w+")==0){
        file->fd=open(pathname, O_RDWR | O_CREAT | O_TRUNC, 0644);
    }

    else if(strcmp(mode, "a")==0){
        file->fd=open(pathname, O_APPEND | O_CREAT, 0644);
    }

    else if(strcmp(mode, "a+")==0){
        file->fd=open(pathname, O_APPEND | O_RDONLY | O_CREAT, 0644);
    }

    return file;
}

int so_fclose(SO_FILE *stream)
{
    if(stream!=NULL){
        close(stream->fd);
        free(stream);
        return 0;
    }

    return SO_EOF;
}

int so_fileno(SO_FILE *stream)
{
    return stream->fd;
}

int so_fflush(SO_FILE *stream)
{

}

int so_fseek(SO_FILE *stream, long offset, int whence)
{
    if(lseek(stream->fd, offset, whence) == -1){
        stream->error_flag=true;
        return -1;
    }

    return 0;
}

long so_ftell(SO_FILE *stream)
{
    int temp;//=ftell(stream->fd);

    if(temp==-1){
        stream->error_flag=true;
        return -1;
    }

    return temp;
}

int so_fgetc(SO_FILE *stream)
{
    char *buffer=(char*)malloc(sizeof(char));

    int ret=read(stream->fd, buffer, sizeof(char));

    if(ret<0){
        stream->error_flag=true;
        return SO_EOF;
    }

    int temp=buffer[0];
    free(buffer);

    return temp;
}   

int so_fputc(int c, SO_FILE *stream)
{
    char ch=(char) c;
    char *buffer=(char*)malloc(sizeof(char));
    buffer[0]=ch;

    if(write(stream->fd,buffer,sizeof(char))<0){
        stream->flags=true;
        return SO_EOF;
    }

    return c;
}

int so_feof(SO_FILE *stream)
{
    ssize_t buffer_read;

    buffer_read=read(stream->fd, stream->buffer, 1);

    if(buffer_read==0)
        return -1;

    if(buffer_read==-1){
        stream->error_flag=true;
        so_ferror(stream);
    }

    return 0;
}

int so_ferror(SO_FILE *stream)
{
    if(stream->error_flag)
        return -1;

    return 0;
}


// int main()
// {
//     SO_FILE *file=so_fopen("file.txt","w");

//     // int var=so_fgetc(file);

//     // printf("vardupa getc(): %c", var);

//     so_fputc((int)'q',file);

//     so_fclose(file);

//     return 0;
// }