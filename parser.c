#include "headers/parser.h"  

#define buf_size 1024

Struct parseFile(char* file_path, Struct s) {
        char buffer[buf_size];
        int file=open(file_path, O_RDONLY, 0666);
        int n = 1, i = 0;
        int w1 = 1, w2 = 0;
        int cm = 0, cmd = 0;
        int menores = 0, maiores = 0;
        char comment[buf_size],command[buf_size];
        while(n!=0) {
                if(i == 0) n = read(file,buffer,buf_size);
                if(n==0){ 
                        if(w2 == 1) {
                                command[cmd]='\0';
                                s = addCommand(comment,command,s);
                        }
                        break;
                }
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
                                        s = addCommand(comment,command,s);
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
                
                if(buffer[i] == '>' && maiores<3){ 
                        i++;
                        maiores++;
                        continue;
                }
                if(maiores == 3 && menores < 3) {
                        if(buffer[i] == '<') menores++;
                        if(buffer[i] != '<' && menores > 0) menores--;

                        i++; 
                        continue;

                }               		
                w1 = 1;
                menores = 0;
                maiores = 0;
        }
        close(file);
        return s;
}
