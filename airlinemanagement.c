#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include <time.h>
#include<ctype.h>
#include<io.h>
#include<malloc.h>

char airport[12][16]={"AMRISTAR ","AHMEDABAD","BANGALORE","CHENNAI  ","DELHI\t","GOA  \t","HYDERABAD","JAIPUR   ","KOCHI\t","LUCKNOW  ","MUMBAI   ","PUNE \t"};
long long int cPNR;
int check=0;

struct passenger{
    long long int PNR;
    int flight_no;
    int flight_class;
    int dep_ar[2];
    int seat_no;
};

struct route{
    int loc;
    int time[2];
    struct route *next;
};

struct flights{
    struct route *rt;
    char flight_name[50];
    int flight_no;
    int dep_ar[2];
    int first,business;
    int econA;
    int econB;
    int econC;
}flights[12];

void login();
void mainmenu(char user[20],char pw[20]);
void signup();
void shutdown();
void startup();
int* search(char user[20],char pw[20],int c);
void database();
void cancelbooking(char user[20],char pw[20]);
void newbooking(char user[20],char pw[20]);
void check_upcoming(char user[20],char pw[20]);

void delay(int number_of_seconds){
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while(clock() < start_time + milli_seconds) ;
}

int cfileexists(const char * filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

void newdir(){
 int check;
 char* dirname = "airlines dbs";
 system("cls");
 check = mkdir(dirname);
 // check if directory is created or not
 if (!check){
     FILE *file;
     mkdir("./airlines dbs/flights");
     file = fopen("./airlines dbs/flights/PNRdata.txt","w");
     cPNR=1000000000;
     fprintf(file,"%lld",cPNR);
     fclose(file);
     file = fopen("./airlines dbs/flights/f0.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[0].first,flights[0].business,flights[0].econA,flights[0].econB,flights[0].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f1.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[1].first,flights[1].business,flights[1].econA,flights[1].econB,flights[1].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f2.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[2].first,flights[2].business,flights[2].econA,flights[2].econB,flights[2].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f3.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[3].first,flights[3].business,flights[3].econA,flights[3].econB,flights[3].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f4.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[4].first,flights[4].business,flights[4].econA,flights[4].econB,flights[4].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f5.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[5].first,flights[5].business,flights[5].econA,flights[5].econB,flights[5].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f6.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[6].first,flights[6].business,flights[6].econA,flights[6].econB,flights[6].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f7.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[7].first,flights[7].business,flights[7].econA,flights[7].econB,flights[7].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f8.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[8].first,flights[8].business,flights[8].econA,flights[8].econB,flights[8].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f9.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[9].first,flights[9].business,flights[9].econA,flights[9].econB,flights[9].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f10.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[10].first,flights[10].business,flights[10].econA,flights[10].econB,flights[10].econC);
     fclose(file);
     file = fopen("./airlines dbs/flights/f11.txt","w");
     fprintf(file,"%d %d %d %d %d\n",flights[11].first,flights[11].business,flights[11].econA,flights[11].econB,flights[11].econC);
     fclose(file);
     printf("Directory created\n");
 }
 else{
     FILE *file;
     file = fopen("./airlines dbs/flights/PNRdata.txt","r");
     fscanf(file,"%lld",&cPNR);
     fclose(file);
 }
}

void display_airport(){
 printf("\n\t\t 1.AMRISTAR\t");
 printf("\n\t\t 2.AHMEDABAD\t");
 printf("\n\t\t 3.BANGALORE\t");
 printf("\n\t\t 4.CHENNAI\t");
 printf("\n\t\t 5.DELHI\t");
 printf("\n\t\t 6.GOA\t");
 printf("\n\t\t 7.HYDERABAD\t");
 printf("\n\t\t 8.JAIPUR\t");
 printf("\n\t\t 9.KOCHI\t");
 printf("\n\t\t 10.LUCKNOW\t");
 printf("\n\t\t 11.MUMBAI\t");
 printf("\n\t\t 12.PUNE\t");
}

int* search_flights(int departure,int arrival,int *num){
    int i,check,j=0;
    int *list=malloc(12*sizeof(int));
    struct route *r;
    for(i=0;i<12;i++)
    {
        check=0;
        r=flights[i].rt;
        while(r!=NULL)
        {
            if(r->loc==departure)
              check++;
            else if(r->loc==arrival && check==1)
            {
                check++;
                *(list+j)=i;
                j++;
                break;
            }
            r=r->next;
        }
    }
    *num=j;
    return list;
}

void display_route(int n){
    struct route *f=flights[n].rt;
    while(f!=NULL){
        printf("\n\t\t%s\t%d:%d",airport[f->loc],f->time[0],f->time[1]);
        f=f->next;
    }
}

void display_flights(int n){
    printf("%s",flights[n].flight_name);
    printf("\n\t\t     FLIGHT NO : %d",flights[n].flight_no);
    printf("\n\t\t     FROM : %s",airport[flights[n].dep_ar[0]]);
    printf("\n\t\t     TO   : %s",airport[flights[n].dep_ar[1]]);
}

int main(){
    database();
    newdir();
    startup();
}

void login(){
    char user[20],pw[20],c,num[20];
    char dir[100]="./airlines dbs/";
    int len,ch,i;
    FILE *fptr;
    redouser:
    strcpy(dir,"./airlines dbs/");
    ch=0;
    system("cls");
    printf("\n\t\t****************************");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t*\t LOGIN\t    \t   *");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t****************************");
    printf("\n\n\t\tUSERNAME : ");
    scanf("\n");
    scanf("%[^\n]%*c",user);
    len=strlen(user);
    if(len>16 || len<6)
    {
        printf("\n\t\tWARNING : USERNAME DOES NOT FOLLOW CONDITIONS. RETRY\n");
        delay(1);
        printf("\n\t\tENTER 'Y' TO RETURN TO MAIN MENU. ENTER ANY OTHER KEY TO RETRY.");
        scanf("%s",&c);
        if(c=='Y' || c=='y')
            return;
        else delay(1);
        goto redouser;
    }
    for(i=0;i<len;i++)
    {
        if(isalnum(user[i])==0)
            ch++;
    }
    if(ch!=0)
    {
        printf("\n\t\tWARNING : USERNAME DOES NOT FOLLOW CONDITIONS. RETRY\n");
        delay(1);
        printf("\n\t\tENTER 'Y' TO RETURN TO MAIN MENU. ENTER ANY OTHER KEY TO RETRY.");
        scanf("%s",&c);
        if(c=='Y' || c=='y')
            return;
        else delay(1);
        goto redouser;
    }
    strcat(dir,user);
    strcat(dir,".txt");
    if(cfileexists(dir)==0)
    {
        printf("\n\t\tWARNING : USERNAME DOES NOT EXIST. RETRY.\n");
        delay(1);
        printf("\n\t\tENTER 'Y' TO RETURN TO MAIN MENU. ENTER ANY OTHER KEY TO RETRY.");
        scanf("%s",&c);
        if(c=='Y' || c=='y')
            return;
        else delay(1);
        goto redouser;
    }
    printf("\t\tPASSWORD : ");
    i=0;
    do{
        pw[i]=getch();
        if(pw[i]!='\r' && pw[i]!='\b'){
            printf("*");
        }
        if(pw[i]=='\b' &&  i>0)
        {
            printf("\b \b");
            i--;
        }
        else
         i++;
        if(i>16)
        {
            printf("\n\t\tWARNING : EXCEEDED 16 CHARACTERS. RETRY.");
            delay(1);
            goto redouser;
        }
        else if(i==1 && pw[i-1]=='\r')
        {
            printf("\n\t\tWARNING : ENTER MINIMUM OF 8 CHARACTERS. RETRY.");
            delay(1);
            goto redouser;
        }
        if(pw[i-1]==' ')
        {
            printf("\n\t\tWARNING : PASSWORD SHOULD NOT CONTAIN <SPACE>. RETRY.");
            delay(1);
            goto redouser;
        }
    }while(pw[i-1]!='\r');
    pw[i-1]='\0';
    if(strlen(pw)<8)
    {
        printf("\n\t\tWARNING : ENTER MINIMUM OF 8 CHARACTERS. RETRY.");
        delay(1);
        goto redouser;
    }
    printf("\n\n\t\tCONFIRM USERNAME & PASSWORD? \n\n\t\tENTER 'Y' TO CONFIRM. ENTER ANY OTHER KEY TO EXIT. ");
    c=getch();
    if(c!='Y' && c!='y'){
        printf("\n\t\tMESSAGE : RETURNING TO MENU...");
        delay(1);
        startup();
    }
    else
    {
        fptr = fopen(dir, "r");
        if(fptr == NULL)
        {
            printf("\n\n\t\tUNABLE TO LOGIN. RETURNING TO HOMEPAGE...");
            startup();
        }
        fscanf(fptr,"%s", &num);
        delay(1);
        if(strcmp(num,pw)!=0)
        {
            printf("\n\t\tWARNING : WRONG PASSWORD. RETRY.");
            delay(1);
            goto redouser;
        }
        fclose(fptr);
        system("cls");
        printf("\n\t\t******************************");
        printf("\n\t\t*\t\t\t     *");
        printf("\n\t\t*\t WELCOME BACK!\t     *");
        printf("\n\t\t*\t\t\t     *");
        printf("\n\t\t******************************");
        delay(1);
        mainmenu(user,pw);
    }
}

void mainmenu(char user[20],char pw[20]){
    char choice;
    check=0;
    while(1)
    {
    system("cls");
    printf("\n\t\t WELCOME, %s.\n",user);
    printf("\n\t\t**************************************************");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t*\t CHOOSE OPTION:   \t\t\t *");
    printf("\n\t\t*\t*********************************\t *");
    printf("\n\t\t*\t*\t\t\t\t*\t *");
    printf("\n\t\t*\t* 1. BOOK NEW TICKETS\t\t*\t *");
    printf("\n\t\t*\t* 2. CANCEL BOOKED TRIPS\t*\t *");
    printf("\n\t\t*\t* 3. CHECK  UPCOMING TRAVELS\t*\t *");
    printf("\n\t\t*\t* 4. LOGOUT\t\t        *\t *");
    printf("\n\t\t*\t*\t\t\t\t*\t *");
    printf("\n\t\t*\t*********************************\t *");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t**************************************************");
    choice=getch();
    switch(choice)
    {
        case '1':
            newbooking(user,pw);
            break;
        case '2':
            cancelbooking(user,pw);
            break;
        case '3':
            check_upcoming(user,pw);
            break;
        case '4':
            system("cls");
            printf("\n\t\t******************************");
            printf("\n\t\t*\t\t\t     *");
            printf("\n\t\t*\t THANK YOU FOR\t     *");
            printf("\n\t\t*\tUSING OUR SERVICE    *");
            printf("\n\t\t*\t\t\t     *");
            printf("\n\t\t******************************");
            {
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);
                printf("\n\n\n\t\tDate: %d-%02d-%02d \n\t\tTime: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
            }
            delay(1);
            return;
        default:
            printf("\n\n\t\tWARNING : INVALID INPUT. TRY AGAIN.");
            delay(1);
    }
    }
}

void signup(){
    char user[20],pw[20],c;
    char dir[100]="./airlines dbs/";
    int len,ch,i;
    FILE *fptr;
    redouser:
    strcpy(dir,"./airlines dbs/");
    ch=0;
    system("cls");
    printf("\n\t\t****************************");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t*\t SIGN UP\t   *");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t****************************");
    printf("\n\n\t\tNOTE : USERNAME SHOULD BE YOUR PASSPORT NUMBER.\n\t\t [ONLY NUMBERS AND ALPHABETS WITHOUT SPACE]");
    printf("\n\n\t\tUSERNAME : ");
    scanf("\n");
    scanf("%s",&user);
    len=strlen(user);
    if(len>16 || len<6)
    {
        printf("\n\t\tWARNING : USERNAME DOES NOT FOLLOW CONDITIONS. RETRY.");
        delay(1);
        goto redouser;
    }
    for(i=0;i<len;i++)
    {
        if(isalnum(user[i])==0)
            ch++;
    }
    if(ch!=0)
    {
        printf("\n\t\tWARNING : USERNAME DOES NOT FOLLOW CONDITIONS. RETRY.");
        delay(1);
        goto redouser;
    }
    strcat(dir,user);
    strcat(dir,".txt");
    if(cfileexists(dir)==1)
    {
        printf("\n\t\tWARNING : USERNAME ALREADY EXISTS. RETRY");
        delay(1);
        goto redouser;
    }
    printf("\t\tPASSWORD: ");
    i=0;
    do{
        pw[i]=getch();
        if(pw[i]!='\r' && pw[i]!='\b'){
            printf("*");
        }
        if(pw[i]=='\b' &&  i>0)
        {
            printf("\b \b");
            i--;
        }
        else
         i++;
        if(i>16)
        {
            printf("\n\t\tWARNING: EXCEEDED 16 CHARACTERS. RETRY.");
            delay(1);
            goto redouser;
        }
        else if(i==1 && pw[i-1]=='\r')
        {
            printf("\n\t\tWARNING: ENTER MINIMUM OF 8 CHARACTERS. RETRY.");
            delay(1);
            goto redouser;
        }
        if(pw[i-1]==' ')
        {
            printf("\n\t\tWARNING: PASSWORD SHOULD NOT CONTAIN <SPACE>. RETRY.");
            delay(1);
            goto redouser;
        }
    }while(pw[i-1]!='\r');
    pw[i-1]='\0';
    if(strlen(pw)<8)
    {
        printf("\n\t\tWARNING: ENTER MINIMUM OF 8 CHARACTERS. RETRY.");
        delay(1);
        goto redouser;
    }
    printf("\n\n\t\tCONFIRM USERNAME & PASSWORD?\n\t\t(ENTER 'Y' TO CONFIRM. ENTER ANY OTHER KEY TO EXIT.) ");
    c=getch();
    if(c!='Y' && c!='y'){
        printf("\n\t\tMESSAGE: RETURNING TO MENU...");
        delay(1);
        startup();
    }
    else
    {
        fptr = fopen(dir, "w");
        if(fptr == NULL)
        {
            printf("\n\n\t\tUNABLE TO CREATE ACCOUNT. RETURNING TO HOMEPAGE...");
            startup();
        }
        fputs(pw, fptr);
        fclose(fptr);
        system("cls");
        printf("\n\t\t******************************");
        printf("\n\t\t*\t\t\t     *");
        printf("\n\t\t*\t THANK YOU FOR\t     *");
        printf("\n\t\t*\t  SIGNING UP\t     *");
        printf("\n\t\t*\t\t\t     *");
        printf("\n\t\t******************************");
        delay(3);
        mainmenu(user,pw);
    }
}

