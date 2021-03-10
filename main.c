#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>>
#include <string.h>
#include <stdbool.h>
char*substring(char*destination,const char *source,int start,int length){       /* diziden substring almamizi saglar*/
   strncpy(destination, (source + start), length);
    return destination;
}
bool isKeyword(char* str)      //keyword bool durumu
{
    if (!strcasecmp(str, "if") || !strcasecmp(str, "else") ||
        !strcasecmp("while",str) || !strcasecmp(str, "do") ||
        !strcasecmp(str, "break") ||
         !strcasecmp(str, "continue") || !strcasecmp(str, "int")
        || !strcasecmp(str, "double") || !strcasecmp(str, "float")
        || !strcasecmp(str, "return") || !strcasecmp(str, "char")
        || !strcasecmp(str, "case")
        || !strcasecmp(str, "sizeof") || !strcasecmp(str, "for")
          || !strcasecmp(str, "const")
         || !strcasecmp(str, "enum")
        || !strcasecmp(str, "long") || !strcasecmp(str, "static")
        || !strcasecmp(str, "record") || !strcasecmp(str, "goto"))
        return (true);
    return (false);
}
bool isDelimiter(char ch)    //delimeter bool durumu
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}
int main()
{
    int i;
    FILE *fp;
    FILE*fptr;
    char* leftpar="LeftPar";
    char * endofLine="EndOfLine";
    char* rightpar="RightPar";
    char*leftSquare="LeftSquareBracket";
    char*RightSquare="RightSquareBracket";
    char*leftCurly="LeftCurlyBracket";
    char*RightCurly="RightCurlyBracket";
    int begin=0;

    char*strings;
    char *subs;
    char *digitstring;
    int bufferLength = 255;
    char satir[bufferLength];
    bool tirnaklimi=false;
    bool yorummu=false;
    int substringlength=0;
    int tirnaklenght=2;


   fp = fopen("code.psi.txt", "r");
   fptr=fopen("code.lex.txt","w");                     //okunacak ve yazilacak dosyalarin acilmasi...

   //while(fscanf(fp, "%s", satir)!=EOF){
   if ((fp) == NULL){
 printf("dosya okumada hata var");
   }
else{
  while(fgets(satir, bufferLength, fp)) {   //dosyayi bu while dongusuyle satir satir okuruz...

   printf("Satir: %s \n", satir );
    int digitlength=0;

    for(i=0;i<strlen(satir);++i){                              //satirin icinde karakter karakter donmemizi saglayan for dongusu..

        if(isdigit(satir[i])&&yorummu==false){                  //integer degerleri bulmak icin kurdugumuz if yapisi..
                                                                //karakter digitse ve yorum satiri degilse ife  girer.
            begin=i;
        if( i>0 && (isDelimiter(satir[i-1]))){

                while(isDelimiter(satir[i])==false){                //satirdaki ilk karakter degilken integer olma kontrolu..
                                                                    /*burada operator veya bosluktan baslayip herhangi bir bosluk
                                                                    veya operator gelene kadar dongu doner. bu sayede substring icin bize lazim
                                                                    olan substringin uzunlugunu buluruz. */


                    digitlength++;
                    i++;
                }


        }
        if(i==0){


                while(isDelimiter(satir[i])==false){            // satirin ilk karakteri digitse  substring olusturmak icin
                                                                //digitlength buluruz.


                    digitlength++;
                    i++;
                }

        }

        digitstring = malloc(sizeof(char) * (digitlength));     /*integer icin dinamik array olusturulur.
                                                                    ve bu arrayle substring olustururuz.
                                                                    Orn:"1582" , "15864ahmet" */
        substring(digitstring,satir,begin,digitlength);
        int tutac;
         bool flag2=false;
        while(tutac<digitlength){
            if(isdigit(digitstring[tutac])==false){             /* substringin her karakterinin digit olup olmama kontrolu*/
                flag2=true;                                         //her karakteri digit degilse hatali identifier !!!
            }
                tutac++;                                            //Orn :"9582ahmet" hatalý identifier.
        }
        tutac=0;
         //printf("digitstring %s\n",digitstring);
        if (flag2==false){
                if(digitlength>10){
                    printf("ERROR!!! Integer size can't be bigger than 10: %s\n",digitstring);
                    fprintf(fptr,"ERROR!!! Integer size can't be bigger than 10: %s\n",digitstring);
                }
                else{
                    //printf("int const %s\n",digitstring);
                     fprintf(fptr,"int const (%s)\n",digitstring);
                }
        }
        else{
            //printf("invalid %s\n ",digitstring);
            printf("ERROR! An identifier must be start with alphabetic character: %s\n ",digitstring);
            fprintf(fptr,"ERROR! An identifier must be start with alphabetic character: %s\n ",digitstring);
        }
        digitlength=0;
        begin=0;
        }
        if(isalpha(satir[i])&&yorummu==false)                               //identifier olusturma kontrolu.
        {    begin=i;
        if(i==0){
             while(isalpha(satir[i])||satir[i]=='_'||isdigit(satir[i])){
                substringlength++;
                //fprintf(fptr,"%c",satir[i]);
                i++;
            }
            if(substringlength>20){
                printf("ERROR! Please check identifier size\n");

                fprintf(fptr,"ERROR! Please check identifier size\n");
            }
            else{
                subs = malloc(sizeof(char) * (substringlength));    /* olusturulan substring keyworde esit degilse
                                                                        identifier olma kontrolu.*/
            substring(subs,satir,begin,substringlength);
                    substringlength=0;

            if(isKeyword(subs)==true){
                    for(int i = 0; subs[i]; i++){
                subs[i] = tolower(subs[i]);
                }

                //printf("Keyword (%s)\n", subs);
             fprintf(fptr,"Keyword (%s)\n",subs);

            }
            else{
                //printf("identifier (%s)\n", subs);
                 for(int i = 0; subs[i]; i++){
                subs[i] = toupper(subs[i]);
                }
             fprintf(fptr,"identifier (%s)\n",subs);
            }
            }
            substringlength=0;
        }

       else if(i>0&&(isDelimiter(satir[i-1]))){
            while(isalpha(satir[i])||satir[i]=='_'||isdigit(satir[i])){

                substringlength++;
                //fprintf(fptr,"%c",satir[i]);
                i++;
            }
            if(substringlength>20){

                printf("ERROR! Please check identifier size.\n");

                fprintf(fptr,"ERROR! Please check identifier size.\n");

            }

            else{
                //printf("%d\n",substringlength);
                subs = malloc(sizeof(char) * (substringlength));         // substring.
            substring(subs,satir,begin,substringlength);
                    substringlength=0;
            if(isKeyword(subs)==true){
                     for(int i = 0; subs[i]; i++){
                subs[i] = tolower(subs[i]);
                }
                //printf("Keyword %s\n", subs);
             fprintf(fptr,"Keyword (%s)\n",subs);
            }
            else{
                 //printf("identifier %s\n", subs);
                  for(int i = 0; subs[i]; i++){
                subs[i] = toupper(subs[i]);
                }
             fprintf(fptr,"identifier (%s)\n",subs);
            }
            }
        }
 }
       //identifier[a]=satir[i];
            //fprintf(fptr,"\n");
              if(satir[i]==';'&&yorummu==false){fprintf(fptr,"%s\n",endofLine);}    //end of line;
            bool flag7=false;
        if(satir[i]=='('&&yorummu==false){                  /*yorum satiri kontrolu dosyanin sonuna kadar kontrol edilir. eger
                                                        yorummu=true kalirsa lexical error verdirilir. */
            //fprintf(fptr,"%s \n",leftpar);
                i++;
            if(satir[i]=='*'){
                    i++;
                    yorummu=true;
                    flag7=true;

            }
            if (flag7==false){
                fprintf(fptr,"%s \n",leftpar);
            }
        }
        if(satir[i]=='*'){
            //fprintf(fptr,"%s \n",leftpar);
                i++;
            if(satir[i]==')'){
                    i++;
                    yorummu=false;

            }

        }
        if(satir[i]==')'&&yorummu==false){ fprintf(fptr,"%s \n",rightpar);}
        if(satir[i]=='['&&yorummu==false){ fprintf(fptr,"%s \n",leftSquare);}
        if(satir[i]==']'&&yorummu==false){ fprintf(fptr,"%s \n",RightSquare);}
        if(satir[i]=='{'&&yorummu==false){ fprintf(fptr,"%s \n",leftCurly);}
        if(satir[i]=='}'&&yorummu==false){ fprintf(fptr,"%s \n",RightCurly);}
        int flag1=0;
        if (satir[i]=='+'&&flag1==0&&yorummu==false){
                if(satir[i+1]=='+'){
                    fprintf(fptr,"Operator(++) %c \n");
                    flag1=1;
                    i++;
                }
                else{
                    fprintf(fptr,"Operator(+) %c \n");

                }
        } flag1=0;
        if (satir[i]=='-'&&flag1==0&&yorummu==false){
                if(satir[i+1]=='-'){
                    fprintf(fptr,"Operator(--) %c \n");
                    flag1=1;
                    i++;
                }
                else{
                    fprintf(fptr,"Operator(-) %c \n");
                }

   }
   if(satir[i]==':'&&satir[i+1]=='='&&yorummu==false){
    fprintf(fptr,"Operator(:=) %c \n");

   }
   if(satir[i]=='*'&&yorummu==false){fprintf(fptr,"Operator(*) %c\n");}

   if(satir[i]=='/'&&yorummu==false){fprintf(fptr,"Operator(/) %c\n");}

  /* if(satir[i]=='"'){
        fprintf(fptr,"string ");
        i++;
        tirnaklimi=true;
        while(satir[i]!='"'&&tirnaklimi==true){
            fprintf(fptr,"%c",satir[i]);
            i++;

            if (satir[i]=='"'){

                tirnaklimi=false;
            }
        }
        if(tirnaklimi){
            fprintf(fptr,"Lexical Error!");

        }

   }*/

   if(satir[i]=='"'){                   /*string kontrolu. satir sonuna kadar kontrol edilir . eger quote kapanmadiysa
                                                lexical error verdirilir.*/
    int begin=i;
    tirnaklimi=true;
    i++;
    while(i<strlen(satir)&&tirnaklimi&&yorummu==false){

        tirnaklenght++;

        i++;
        if(satir[i]=='"'){

            tirnaklimi=false;

            strings=malloc(sizeof(char)*tirnaklenght);
            substring(strings,satir,begin,tirnaklenght);
            //printf("%s",strings);
            fprintf(fptr,"String (%s)\n",strings);
        }

    }
    tirnaklenght=2;
    if(tirnaklimi&&yorummu==false){
        printf("Quote is missed!!!\n");
        fprintf(fptr,"Quote is missed!!!\n");
    }
   }
        }



printf("\n");

     }

if(yorummu){
    printf("Comment ERROR!!!\n");
    fprintf(fptr,"Comment ERROR!!!\n");
}
printf("\n");
printf("Analysis was made to the Code.lex file.");
printf("\n");
}
free(subs);
free(digitstring);
free(strings);
fclose(fp);
fclose(fptr);
    return 0;
   }
