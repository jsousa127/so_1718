#include "headers/parser.h"  

Struct parseFile(char* file_path, Struct s) {
        char buffer[128];
        int file=open(file_path, O_RDONLY, 0666);
        int n = 1, i = 0;
        int w1 = 1, w2 = 0;
        int cm = 0, cmd = 0;
        int menores = 0, maiores = 0;
        char comment[512],command[128];
        while(n!=0) {
                if(i == 0) n = read(file,buffer,128);
                if(n==0) break;
                if (w1 == 1){
                        while(1) {
                                comment[cm]=buffer[i];
                                cm++;
                                i++;
                                if (i==n) {
                                        i = 0;
                                        break;
                                }
                                if (buffer[i]=='$') {
                                        comment[cm]='\0';
                                        cm = 0;
                                        w1=0;
                                        w2=1;
                                        break;
                                }
                        }
                        if (w1 == 1) continue;
                }
                if (w2 == 1){         
                        while(2) {
                                command[cmd] = buffer[i];
                                cmd++;
                                i++;
                                if(i==n) {
                                        i = 0;
                                        break;
                                }    
                                if (buffer[i]=='\n') {
                                        command[cmd]='\0';
                                        cmd = 0;
                                        w2=0;
                                        break;
                                }
                        }

                        if (w2 == 1) continue;
                        else i++;
                }
                if(i==n) {
                        i = 0;
                        continue;
                }
                if(buffer[i] == '<'){
                        i++;
                        menores++;
                        continue;
                }
                if(menores == 3 && maiores < 3) {
                        if(buffer[i] == '>') maiores++;
                        i++;
                        continue;

                }               		
                s = addCommand(comment,command,s);
                w1 = 1;
                menores = 0;
                maiores = 0;
        }
        close(file);
        return s;
}