void shutdown(){
    FILE *file;
    file = fopen("./airlines dbs/flights/PNRdata.txt","w");
    fprintf(file,"%lld",cPNR);
    fclose(file);
    file = fopen("./airlines dbs/flights/f0.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[0].first,flights[0].business,flights[0].econA,flights[0].econB,flights[0].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f1.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[1].first,flights[1].business,flights[1].econA,flights[1].econB,flights[1].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f2.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[2].first,flights[2].business,flights[2].econA,flights[2].econB,flights[2].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f3.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[3].first,flights[3].business,flights[3].econA,flights[3].econB,flights[3].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f4.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[4].first,flights[4].business,flights[4].econA,flights[4].econB,flights[4].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f5.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[5].first,flights[5].business,flights[5].econA,flights[5].econB,flights[5].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f6.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[6].first,flights[6].business,flights[6].econA,flights[6].econB,flights[6].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f7.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[7].first,flights[7].business,flights[7].econA,flights[7].econB,flights[7].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f8.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[8].first,flights[8].business,flights[8].econA,flights[8].econB,flights[8].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f9.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[9].first,flights[9].business,flights[9].econA,flights[9].econB,flights[9].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f10.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[10].first,flights[10].business,flights[10].econA,flights[10].econB,flights[10].econC);
    fclose(file);
    file = fopen("./airlines dbs/flights/f11.txt","w");
    fprintf(file,"%d %d %d %d %d\n",flights[11].first,flights[11].business,flights[11].econA,flights[11].econB,flights[11].econC);
    fclose(file);
    system("cls");
    printf("\n\t\t******************************");
    printf("\n\t\t*\t\t\t     *");
    printf("\n\t\t*\t THANK YOU FOR\t     *");
    printf("\n\t\t*\tUSING OUR SERVICE    *");
    printf("\n\t\t*\t\t\t     *");
    printf("\n\t\t******************************");
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("\n\n\n\t\tDate: %d-%02d-%02d \n\t\tTime: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    delay(3);
}

void startup(){
    char choice;
    system("cls");
    system("color 30");
    printf("\n\t\t**********************************************************");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t   WELCOME TO ALL INDIA AIRWAYS SERVICE\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t YOU CAN BOOK TICKETS TO YOUR\t                 *");
    printf("\n\t\t*\t PREFFERED DESTINATION WITHOUT WORRYING ABOUT    *");
    printf("\n\t\t*\t SAFETY AND SECURITY. THE DATA ABOUT             *");
    printf("\n\t\t*\t YOUR TRAVELS IS SECURED IN YOUR                 *");
    printf("\n\t\t*\t PERSONAL PASSENGER ACCOUNT.                     *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t*\t\t\t\t\t\t         *");
    printf("\n\t\t**********************************************************");
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("\n\n\n\t\tDate: %d-%02d-%02d \n\t\tTime: %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    printf("\n\n\t\tPRESS ANY KEY TO CONTINUE... "); getch();
    while(1)
    {
        system("cls");
        printf("\n\t\t**************************************************");
        printf("\n\t\t*\t\t\t\t\t\t *");
        printf("\n\t\t*\t\t\t\t\t\t *");
        printf("\n\t\t*\t CHOOSE YOUR OPTION\t\t\t *");
        printf("\n\t\t*\t*********************************\t *");
        printf("\n\t\t*\t*\t\t\t\t*\t *");
        printf("\n\t\t*\t* 1. LOGIN TO EXISTING ACCOUNT\t*\t *");
        printf("\n\t\t*\t* 2. CREATE NEW ACCOUNT\t        *\t *");
        printf("\n\t\t*\t* 3. EXIT\t                *\t *");
        printf("\n\t\t*\t*\t\t\t\t*\t *");
        printf("\n\t\t*\t*********************************\t *");
        printf("\n\t\t*\t\t\t\t\t\t *");
        printf("\n\t\t**************************************************");
        choice=getch();
        switch(choice)
        {
            case '1': login();
                      break;
            case '2': signup();
                      break;
            case '3': shutdown();
                      exit(0);
            default : printf("\n\t\tWARNING : INVALID INPUT. TRY AGAIN\n");
                      delay(1);
        }
    }
}

int* search(char user[20],char pw[20],int c){
    int choice,origin,dest,n_flights,i,*First,*index=malloc(3*sizeof(int));
    char option,ch;
    if(c==0){
        redo_origin :
        system("cls");
        printf("\n\t\t****************************");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t*\t NEW BOOKING\t   *");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t****************************");
        printf("\n\n\t\t NOTE : CHOOSE WHERE YOU WISH TO TRAVEL FROM.\n");
        display_airport();
        printf("\n\t\t CHOICE : ");
        scanf("%d",&choice);
        if(choice<=0 || choice>12){
            printf("\n\t\t WARNING : INVALID OPTION. RETRY.");
            delay(1);
            goto redo_origin;
        }
        origin=choice-1;
        redo_dest :
        system("cls");
        printf("\n\t\t****************************");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t*\t NEW BOOKING\t   *");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t****************************");
        printf("\n\n\t\t NOTE : CHOOSE YOUR DESTINATION.\n");
        display_airport();
        printf("\n\t\t CHOICE : ");
        scanf("%d",&choice);
        if(choice<=0 || choice>12){
            printf("\n\t\t WARNING : INVALID OPTION. RETRY.");
            delay(1);
            goto redo_dest;
        }
        dest=choice-1;
        First=search_flights(origin,dest,&n_flights);
        system("cls");
        printf("\n\t\t****************************");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t*\t NEW BOOKING\t   *");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t****************************");
        if(n_flights==0){
            printf("\n\t\t NOTE : NO DIRECT FLIGHTS FOUND");
            printf("\n\t\t NOTE : PRESS 'Y' TO VIEW FLIGHTS. PRESS ANY OTHER TO EXIT ");
            option=getch();
            if(option=='Y' || option=='y')
                search(user,pw,1);
            else{
                check=1;}
        }
        else{
            printf("\n");
            for(i=0;i<n_flights;i++){
                printf("\n\t\t %d. ",i+1);
                display_flights(*(First+i));
            }
            printf("\n");
        printf("\n\t\t NOTE : CHOOSE WHICH FLIGHT TO BOOK. ANY OTHER KEY TO EXIT.");
        option=getch();
        choice=option-'0';
        if(option<'1' || option>'9' || choice>n_flights || choice<0){
            printf("\n\t\t\t WARNING : INVALID INPUT. RETURNING TO MENU");
            check=1;
            delay(1);
        }
        else{
            choice=option-'0';
        system("cls");
        printf("\n\t\t****************************");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t*\tCONFIRM BOOKING\t   *");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t****************************");
        printf("\n\n\t\tROUTE:");
        printf("\n\t\t------");
        printf("\n\t\tAIRPORT \tTIME");
        printf("\n\t\t-------- \t----");
        display_route(*(First+choice-1));
        printf("\n\n\t\t NOTE : PRESS 'Y' TO CONFIRM BOOKING. PRESS ANY OTHER TO EXIT.");
        option=getch();
        if(option=='Y' || option=='y'){
            *index=origin;
            *(index+1)=dest;
            *(index+2)=*(First+choice-1);
            return index;
        }
        else{
            check=1;
        }
    }}}
    else if(c==1){
        redoview:
        system("cls");
        printf("\n\t\t WELCOME, %s.\n",user);
        system("cls");
        printf("\n\t\t****************************");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t*\t NEW BOOKING\t   *");
        printf("\n\t\t*\t\t\t   *");
        printf("\n\t\t****************************");
        printf("\n");
        for(i=0;i<12;i++){
            printf("\n\t\t%d. ",i+1);
            display_flights(i);
            printf("\n");
        }
        printf("\n\n\t\t CHOOSE FLIGHT : ");
        scanf("%d",&choice);
        if(choice<1 || choice>12){
            printf("\n\t\t NOTE : INVALID INPUT. RETRY.");
            goto redoview;
        }
        choice-=1;
        printf("\n\t\t NOTE : PRESS 1 TO VIEW ROUTE. 0 TO BOOK.");
        option=getch();
        if(option!='1' && option!='0'){
            printf("\n\t\t NOTE : INVALID INPUT. RETRY.");
            goto redoview;
        }
        else if(option=='1'){
            system("cls");
            printf("\n\t\t****************************");
            printf("\n\t\t*\t\t\t   *");
            printf("\n\t\t*\tVIEW ROUTE\t   *");
            printf("\n\t\t*\t\t\t   *");
            printf("\n\t\t****************************");
            printf("\n\n\t\tAIRPORT\t\tTIME");
            printf("\n\t\t--------\t----");
            display_route(choice);
            printf("\n\n\t\t NOTE : PRESS 1 TO BOOK, 0 TO GO BACK, ANY OTHER TO EXIT. ");
            ch=getch();
            if(ch=='1'){
                *index=flights[choice].dep_ar[0];
                *(index+1)=flights[choice].dep_ar[1];
                *(index+2)=choice;
                return index;
            }
            else if(ch=='0')
                goto redoview;
            else{
                check=1;}
        }
        else if(option=='0'){
            *index=flights[choice].dep_ar[0];
            *(index+1)=flights[choice].dep_ar[1];
            *(index+2)=choice;
            return index;
        }
    }
}

