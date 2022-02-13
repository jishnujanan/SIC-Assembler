#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct node
{
    char label[10];
    int addr;
    struct node * link;
};
struct arrayOfstring
{
    char * opvalue;
} arrayOfstring[1000];
struct node* header=NULL;
struct node* ptr=NULL;
struct node* ptr1=NULL;
FILE *fp;
FILE *fpass1;
FILE *fpass2;
int locctr=0;
int hashvaluereturn(char * opcode)
{
    int len=strlen(strtok(opcode,"\n"));
    int i=0,hashvalue=0,jfactor=1;
    while(i<len)
    {
        hashvalue+=pow(opcode[i]-'0',1.5);
        jfactor*=opcode[i]-'0';
        i++;
    }
    hashvalue=hashvalue%jfactor;
    //arrayOfstring[hashvalue].opvalue=opvalue;
    //printf("The hashvalue of %s is %d\n",opcode,hashvalue);
    return hashvalue;
}

int hash(char *opcode,int opvalue)
{
    int len=strlen(strtok(opcode,"\n"));
    int i=0,hashvalue=0,jfactor=1;
    while(i<len)
    {
        hashvalue+=pow(opcode[i]-'0',1.5);
        jfactor*=opcode[i]-'0';
        i++;
    }
    hashvalue=hashvalue%jfactor;
    arrayOfstring[hashvalue].opvalue=opvalue;
    //printf("The hashvalue of %s is %d\n",opcode,hashvalue);
    return hashvalue;
}
int search(char* line,char* opcode)
{
    int len=strlen(line);
    int i=0;
    int j=0;
    while(i<len)
    {
        if(line[i]==opcode[j])
        {
            //printf("\nfound at i %d at %d",i,j);
            j++;
            if(j==strlen(opcode))
            {
                return i;
            }
        }
        i++;
    }
    return 0;
}
int symbol(char * label)
{
    struct node * ptr=header;
    while(ptr!=NULL)
    {
        //strcat(ptr->label,"\n");
        if(strcmp(ptr->label,label)==0)
        {
            return ptr->addr;
        }
        ptr=ptr->link;
    }
    return 0;
}
void symtab(char* labelname,int addr)
{
    ptr =(struct node *)malloc(sizeof(struct node));
    if(header==NULL)
    {
        ptr->addr=addr;
        strcpy(ptr->label,labelname);
        ptr->link=NULL;
        header=ptr;
        ptr1=ptr;
        //printf("data and address is %s %x\n",ptr->label,ptr->addr);
    }
    else
    {
        //ptr->label=labelname;
        ptr->addr=addr;
        strcpy(ptr->label,labelname);
        ptr->link=NULL;
        ptr1->link=ptr;
        ptr1=ptr1->link;
        //printf("data and address is %s %x\n",ptr->label,ptr->addr);
    }

}

