 #include "headers/runner.h"


int runPiped(char* input, char* cmd, char* output) {
    int fIn,fOut;
    fIn = open(input,O_RDONLY, 0666);
    fOut=open (output, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup2(fIn,0);
    close(fIn);
    dup2(fOut,1);
    close(fOut);
    printf("%s",cmd) ;
    execlp(cmd,cmd,NULL);
    return 1;
}

int runSingle(char* cmd, char* filename) {
    int fd;

    fd=open (filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
    dup2(fd,1); 
	close(fd);

    execlp(cmd,cmd,NULL);
    return 1;
}

bool runCommand(char* line,int cmdNumber){
    char cmd[3];
    char cmdPipe[3];
    char* token;
    int status,ret = 0, n = 1,sum=3;
    sprintf(cmd,"%d",cmdNumber);
    printf("%s",line+2);
    if(!fork()){
        if(startsWith("$|",line)) {
                
                if(line[2]!=' '){
                        token=strtok(line+2,"");
                        write(1,token,23);
                        n = getNumber(line+2);
                        if(n>9) sum = 5;
                    else sum = 4; 
                }
                sprintf(cmdPipe, "%d", cmdNumber-n);
                
                ret = runPiped(cmdPipe,line+sum,cmd);
        }
        else ret = runSingle(line+2,cmd);
        _exit(ret);
    }
    else {
        wait(&status);
        if (WIFEXITED(status)) 
                ret=WEXITSTATUS(status);
    }
    return ret == 1 ? false : true;
}