void database(){
    struct route *f1,*f2;
    //flight 1 - amritsar to chennai
    strcpy(flights[0].flight_name,"INDIGO");
    flights[0].dep_ar[0]=0;flights[0].dep_ar[1]=3;
    flights[0].flight_no=12674;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=0;
    flights[0].rt=f1;
    f1->time[0]=17;f1->time[1]=15;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=6;
    f1->next=f2;
    f2->time[0]=19;f2->time[1]=20;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=7;
    f2->next=f1;
    f1->time[0]=21;f1->time[1]=45;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=3;
    f1->next=f2;
    f2->time[0]=6;f2->time[1]=20;

    f2->next=NULL;
    flights[0].first=0;flights[0].business=0;flights[0].econA=0;flights[0].econB=0;flights[0].econC=0;

    //flight 2 - ahmedabad to delhi
    strcpy(flights[1].flight_name,"AIR INDIA");
    flights[1].dep_ar[0]=1;flights[1].dep_ar[1]=4;
    flights[1].flight_no=12676;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=1;
    flights[1].rt=f1;
    f1->time[0]=6;f1->time[1]=10;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=10;
    f1->next=f2;
    f2->time[0]=7;f2->time[1]=0;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=0;
    f2->next=f1;
    f1->time[0]=8;f1->time[1]=0;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=7;
    f1->next=f2;
    f2->time[0]=8;f2->time[1]=50;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=4;
    f2->next=f1;
    f1->time[0]=14;f1->time[1]=10;

    f1->next=NULL;
    flights[1].first=0;flights[1].business=0;flights[1].econA=0;flights[1].econB=0;flights[1].econC=0;

    //flight 3 - jaipur to kochi
    strcpy(flights[2].flight_name,"AIR INDIA EXPRESS");
    flights[2].dep_ar[0]=7;flights[2].dep_ar[1]=8;
    flights[2].flight_no=12678;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=7;
    flights[2].rt=f1;
    f1->time[0]=7;f1->time[1]=0;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=6;
    f1->next=f2;
    f2->time[0]=7;f2->time[1]=40;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=5;
    f2->next=f1;
    f1->time[0]=8;f1->time[1]=40;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=3;
    f1->next=f2;
    f2->time[0]=9;f2->time[1]=50;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=8;
    f2->next=f1;
    f1->time[0]=16;f1->time[1]=0;

    f1->next=NULL;
    flights[2].first=0;flights[2].business=0;flights[2].econA=0;flights[2].econB=0;flights[2].econC=0;

    //flight 4 - bangalore to mumbai
    strcpy(flights[3].flight_name,"SPICEJET");
    flights[3].dep_ar[0]=2;flights[3].dep_ar[1]=10;
    flights[3].flight_no=12680;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=2;
    flights[3].rt=f1;
    f1->time[0]=6;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=3;
    f1->next=f2;
    f2->time[0]=9;f2->time[1]=0;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=8;
    f2->next=f1;
    f1->time[0]=10;f1->time[1]=50;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=11;
    f1->next=f2;
    f2->time[0]=13;f2->time[1]=50;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=10;
    f2->next=f1;
    f1->time[0]=2;f1->time[1]=40;

    f1->next=NULL;
    flights[3].first=0;flights[3].business=0;flights[3].econA=0;flights[3].econB=0;flights[3].econC=0;

    //flight 5 - goa to pune
    strcpy(flights[4].flight_name,"GOAIR");
    flights[4].dep_ar[0]=5;flights[4].dep_ar[1]=11;
    flights[4].flight_no=12682;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=5;
    flights[4].rt=f1;
    f1->time[0]=5;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=6;
    f1->next=f2;
    f2->time[0]=7;f2->time[1]=10;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=9;
    f2->next=f1;
    f1->time[0]=8;f1->time[1]=50;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=1;
    f1->next=f2;
    f2->time[0]=10;f2->time[1]=20;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=11;
    f2->next=f1;
    f1->time[0]=16;f1->time[1]=10;

    f1->next=NULL;
    flights[4].first=0;flights[4].business=0;flights[4].econA=0;flights[4].econB=0;flights[4].econC=0;

    //flight 6 - hyderabad to lucknow
    strcpy(flights[5].flight_name,"AIR ASIA INDIA");
    flights[5].dep_ar[0]=6;flights[5].dep_ar[1]=9;
    flights[5].flight_no=12684;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=6;
    flights[5].rt=f1;
    f1->time[0]=6;f1->time[1]=40;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=4;
    f1->next=f2;
    f2->time[0]=7;f2->time[1]=50;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=0;
    f2->next=f1;
    f1->time[0]=10;f1->time[1]=0;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=1;
    f1->next=f2;
    f2->time[0]=12;f2->time[1]=20;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=9;
    f2->next=f1;
    f1->time[0]=15;f1->time[1]=30;

    f1->next=NULL;
    flights[5].first=0;flights[5].business=0;flights[5].econA=0;flights[5].econB=0;flights[5].econC=0;

    //flight 7 - chennai to bangalore
    strcpy(flights[6].flight_name,"JET AIRWAYS");
    flights[6].dep_ar[0]=3;flights[6].dep_ar[1]=2;
    flights[6].flight_no=12686;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=3;
    flights[6].rt=f1;
    f1->time[0]=6;f1->time[1]=50;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=8;
    f1->next=f2;
    f2->time[0]=9;f2->time[1]=10;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=7;
    f2->next=f1;
    f1->time[0]=10;f1->time[1]=25;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=5;
    f1->next=f2;
    f2->time[0]=11;f2->time[1]=0;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=2;
    f2->next=f1;
    f1->time[0]=19;f1->time[1]=45;

    f1->next=NULL;
    flights[6].first=0;flights[6].business=0;flights[6].econA=0;flights[6].econB=0;flights[6].econC=0;

    //flight 8 - delhi to jaipur
    strcpy(flights[7].flight_name,"ZOOM AIR");
    flights[7].dep_ar[0]=4;flights[7].dep_ar[1]=7;
    flights[7].flight_no=12688;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=4;
    flights[7].rt=f1;
    f1->time[0]=14;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=6;
    f1->next=f2;
    f2->time[0]=15;f2->time[1]=50;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=9;
    f2->next=f1;
    f1->time[0]=16;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=11;
    f1->next=f2;
    f2->time[0]=17;f2->time[1]=30;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=7;
    f2->next=f1;
    f1->time[0]=22;f1->time[1]=20;

    f1->next=NULL;
    flights[7].first=0;flights[7].business=0;flights[7].econA=0;flights[7].econB=0;flights[7].econC=0;

    //flight 9 - kochi to amritsar
    strcpy(flights[8].flight_name,"STAR AIR");
    flights[8].dep_ar[0]=8;flights[8].dep_ar[1]=0;
    flights[8].flight_no=12690;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=8;
    flights[8].rt=f1;
    f1->time[0]=16;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=3;
    f1->next=f2;
    f2->time[0]=17;f2->time[1]=10;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=5;
    f2->next=f1;
    f1->time[0]=18;f1->time[1]=40;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=1;
    f1->next=f2;
    f2->time[0]=20;f2->time[1]=10;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=0;
    f2->next=f1;
    f1->time[0]=1;f1->time[1]=30;

    f1->next=NULL;
    flights[8].first=0;flights[8].business=0;flights[8].econA=0;flights[8].econB=0;flights[8].econC=0;

    //flight 10 - mumbai to goa
    strcpy(flights[9].flight_name,"AIR CARNIVAL");
    flights[9].dep_ar[0]=10;flights[9].dep_ar[1]=5;
    flights[9].flight_no=12692;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=10;
    flights[9].rt=f1;
    f1->time[0]=3;f1->time[1]=10;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=11;
    f1->next=f2;
    f2->time[0]=4;f2->time[1]=20;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=4;
    f2->next=f1;
    f1->time[0]=5;f1->time[1]=40;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=3;
    f1->next=f2;
    f2->time[0]=7;f2->time[1]=20;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=5;
    f2->next=f1;
    f1->time[0]=1;f1->time[1]=0;

    f1->next=NULL;
    flights[9].first=0;flights[9].business=0;flights[9].econA=0;flights[9].econB=0;flights[9].econC=0;

    //flight 11 - pune to hyderabad
    strcpy(flights[10].flight_name,"AIR COSTA");
    flights[10].dep_ar[0]=11;flights[10].dep_ar[1]=6;
    flights[10].flight_no=12694;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=11;
    flights[10].rt=f1;
    f1->time[0]=15;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=0;
    f1->next=f2;
    f2->time[0]=17;f2->time[1]=30;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=9;
    f2->next=f1;
    f1->time[0]=18;f1->time[1]=30;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=4;
    f1->next=f2;
    f2->time[0]=20;f2->time[1]=20;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=6;
    f2->next=f1;
    f1->time[0]=3;f1->time[1]=30;

    f1->next=NULL;
    flights[10].first=0;flights[10].business=0;flights[10].econA=0;flights[10].econB=0;flights[10].econC=0;

    //flight 12 - lucknow to ahmedabad
    strcpy(flights[11].flight_name,"JET LITE");
    flights[11].dep_ar[0]=9;flights[11].dep_ar[1]=1;
    flights[11].flight_no=12696;
    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=9;
    flights[11].rt=f1;
    f1->time[0]=16;f1->time[1]=10;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=8;
    f1->next=f2;
    f2->time[0]=17;f2->time[1]=30;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=3;
    f2->next=f1;
    f1->time[0]=18;f1->time[1]=40;

    f2=(struct route*)malloc(sizeof(struct route));
    f2->loc=10;
    f1->next=f2;
    f2->time[0]=20;f2->time[1]=0;

    f1=(struct route*)malloc(sizeof(struct route));
    f1->loc=1;
    f2->next=f1;
    f1->time[0]=1;f1->time[1]=40;

    f1->next=NULL;
    flights[11].first=0;flights[11].business=0;flights[11].econA=0;flights[11].econB=0;flights[11].econC=0;
}