int charToNum(int index,char * data)
{
    //printf("%s",data);
    int num,temp,decimal=0,start_addr=0;
    index+=1;//reaches to the space
    num=strlen(data)-index-2;
    temp=num;
    int k=0;
    int value;
    index++;
    while(k<num)
    {
        value=data[index]-'0';
        start_addr=start_addr*10+value;
        decimal+= pow(16,temp-1)*value;
        index++;
        k++;
        temp--;

    }
    return decimal;
}
int pass1()
{

    int i=0,loc;
    int decimal;
    int found=0;
    char data[30];
    fp=fopen("assembly.txt","r");
    fpass1=fopen("pass1.txt","w+");
    //fprintf(fpass1,"%s","data is");
    if(fp==NULL)
    {
        //printf("File not exist!!");
    }
    else
    {
        while(fgets(data,30,fp)!=NULL)
        {
            int j=0;
            char *tokens[3];
            tokens[1]="#";
            tokens[2]="#";
            char datacopy[30];
            char *token2,*token3,*label,*token;
            strcpy(datacopy,data);
            token = strtok(datacopy," ");
            while(token!=NULL)
            {
                tokens[j]=token;
                //printf("%s ",tokens[j]);
                token=strtok(NULL," ");
                j++;
            }
            label=tokens[0];
            token2=tokens[1];
            strtok(token2,"\n");
            token3=tokens[2];
            strtok(token3,"\n");
            strtok(label,"\n");
            //strcpy(label,tokens[0]);
            //strcpy(token2,tokens[1]);
            if(i==0)//for first line
            {
                int loc = search(data,"START");
                //printf("%s",data);
                //printf("loc is %d\n",loc);
                if(loc!=0)
                {
                    fprintf(fpass1,"%s",data);
                    locctr=charToNum(loc,data);
                    decimal=locctr;
                    //printf("%d",decimal);
                }
                else
                {
                    locctr=0;
                    decimal=0;


                    if(strcmp(label,"ADD") ==0||strcmp(label,"AND")==0||strcmp(label,"COMP")==0||strcmp(label,"DIV")==0||strcmp(label,"J")==0||strcmp(label,"JEQ")==0||strcmp(label,"JGT")==0||strcmp(label,"JLT")==0||strcmp(label,"JSUB")==0||strcmp(label,"LDA")==0|| strcmp(label,"LDCH")==0 || strcmp(label,"LDL") ==0|| strcmp(label,"LDX") ==0|| strcmp(label,"MUL")==0 || strcmp(label,"OR") ==0||strcmp(label,"RD")==0||strcmp(label,"RSUB")==0|| strcmp(label,"STA")==0 || strcmp(label,"STCH")==0 || strcmp(label,"STL") ==0|| strcmp(label,"STSW")==0 || strcmp(label,"STX")==0 || strcmp(label,"SUB") ==0|| strcmp(label,"TD")==0 || strcmp(label,"TIX") ==0|| strcmp(label,"WD")==0||strcmp(token2,"ADD") ==0||strcmp(token2,"AND")==0||strcmp(token2,"COMP")==0||strcmp(token2,"DIV")==0||strcmp(token2,"J")==0||strcmp(token2,"JEQ")==0||strcmp(token2,"JGT")==0||strcmp(token2,"JLT")==0||strcmp(token2,"JSUB")==0||strcmp(token2,"LDA")==0|| strcmp(token2,"LDCH")==0 || strcmp(token2,"LDL") ==0|| strcmp(token2,"LDX") ==0|| strcmp(token2,"MUL")==0 || strcmp(token2,"OR") ==0||strcmp(token2,"RD")==0||strcmp(token2,"RSUB")==0|| strcmp(token2,"STA")==0 || strcmp(token2,"STCH")==0 || strcmp(token2,"STL") ==0|| strcmp(token2,"STSW")==0 || strcmp(token2,"STX")==0 || strcmp(token2,"SUB") ==0|| strcmp(token2,"TD")==0 || strcmp(token2,"TIX") ==0|| strcmp(token2,"WD")==0)//||strcmp(label,"ADD") ==0||strcmp(label,"AND")==0||strcmp(label,"COMP")==0||strcmp(label,"DIV")==0||strcmp(label,"J")==0||strcmp(label,"JEQ")==0||strcmp(label,"JGT")==0||strcmp(label,"JLT")==0||strcmp(label,"JSUB")==0||strcmp(label,"LDA")==0|| strcmp(label,"LDCH")==0 || strcmp(label,"LDL") ==0|| strcmp(label,"LDX") ==0|| strcmp(label,"MUL")==0 || strcmp(label,"OR") ==0||strcmp(label,"RD")==0||strcmp(label,"RSUB")==0|| strcmp(label,"STA")==0 || strcmp(label,"STCH")==0 || strcmp(label,"STL") ==0|| strcmp(label,"STSW")==0 || strcmp(label,"STX")==0 || strcmp(label,"SUB") ==0|| strcmp(label,"TD")==0 || strcmp(label,"TIX") ==0|| strcmp(label,"WD")==0)//||strcmp(token2,"ADD") ==0||strcmp(token2,"AND")==0||strcmp(token2,"COMP")==0||strcmp(token2,"DIV")==0||strcmp(token2,"J")==0||strcmp(token2,"JEQ")==0||strcmp(token2,"JGT")==0||strcmp(token2,"JLT")==0||strcmp(token2,"JSUB")==0||strcmp(token2,"LDA")==0|| strcmp(token2,"LDCH")==0 || strcmp(token2,"LDL") ==0|| strcmp(token2,"LDX") ==0|| strcmp(token2,"MUL")==0 || strcmp(token2,"OR") ==0||strcmp(token2,"RD")==0||strcmp(token2,"RSUB")==0|| strcmp(token2,"STA")==0 || strcmp(token2,"STCH")==0 || strcmp(token2,"STL") ==0|| strcmp(token2,"STSW")==0 || strcmp(token2,"STX")==0 || strcmp(token2,"SUB") ==0|| strcmp(token2,"TD")==0 || strcmp(token2,"TIX") ==0|| strcmp(token2,"WD")==0)
                    {
                        if(token3==NULL)
                        {
                            fprintf(fpass1,"%x %s",decimal,data);

                        }
                        else
                        {
                            fprintf(fpass1,"%x %s %s",decimal,token2,token3);
                        }
                        decimal+=3;
                    }
                    else
                    {
                        if(loc = (search(data,"WORD")))
                        {
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used already");//set error flag
                            }
                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=3;
                        }
                        else if(loc = search(data,"BYTE"))
                        {
                            //||strcmp(label,"WORD")||strcmp(label,"RESW")||strcmp(label,"RESB")||strcmp(label,"BYTE")
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }
                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=1;
                        }
                        else if(loc = search(data,"RESW"))
                        {
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }

                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=3*charToNum(loc,data);
                        }
                        else if(loc = search(data,"RESB"))
                        {
                            //printf("in resb");
                            struct node* ptr2;
                            ptr2=header;
                            while(ptr2!=NULL)
                            {
                                if(strcmp(ptr2->label,label)==0)
                                {
                                    found=1;
                                    //printf("data = date");
                                    break;
                                }
                                ptr2=ptr2->link;
                            }
                            free(ptr2);
                            if(found==0)
                            {
                                symtab(label,decimal);
                            }
                            else
                            {
                                fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                            }


                            fprintf(fpass1,"%x %s",decimal,data);
                            decimal+=1*charToNum(loc,data);
                        }





                        //int address=symbol(label);

                    }
                }
                i++;
            }
            else//for rest of lines
            {

                found=0;
                if(strcmp(label,"ADD") ==0||strcmp(label,"AND")==0||strcmp(label,"COMP")==0||strcmp(label,"DIV")==0||strcmp(label,"J")==0||strcmp(label,"JEQ")==0||strcmp(label,"JGT")==0||strcmp(label,"JLT")==0||strcmp(label,"JSUB")==0||strcmp(label,"LDA")==0|| strcmp(label,"LDCH")==0 || strcmp(label,"LDL") ==0|| strcmp(label,"LDX") ==0|| strcmp(label,"MUL")==0 || strcmp(label,"OR") ==0||strcmp(label,"RD")==0||strcmp(label,"RSUB")==0|| strcmp(label,"STA")==0 || strcmp(label,"STCH")==0 || strcmp(label,"STL") ==0|| strcmp(label,"STSW")==0 || strcmp(label,"STX")==0 || strcmp(label,"SUB") ==0|| strcmp(label,"TD")==0 || strcmp(label,"TIX") ==0|| strcmp(label,"WD")==0||strcmp(token2,"ADD") ==0||strcmp(token2,"AND")==0||strcmp(token2,"COMP")==0||strcmp(token2,"DIV")==0||strcmp(token2,"J")==0||strcmp(token2,"JEQ")==0||strcmp(token2,"JGT")==0||strcmp(token2,"JLT")==0||strcmp(token2,"JSUB")==0||strcmp(token2,"LDA")==0|| strcmp(token2,"LDCH")==0 || strcmp(token2,"LDL") ==0|| strcmp(token2,"LDX") ==0|| strcmp(token2,"MUL")==0 || strcmp(token2,"OR") ==0||strcmp(token2,"RD")==0||strcmp(token2,"RSUB")==0|| strcmp(token2,"STA")==0 || strcmp(token2,"STCH")==0 || strcmp(token2,"STL") ==0|| strcmp(token2,"STSW")==0 || strcmp(token2,"STX")==0 || strcmp(token2,"SUB") ==0|| strcmp(token2,"TD")==0 || strcmp(token2,"TIX") ==0|| strcmp(token2,"WD")==0)
                {
                    if(strcmp(token3,"#")==0)
                    {
                        //printf("here %d %s %s\n",strlen(token3),token2,token3);
                        fprintf(fpass1,"%x %s",decimal,data);

                    }
                    else
                    {
                        fprintf(fpass1,"%x %s %s\n",decimal,token2,token3);
                    }
                    decimal+=3;
                }
                else if(loc = search(data,"WORD"))
                {
                    //found=0;
                    struct node * ptr2=header;
                    while(ptr2!=NULL)
                    {

                        if(strcmp(ptr2->label,label)==0)
                        {
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    if(found==0)
                    {
                        symtab(label,decimal);
                        fprintf(fpass1,"%x %s",decimal,data);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                    }

                    decimal+=3;
                }
                else if(loc = search(data,"BYTE"))
                {
                    //||strcmp(label,"WORD")||strcmp(label,"RESW")||strcmp(label,"RESB")||strcmp(label,"BYTE")
                    //found=0;
                    struct node * ptr2=header;
                    while(ptr2!=NULL)
                    {
                        if(strcmp(ptr2->label,label)==0)
                        {
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    if(found==0)
                    {
                        symtab(label,decimal);
                        fprintf(fpass1,"%x %s",decimal,data);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal," symbol used aready");//set error flag
                    }
                    decimal+=1;
                }
                else if(loc = search(data,"RESW"))
                {
                    //found=0;
                    struct node * ptr2=header;
                    while(ptr2!=NULL)
                    {
                        if(strcmp(ptr2->label,label)==0)
                        {
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    if(found==0)
                    {
                        symtab(label,decimal);
                    }
                    else
                    {
                        fprintf(fpass1,"%X %s",decimal,"symbol used aready");//set error flag
                    }

                    fprintf(fpass1,"%x %s",decimal,data);
                    //printf("resw length in instruction is %d",charToNum(loc,data));
                    decimal+=charToNum(loc,data)*3;
                }
                else if(loc = search(data,"RESB"))
                {
                    //found=0;
                    struct node * ptr2=header;
                    while(ptr2!=NULL)
                    {
                        if(strcmp(ptr2->label,label)==0)
                        {
                            //printf("DATA CMP DATE %d",strcmp("DATA","DATE"));
                            found=1;
                            break;
                        }
                        ptr2=ptr2->link;
                    }
                    free(ptr2);
                    //printf("\n%s  %d value of found",data,found);
                    if(found==0)
                    {
                        symtab(label,decimal);
                    }
                    else
                    {
                        fprintf(fpass1,"%x %s",decimal,"symbol used aready");//set error flag
                    }
                    fprintf(fpass1,"%x %s",decimal,data);

                    int bytes=0;
                    char *string;
                    strcpy(string,data);
                    char* token1,*token2,*token3;
                    char* token = strtok(string, " ");
                    token1=token;
                    token=strtok(NULL," ");
                    token2=token;
                    token=strtok(NULL," ");
                    token3=token;
                    strtok(token3,"\n");
                    int count=0;
                    //printf("count %d",count);
                    while(count<strlen(token3))
                    {
                        bytes=bytes*10+(token3[count]-'0');
                        count++;
                    }
                    //printf("\nThe bytes is %d",bytes);
                    decimal=decimal+bytes;
                    //printf("\nchar to num is %x\n",charToNum(loc,data));
                    //printf("\nNow the decimal is at %d\n",decimal);

                }
                else if(loc = search(data,"END") )
                {
                    fprintf(fpass1,"%x END",decimal);
                    fclose(fp);
                    fclose(fpass1);

                }


            }
        }

    }
    return decimal;
}
void pass2(int starting_address)
{
    fpass1=fopen("pass1.txt","r");
    fpass2=fopen("pass2.txt","w+");
    char data[25];
    char *machinecode;
    int index=0,address,size_textrecord=0,hashingvalue,check=0;
    char * token1,*token2,*token3,*token4;
    while(fgets(data,25,fpass1)!=NULL)
    {
        int j=0;
        index=0;
        char * tokens[4];
        tokens[3]="#";
        tokens[2]="#";
        char* token = strtok(data, " ");
        while(token!=NULL)
        {
            tokens[j]=token;
            token=strtok(NULL," ");
            j++;
        }
        token1=tokens[0];
        token2=tokens[1];
        token3=tokens[2];
        token4=tokens[3];
        strtok(token2,"\n");
        strtok(token3,"\n");
        strtok(token4,"\n");
        //token=strtok(NULL," ");
        printf("token2 is %s\n",token2);
        if(strcmp(token2,"START")==0)
        {
            if(strlen(token3)==2)
            {
                fprintf(fpass2,"H^%s^0000%s^%x",token1,token3,starting_address-locctr);
            }
            else if(strlen(token3)==4)
            {
                fprintf(fpass2,"H^%s^00%s^%x",token1,token3,starting_address-locctr);
            }
            fprintf(fpass2,"\nT^%s",token3);
        }
        else if(strcmp(strtok(token2,"\n"),"ADD") ==0||strcmp(strtok(token2,"\n"),"AND")==0||strcmp(strtok(token2,"\n"),"COMP")==0||strcmp(strtok(token2,"\n"),"DIV")==0||strcmp(strtok(token2,"\n"),"J")==0||strcmp(strtok(token2,"\n"),"JEQ")==0||strcmp(strtok(token2,"\n"),"JGT")==0||strcmp(strtok(token2,"\n"),"JLT")==0||strcmp(strtok(token2,"\n"),"JSUB")==0||strcmp(strtok(token2,"\n"),"LDA")==0|| strcmp(strtok(token2,"\n"),"LDCH")==0 || strcmp(strtok(token2,"\n"),"LDL") ==0|| strcmp(strtok(token2,"\n"),"LDX") ==0|| strcmp(strtok(token2,"\n"),"MUL")==0 || strcmp(strtok(token2,"\n"),"OR") ==0||strcmp(strtok(token2,"\n"),"RD")==0|| strcmp(strtok(token2,"\n"),"STA")==0 || strcmp(strtok(token2,"\n"),"STCH")==0 || strcmp(strtok(token2,"\n"),"STL") ==0|| strcmp(strtok(token2,"\n"),"STSW")==0 || strcmp(strtok(token2,"\n"),"STX")==0 || strcmp(strtok(token2,"\n"),"SUB") ==0|| strcmp(strtok(token2,"\n"),"TD")==0 || strcmp(strtok(token2,"\n"),"TIX") ==0|| strcmp(strtok(token2,"\n"),"WD")==0)
        {

            if(token3!=NULL)
            {
                index=search(token3,",X");
                if(index==0)
                {

                    hashingvalue=hashvaluereturn(token2);
                    machinecode=arrayOfstring[hashingvalue].opvalue;
                    //printf("\nThe opcode is %s for opcode% s\n",machinecode,token2);
                    address=symbol(token3);
                    //printf("address is %x",address);
                    if(size_textrecord==30)
                    {

                        fprintf(fpass2,"^%x\nT^%s^%s%x",size_textrecord,token1,machinecode,address);
                        size_textrecord=0;
                    }
                    else
                    {
                        fprintf(fpass2,"^%s%x",machinecode,address);
                    }


                }
                else
                {
                    hashingvalue=hashvaluereturn(strtok(token2,","));
                    machinecode=arrayOfstring[hashingvalue].opvalue;
                    address=symbol(strtok(token3,",X"))+32768;
                    //printf("address is %d\n",symbol(token3));
                    //printf("token3 is %s\n",token3);
                    if(size_textrecord==30)
                    {
                        fprintf(fpass2,"^%x\nT^%s^%s%x",size_textrecord,token1,machinecode,address);
                        size_textrecord=0;
                    }
                    else
                    {
                        fprintf(fpass2,"^%s%x",machinecode,address);
                    }
                }
                size_textrecord+=3;
                check=0;
            }
        }
        else if(strcmp(token2,"RSUB")==0)
        {

            hashingvalue=hashvaluereturn(token2);
            machinecode=arrayOfstring[hashingvalue].opvalue;
            if(size_textrecord==30)
            {

                fprintf(fpass2,"^%x\nT^%s^%s0000",size_textrecord,token1,machinecode);
                size_textrecord=0;

            }
            else
            {
                fprintf(fpass2,"^%s0000",machinecode);
            }
            size_textrecord+=3;
            check=0;

        }
        else if(strcmp(token3,"WORD")==0)
        {
            if(token4!=NULL)
            {
                if(check==0)
                {
                    if(size_textrecord==30)
                    {
                        int lengthofword=strlen(token4);
                        if(lengthofword==1)
                            fprintf(fpass2,"^%x\nT^%s^00000%s",size_textrecord,token1,token4);
                        else if(lengthofword==2)
                            fprintf(fpass2,"^%x\nT^%s^0000%s",size_textrecord,token1,token4);
                        else if(lengthofword==3)
                            fprintf(fpass2,"^%x\nT^%s^000%s",size_textrecord,token1,token4);
                        check=1;
                        size_textrecord=0;
                    }
                    else
                    {
                        int lengthofword=strlen(token4);
                        if(lengthofword==1)
                            fprintf(fpass2,"^%x\nT^%s^00000%s",size_textrecord,token1,token4);
                        else if(lengthofword==2)
                            fprintf(fpass2,"^%x\nT^%s^0000%s",size_textrecord,token1,token4);
                        else if(lengthofword==3)
                            fprintf(fpass2,"^%x\nT^%s^000%s",size_textrecord,token1,token4);
                            size_textrecord=0;
                    }
                    size_textrecord+=3;
                }
                else//ALREADY A WORD APPEARED BEFORE
                {
                    if(size_textrecord==30)
                    {
                        int lengthofword=strlen(token3);
                        if(lengthofword==1)
                            fprintf(fpass2,"^%x\nT^%s^00000%s",size_textrecord,token1,token4);
                        else if(lengthofword==2)
                            fprintf(fpass2,"^%x\nT^%s^0000%s",size_textrecord,token1,token4);
                        else if(lengthofword==3)
                            fprintf(fpass2,"^%x\nT^%s^000%s",size_textrecord,token1,token4);

                        size_textrecord=0;
                    }
                    else
                    {
                        int lengthofword=strlen(token3);
                        if(lengthofword==1)
                            fprintf(fpass2,"^00000%s",token4);
                        else if(lengthofword==2)
                            fprintf(fpass2,"^0000%s",token4);
                        else if(lengthofword==3)
                            fprintf(fpass2,"^000%s",token4);
                    }
                    size_textrecord+=3;
                }
            }
        }
        else if(strcmp(token3,"BYTE")==0)
        {
            if(token4!=NULL)
            {
                if(check==0)
                {
                    fprintf(fpass2,"^%x\nT^%s^%s",size_textrecord,token1,strtok(token4,"'"));
                    if(size_textrecord==30)
                    {
                        size_textrecord=0;
                    }
                    else
                    {

                    }
                    check=1;
                }
                else
                {

                    if(size_textrecord==30)
                    {
                        fprintf(fpass2,"^%x\nT^%s^%s",size_textrecord,token1,strtok(token4,"'"));
                        size_textrecord=0;
                    }
                    else
                    {
                        fprintf(fpass2,"^%s",strtok(token4,"'"));
                    }

                }
                size_textrecord+=1;
            }
        }
        else if(strcmp(token3,"RESW")==0||strcmp(token3,"RESB")==0)
        {
            //size_textrecord=0;
            check=0;
        }
        else if(strcmp(token2,"END")==0)
        {
            fprintf(fpass2,"^%x\nE^%x",size_textrecord,locctr);
        }




    }
    fclose(fpass2);
}
int main()
{
    hash("ADD","40");
    hash("AND","18");
    hash("COMP","28");
    hash("DIV","24");
    hash("J","3C");
    hash("JEQ","30");
    hash("JSUB","48");
    hash("JLT","38");
    hash("JGT","34");
    hash("LDL","08");
    hash("LDA","00");
    hash("LDCH","50");
    hash("LDX","04");
    hash("MUL","20");
    hash("OR","44");
    hash("RD","D8");
    hash("RSUB","4C");
    hash("STA","0C");
    hash("STCH","54");
    hash("STL","14");
    hash("STSW","E8");
    hash("STX","10");
    hash("SUB","1C");
    hash("TD","E0");
    hash("TIX","2C");
    hash("WD","DC");
    int size;
    size=pass1();
    pass2(size);
    ptr=header;
    printf("THE SYMBOL TABLE\n\nsymbol      address\n");
    printf("\n");
    while(ptr!=NULL)
    {
        printf("%s         %x\n",ptr->label,ptr->addr);
        ptr=ptr->link;
    }
    return 0;
}