void cancelbooking(char user[20],char pw[20]){
    FILE *in,*out;
    char dir[100]="./airlines dbs/",ps[20],c,dir2[100];
    struct passenger p,r;
    int i=0,n,index;
    strcat(dir,user);strcat(dir,".txt");
    redoview:
    i=0;
    in = fopen(dir,"r");
    system("cls");
    printf("\n\t\t****************************");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t*\tCANCEL BOOKING\t   *");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t****************************");
    fscanf(in,"%s",&ps);
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d",&p.PNR,&p.flight_no,&p.dep_ar[0],&p.dep_ar[1],&p.flight_class,&p.seat_no);
        printf("\n\n\t\t%d. ",i+1);i++;
        printf("PNR         : %lld",p.PNR);
        printf("\n\t\t   FLIGHT NO.  : %d ",p.flight_no);
        printf("\n\t\t   FROM        : %s",airport[p.dep_ar[0]]);
        printf("\n\t\t   TO          : %s",airport[p.dep_ar[1]]);
        if(p.flight_class==1)
            printf("\n\t\t   FIRST CLASS");
        else if(p.flight_class==2)
            printf("\n\t\t   BUSINESS CLASS");
        else if(p.flight_class==3)
            printf("\n\t\t   ECONOMY A (WINDOW SEAT)");
        else if(p.flight_class==4)
            printf("\n\t\t   ECONOMY B (CENTRE SEAT)");
        else if(p.flight_class==5)
            printf("\n\t\t   ECONOMY C (AISLE SEAT)");
        printf("\n\t\t   SEAT NO.     : %d",p.seat_no);
        if(getc(in)==EOF)
            break;
    }
    fclose(in);
    if(i==0){
        printf("\n\n\t\t NOTE : NO BOOKING DONE. RETURNING TO MENU.");
        delay(1);
        mainmenu(user,pw);
    }
    else{
    printf("\n\n\t\t ENTER THE BOOKING THAT NEEDS TO BE CANCELLED : ");
    scanf("%d",&n);
    if(n>i || n<1){
        printf("\n\t\t NOTE : INVALID OPTION. RETRY.");
        delay(1);
        goto redoview;
    }
    else{
    printf("\n\t\t NOTE : PRESS 'Y' TO CONFIRM. ANY OTHER TO EXIT.");
    c=getch();
    if(c!='y' && c!='Y')
        mainmenu(user,pw);
    else{
    strcpy(dir,"./airlines dbs/");strcat(dir,"temp.txt");
    out = fopen(dir,"w");
    strcpy(dir,"./airlines dbs/");strcat(dir,user);strcat(dir,".txt");
    in = fopen(dir,"r");
    fscanf(in,"%s",&ps);
    fprintf(out,"%s",ps);
    i=0;
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d",&p.PNR,&p.flight_no,&p.dep_ar[0],&p.dep_ar[1],&p.flight_class,&p.seat_no);
        i++;
        if(i!=n){
            fprintf(out,"\n%lld %d %d %d %d %d",p.PNR,p.flight_no,p.dep_ar[0],p.dep_ar[1],p.flight_class,p.seat_no);
        }
        else if(i==n){
            index=(p.flight_no-12674)/2;
                if(p.flight_class==1)
                    flights[index].first-=1;
                else if(p.flight_class==2)
                    flights[index].business-=1;
                else if(p.flight_class==3)
                    flights[index].econA-=1;
                else if(p.flight_class==4)
                    flights[index].econB-=1;
                else if (p.flight_class==5);
                    flights[index].econC-=1;
                r=p;
            }
                }
            }
        }
    }
    fclose(in);
    fclose(out);
    strcpy(dir,"./airlines dbs/");strcat(dir,"temp.txt");
    strcpy(dir2,"./airlines dbs/");strcat(dir2,user);strcat(dir2,".txt");
    remove(dir2);
    rename(dir,dir2);

    printf("\n\t\t NOTE : SUCCESSFULLY CANCELLED BOOKING.");
    delay(1);
    mainmenu(user,pw);
    }

void newbooking(char user[20],char pw[20]){
    char ch,dir[100]="./airlines dbs/";
    struct passenger newp;
    int *index,c;
    FILE *file;
    retry:
    system("cls");
    printf("\n\t\t WELCOME, %s.\n",user);
    printf("\n\t\t**************************************************");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t*\t NEW BOOKING\t\t\t\t *");
    printf("\n\t\t*\t*********************************\t *");
    printf("\n\t\t*\t*\t\t\t\t*\t *");
    printf("\n\t\t*\t* 1. SEARCH BY LOCATION\t\t*\t *");
    printf("\n\t\t*\t* 2. SEARCH BY FLIGHTS\t\t*\t *");
    printf("\n\t\t*\t* 3. BACK TO MENU\t\t*\t *");
    printf("\n\t\t*\t*\t\t\t\t*\t *");
    printf("\n\t\t*\t*********************************\t *");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t**************************************************");
    printf("\n\t\tENTER YOUR CHOICE : ");
    scanf("%d",&c);
    switch(c)
    {
        case 1:
            index=search(user,pw,0);
            break;
        case 2:
            index=search(user,pw,1);
            break;
        case 3:
            return;
        default:
            printf("\n\n\t\tWARNING : INVALID INPUT. TRY AGAIN.");
            delay(1);
            goto retry;
            break;
    }
    if(check==0){
    redocpt:
    system("cls");
    printf("\n\t\t WELCOME, %s.\n",user);
    printf("\n\t\t**************************************************");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t*\t CHOOSE CLASS    \t\t\t *");
    printf("\n\t\t*\t*********************************\t *");
    printf("\n\t\t*\t*\t\t\t\t*\t *");
    printf("\n\t\t*\t* 1. FIRST CLASS\t\t*\t *");
    printf("\n\t\t*\t* 2. BUSINESS CLASS\t\t*\t *");
    printf("\n\t\t*\t* 3. ECONOMY CLASS WINDOW\t*\t *");
    printf("\n\t\t*\t* 4. ECONOMY CLASS CENTRE\t*\t *");
    printf("\n\t\t*\t* 5. ECONOMY CLASS AISLE \t*\t *");
    printf("\n\t\t*\t*\t\t\t\t*\t *");
    printf("\n\t\t*\t*********************************\t *");
    printf("\n\t\t*\t\t\t\t\t\t *");
    printf("\n\t\t**************************************************");
    printf("\n\t\tEnter your choice : ");
    scanf("%d",&c);
    switch(c)
    {
        case 1:
            if(flights[*(index+2)].first<60){
                newp.flight_class=1;
                newp.seat_no=flights[*(index+2)].first+1;
                flights[*(index+2)].first+=1;
            }
            else{
                printf("\n\t\t NOTE : PREFERRED CLASS NOT AVAILABLE.\n\t\t ENTER 'Y' TO RETRY.");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
                }
            break;

        case 2:
            if(flights[*(index+2)].business<60){
                newp.flight_class=2;
                newp.seat_no=flights[*(index+2)].business+1;
                flights[*(index+2)].business+=1;
            }
            else{
                printf("\n\t\t NOTE : PREFERRED CLASS NOT AVAILABLE.\n\t\t ENTER 'Y' TO RETRY. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
            }
            break;
        case 3:
            if(flights[*(index+2)].econA<60){
                newp.flight_class=3;
                newp.seat_no=flights[*(index+2)].econA+1;
                flights[*(index+2)].econA+=1;
            }
            else{
                printf("\n\t\t NOTE : PREFERRED CLASS NOT AVAILABLE.\n\t\t PRESS 'Y' TO RETRY. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
            }
            break;
        case 4:
            if(flights[*(index+2)].econB<60){
                newp.flight_class=4;
                newp.seat_no=flights[*(index+2)].econB+1;
                flights[*(index+2)].econB+=1;
            }
            else{
                printf("\n\t\t NOTE : PREFERRED CLASS NOT AVAILABLE.\n\t\t ENTER 'Y' TO RETRY. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
            }
            break;
        case 5:
            if(flights[*(index+2)].econC<60){
                newp.flight_class=5;
                newp.seat_no=flights[*(index+2)].econC+1;
                flights[*(index+2)].econC+=1;
            }
            else{
                printf("\n\t\t NOTE : PREFERRED CLASS NOT AVAILABLE.\n\t\t ENTER 'Y' TO RETRY. ");
                ch=getch();
                if(ch=='Y' || ch=='y')
                    goto redocpt;
            }
            break;
        default:
            printf("\n\n\t\tWARNING : INVALID INPUT. TRY AGAIN.");
            delay(1);
            goto redocpt;
            break;
    }
    newp.dep_ar[0]=*index;newp.dep_ar[1]=*(index+1);
    newp.PNR=cPNR++;
    newp.flight_no=flights[*(index+2)].flight_no;

    strcat(dir,user);strcat(dir,".txt");
    file = fopen(dir,"a");
    fprintf(file,"\n%lld %d %d %d %d %d",newp.PNR,newp.flight_no,newp.dep_ar[0],newp.dep_ar[1],newp.flight_class,newp.seat_no);
    fclose(file);

    printf("\n\t\tNOTE : SUCCESSFULLY BOOKED.");
    check=0;
    delay(1);
    }
    mainmenu(user,pw);
}

void check_upcoming(char user[20],char pw[20]){
    FILE *in;
    char dir[100]="./airlines dbs/",ps[20];
    struct passenger p;
    int i=0;
    strcat(dir,user);strcat(dir,".txt");
    in = fopen(dir,"r");
    system("cls");
    printf("\n\t\t****************************");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t*   UPCOMING TRAVELS\t   *");
    printf("\n\t\t*\t\t\t   *");
    printf("\n\t\t****************************");
    fscanf(in,"%s ",&ps);
    while(!feof(in)){
        fscanf(in,"%lld %d %d %d %d %d",&p.PNR,&p.flight_no,&p.dep_ar[0],&p.dep_ar[1],&p.flight_class,&p.seat_no);
        printf("\n\n\t\t%d. ",i+1);i++;
        printf("PNR         : %lld",p.PNR);
        printf("\n\t\t   FLIGHT NO.  : %d ",p.flight_no);
        printf("\n\t\t   FROM        : %s",airport[p.dep_ar[0]]);
        printf("\n\t\t   TO          : %s",airport[p.dep_ar[1]]);
        if(p.flight_class==1)
            printf("\n\t\t   FLIGHT CLASS : FIRST");
        else if(p.flight_class==2)
            printf("\n\t\t   FLIGHT CLASS : BUSINESS");
        else if(p.flight_class==3)
            printf("\n\t\t   FLIGHT CLASS : ECONOMY A (WINDOW SEAT)");
        else if(p.flight_class==4)
            printf("\n\t\t   FLIGHT CLASS : ECONOMY B (CENTRE SEAT)");
        else if(p.flight_class==5)
            printf("\n\t\t   FLIGHT CLASS : ECONOMY C (AISLE SEAT)");
        printf("\n\t\t   SEAT NO.     : %d",p.seat_no);
        printf("\n\t\t   STATUS      : CONFIRMED");
        if(getc(in)==EOF)
            break;
    }
    fclose(in);
    if(i==0){
        printf("\n\n\t\t NOTE : NO BOOKING DONE. RETURNING TO MENU.");
        delay(1);
        mainmenu(user,pw);
    }
    else{
        printf("\n\n\t\t NOTE : PRESS ANY KEY TO RETURN.");
        getch();
        mainmenu(user,pw);
    }
}
