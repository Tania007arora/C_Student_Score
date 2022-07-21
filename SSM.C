/*
* STUDENT SCORE MANAGEMENT SYSTEM (SSM)
* author:Tania Arora
* roll number -36888
*/
#include <stdio.h>
#include <string.h>  
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <ctype.h>
//global varisables
int nsubject=0; //total number of subjects
int nstud=0;   //total number of students
char loginkey[]="aHjd84KlkP";
struct student{
			char student_name[100];
			int student_roll;
			float subject[10];
			float percentage;
			char enter_key[2];
			int position;
		};
//Function declarations
void intro();
float percentage(float [],int);  
void position(struct student []);
void print_report(struct student [],char [] ,char subject_names[][5],char []);                                                                                                                     
void position_count(struct student []);
int read(char row[][16],struct student [] ,char [],int);
void print_file(struct student [],int,int);
void print_record(struct student ,int );
int roll_check(struct student [],int,int);
int main(){
	SetConsoleTitle("SCORE MANAGEMENT"); //setting console title
	char key[11];
	printf("Enter the login key\n=>");  //login check
	scanf("%s",key);
	if(strcmp(key,loginkey)==0){ //authentication
	fflush(stdin);
	system("cls");
	//declarations
	int total_marks;
	char path[400];
	char filename[30];
	int option;
	char end;
	menubasic:intro();
	//mainmenu starts
	printf("\n\n\nKindly chose which operation you want to perform from following options-\n1)Create new report of students which will include position and percentage.\n2)Update existing report of students.\n=>");
	enter:scanf("%d",&option);
	if(option==1){
		//entering data into file
		printf("\t\t\t\t*****Default structure of file input is: Student Name ,Student Roll No., Subjects *****\n\n");
		printf("Kindly enter required information.\n");
		printf("Kindly enter total number of subjects\n=>");
		scanf("%d",&nsubject);   
		//Taking subject names as input
		char subject_names[nsubject][5];
		printf("Kindly enter a subject code(<=5) for %d subjects\n",nsubject);
		int sname;
	    	for(sname=0;sname<nsubject;sname++){
	    		subject:printf("Subject code of subject %d\n=>",sname+1);
	    		scanf("%s", subject_names[sname]);
				if(strlen(subject_names[sname])>5){
					MessageBox(0,"Subject code is greater than 5.","ERROR",MB_ICONERROR);  //error handling
					printf("Kindly enter subject code with length <5.\n ");
					goto subject;
				}
	    	}
		printf("Kindly enter Total Marks.\n=>");
		scanf("%d",&total_marks);
		printf("Kindly enter total number of students\n=>");
		scanf("%d",&nstud); 
		printf("Kindly give path to store Report.Eg-\\C:\\Users\\personal\\ \n=>"); 
		scanf("%s",path);
		printf("*****Kindly enter %d students information*****\n\n\n",nstud);
		struct student s[nstud];
		int i;
		for(i=0;i<nstud;i++){
			printf("\tEnter Student's Information. S.No.-%d\n",i+1);
			printf("Enter name=>");
			gets(s[i].enter_key);
			gets(s[i].student_name);
			here:printf("Roll number=>");
			scanf("%d",&s[i].student_roll);
			int check=roll_check(s,s[i].student_roll,i+1);  //To check uniqueness of roll number
			if(check==0){	
				printf("Roll number should be unique\n");
				MessageBox(0,"Roll number already exist.","ERROR",MB_ICONERROR);  //to show error dialog box
				goto here;
			}
			int j;
			for(j=0;j<nsubject;j++){ 
				printf("Enter subject marks for %s =>",subject_names[j]);							
				scanf("%f",&s[i].subject[j]);
				printf("\n");
			}
	
			//calling function to calculate percentage
			s[i].percentage=percentage(s[i].subject,total_marks);
			printf(" Percentage final output %.2f\n",s[i].percentage);

		}
	
		//to sort data of students
		position(s);
		//finding position of every student.
		position_count(s);	
		printf("Kindly enter the file name.Eg-student_report.csv \n=>");
		getchar();
		gets(filename);
		print_report(s,path,subject_names,filename);
		printf("\t*****Report has been generated and placed at path mentioned -%s  *****",path);
		MessageBox(0,"Report has been generated","SCORE",MB_ICONASTERISK);	
		printf("\n*****Press X to exit or any other key to go back to MENU.*****\n=>");
		scanf("%c",&end);
		if(end=='X'||end=='x'){
			exit(1);
		}
		else{
			system("cls");
			goto menubasic;
		}
	}
	else if(option==2){
		int nsub,lines,i,j,k,optmen,roll,rollposition=-1,total_marks,newstudent;
		char filename[2]="";
		printf("*****File must include columns - Student Name , Student roll number , Subjects , Percentage , Position*****\n\n");
		printf("Enter the complete path including file name which you want to update.Eg-C:\\Users\\personal\\report.csv .\n=>");
		scanf("%s",path);
		printf("Enter total number of subjects in report\n=>");
		scanf("%d",&nsub);
		printf("Enter total marks\n=>");
		scanf("%d",&total_marks);
		nsubject=nsub;	//global variable number of subjects updated
		printf("\n");
		struct student sf[100];
		char row1 [4+nsub][16];
		char subject_names[nsub][5];
		lines=read(row1,sf,path,nsub);
		nstud=lines;
		for(k=0;k<nsub;k++){
			strcpy(subject_names[k],row1[2+k]);
		}
			//printing file data
		printf("Below is the student report\n\n");
		print_file(sf,lines,nsub);
		//submenu
		menuopr:printf("\nChoose one operation you would like to perform on the report\n1.Insert new student data.\n2.Delete data of student.\n3.Update a student data using roll number.\n=>");
		scanf("%d",&optmen);
		if(optmen==1){
			printf("Enter number of new students that will be inserted\n=>");
			scanf("%d",&newstudent);
			nstud=nstud+newstudent;
			//taking input
			for(i=0;i<newstudent;i++){
			printf("Enter Student's Information. S.No.-%d",i+1);
			printf("Enter name=>");
			gets(sf[lines+i].enter_key);
			gets(sf[lines+i].student_name);
			here1:printf("Roll number=>");
			scanf("%d",&sf[lines+i].student_roll);
			int check=roll_check(sf,sf[lines+i].student_roll,lines+i+1); //checking uniqueness of roll number
			if(check==0){
				MessageBox(0,"Roll number already exist.","ERROR",MB_ICONERROR);
				printf("\nRoll number should be unique\n");
				goto here1;
			}
			int j;
			for(j=0;j<nsubject;j++){ 
				printf("Enter subject marks for %s =>",subject_names[j]);							
				scanf("%f",&sf[lines+i].subject[j]);
				printf("\n");
			}
			//formula for percentage
			sf[lines+i].percentage=percentage(sf[lines+i].subject,total_marks);
			printf(" percentage final output %.2f\n",sf[lines+i].percentage);
		
		}	
		position(sf);
		position_count(sf);  //again finding positions
		print_report(sf,path,subject_names,filename);
		printf("Updated file has been placed at same path i.e.-%s",path);
		MessageBox(0,"Report has been generated","SCORE",MB_ICONASTERISK);	

		}
		else if(optmen==2){
			rollagain:printf("Enter roll number of student for which you want to remove data.\n=>");
			scanf("%d",&roll);
			for(i=0;i<lines;i++){
				if(sf[i].student_roll==roll){
					rollposition=i;
					break;
					
				}
			} //roll number should exist in list
			if(rollposition==-1){
				MessageBox(0,"Roll number doesn't exist in list.","ERROR",MB_ICONERROR);
				printf("Roll number doesn't exist in list.");
				goto rollagain;
			}
			printf("Below data will be deleted from the report\n");
			print_record(sf[rollposition],nsub);
			system("pause");
			nstud=lines-1;
			struct student sd[lines-1]; //creating new structure variable to store data without deleted row
			int count=0;
			for(i=0;i<lines-1;i++){
				if(i==rollposition){
					count++;
				}
				sd[i]=sf[count];
				count++;
				
			}
			position(sd);
			position_count(sd);
			print_report(sd,path,subject_names,filename);
			printf("*****Updated file has been placed at same path i.e.-%s.Positions are also updated.*****",path);
			MessageBox(0,"Report has been generated","SCORE",MB_ICONASTERISK);	
		}
		else if(optmen==3){ //updating data
			rollagain3:printf("Enter student's' roll number whose data you want to update\n=>");
			scanf("%d",&roll);
			for(i=0;i<lines;i++){
				if(sf[i].student_roll==roll){
					rollposition=i;
					break;
					
				}
			} //roll number should exist in list
			if(rollposition==-1){
				MessageBox(0,"Roll number doesn't exist in list.","ERROR",MB_ICONERROR);
				printf("Roll number doesn't exist in list.\n");
				goto rollagain3;
			}
			
		
		print_record(sf[rollposition],nsub);
		printf("Enter student name that will be updated\n=>");
		gets(sf[rollposition].enter_key);
		gets(sf[rollposition].student_name);
		printf("Enter updated marks for %d subjects in the same order \n=>",nsub);
		for(j=0;j<nsub;j++){
			scanf("%f",&sf[rollposition].subject[j]);
		}

		sf[rollposition].percentage=percentage(sf[rollposition].subject,total_marks);
		position(sf);
		position_count(sf);
		print_report(sf,path,subject_names,filename);
		printf("Updated file has been placed at same path i.e.-%s",path);
		MessageBox(0,"Report has been generated","SCORE",MB_ICONASTERISK);	
	}
	else{
		fflush(stdin); //to clear input from buffer
		MessageBox(0,"Wrong option selected","ERROR",MB_ICONERROR);
		printf("\nOption doesnot exist\n");
		printf("Please select options from 1-3.\n");
		goto menuopr; 
	}
	printf("\n*****Press X to exit or any key to go back to MENU.*****\n");
		scanf("%*c%c",&end); 
		if(end=='X'||end=='x'){
			exit(1);
		}
		else{
			system("cls");
			goto menubasic;
		}
	}
	else{
		fflush(stdin); //to clear input buffer
		MessageBox(0,"Wrong option selected","ERROR",MB_ICONERROR);
		printf("\nOption doesnot exist\n");
		printf("Please select options from 1-2.\n");
		system("cls");
		goto menubasic;
	}
}
else{
	printf("\nAuthentication failed\n");
	exit(1);
}
return 0;
}

//FUNCTIONS Definitaion

float percentage(float subjects[],int total_marks){
	int j;
	int i; float perg,sum=0.0;
	for(i=0;i<nsubject;i++){
		
		sum=sum+subjects[i];
	}
	perg=(sum/total_marks)*100;
	return perg;
	
}

void position(struct student s[]){
		int i,j,y;
		struct student temp;
		
		for(i=0;i<nstud;i++){
			for(j=i+1;j<nstud;j++){
				if(s[i].percentage<=s[j].percentage){
					temp=s[i];
					s[i]=s[j];
					s[j]=temp;
				}
			}
		}
		
	}

void position_count(struct student s[]){ //updating position on new percentage
		int i,count =1;
		s[0].position=count;
		for(i=1;i<nstud;i++){
			
				if(s[i].percentage==s[i-1].percentage)
					count=count;
				else
					count++;
				s[i].position=count;	
				}
	}
	
void print_report(struct student s[],char path[], char subject_names[][5],char filename[] ){	
	int i;
	FILE *studentreportPtr;
	 strcat(path,filename);
	 
	studentreportPtr=fopen(path,"w"); //creating a new file at given path
	if(studentreportPtr==NULL){
		printf("File couldn't be opened.Kindly check path entered again.");  //error handling
		exit(1); 
	}
	//printing data in formatted form
	fprintf(studentreportPtr,"STUDENT_NAME,STUDENT_ROLL_NUMBER");
	int sname;
	for(sname=0;sname<nsubject;sname++){
		fprintf(studentreportPtr,",%s",subject_names[sname]);
	}
	fprintf(studentreportPtr,",STUDENT_PERCENTAGE,STUDENT_POSITION\n");
	
	for(i=0;i<nstud;i++){
		
		fprintf(studentreportPtr,"%s,%d",s[i].student_name,s[i].student_roll);
		int smarks;
		for(smarks=0;smarks<nsubject;smarks++){
			fprintf(studentreportPtr,",%f",s[i].subject[smarks]);
		}
		fprintf(studentreportPtr,",%.2f,%d\n",s[i].percentage,s[i].position);
	}
	fclose(studentreportPtr);
		
	}

int read(char row1[][16],struct student s [], char path[],int nsub){
	
	int newline=0;
	FILE *readptr;
	readptr=fopen(path,"r+");
	if(readptr==NULL){
		system("cls");
		MessageBox(0,"File couldn't be opened.Kindly check path entered again.Re running the program.","ERROR",MB_ICONASTERISK);
		printf("\t*****File couldn't be opened.Kindly check path entered again.Re running the program*****\n\n\n");
		main();
	}
	char strin[20]="";
	char empt[20]="";
	int i=0,a;
	char ch[1];
	while((ch[0]=fgetc(readptr))!='\n'){
		//take input and append 1st row in above variables
		if(ch[0]==','){
			ch[0]=empt[0];
			strcpy(row1[i],strin);
			strcpy(strin,empt);
			i++;
		}
		strcat(strin,ch);
	}
		strcpy(row1[3+nsub],"STUDENT_POSITION");
		strcpy(strin,empt);
	int j=0,commacount=0,lines=0;
	//Inputting data of students
	while((ch[0]=fgetc(readptr))!=EOF){
		if(ch[0]==','||ch[0]=='\n'){
			if(ch[0]==','){
				commacount++;
				ch[0]=empt[0]; //to remove , rom getting concatenated in strin.
			if(commacount<=3+nsub&&commacount>0){
				if(commacount==1){
					strcpy(s[j].student_name,strin);
					strcpy(strin,empt);
				}
				else if(commacount==2){
					s[j].student_roll=atoi(strin);
					strcpy(strin,empt);
				}
				else if(commacount==3+nsub){
					s[j].percentage=atof(strin);
					strcpy(strin,empt);
				}
				else if(commacount>=3&&commacount<=2+nsub){
					s[j].subject[commacount-3]=atof(strin);
					strcpy(strin,empt);
				}
			}
			else{
				//if wrong number of subjects mentioned or format is wrong
				printf("File format not correct.Please contact administerator/developer");
				exit(1);
			} }
			if(ch[0]=='\n'){  //reading new line
				ch[0]=empt[0];
				s[j].position=atoi(strin);
				strcpy(strin,empt);
				commacount=0;
				lines++;
				j++;
			}
		}
		
		strcat(strin,ch);
	}
	return lines;
}
//to print complete output on terminal
void print_file(struct student s [],int lines,int nsub){
	int i,j,k;
	for(i=0;i<lines;i++){
			printf("\t%-30s\t %-10d\t",s[i].student_name,s[i].student_roll);
			for(j=0;j<nsub;j++){
				printf("%-5.2f\t",s[i].subject[j]);
			}
			printf("%-5.2f\t%-5d\n",s[i].percentage,s[i].position);
			printf("\t");
			for(k=0;k<(75+nsub*5);k++){
				printf("-");
			}
			printf("\n");
		}
	
}	
//to print single record
void print_record(struct student s,int nsub){
	int i,j,k;
	
			printf("%s\t \t %d\t",s.student_name,s.student_roll);
			for(j=0;j<nsub;j++){
				printf("%.2f\t",s.subject[j]);
			}
			printf("%.2f\t%d\n",s.percentage,s.position);
			
			
		
	
}
//unique roll number check error handling
int roll_check(struct student s[],int rnumber,int lines){
	int check=1;
	int i;
	for(i=0;i<lines-1;i++){
		if(s[i].student_roll==rnumber){
			check=0;
			break;
		}
	}
			return check;

}

void intro(){
		printf("\t\t\t\t\t\t");
	int l;
	for(l=0;l<37;l++){
		printf("-");
	}
	printf("\n\t\t\t\t\t\t");
	for(l=0;l<37;l++){
		printf("-");
	}
	printf("\n\t\t\t\t\t\t|| STUDENT SCORE MANAGEMENT SYSTEM || \t\t\t\t\n");
	printf("\n\t\t\t\t\t\t NAME-TANIA ARORA\n");
	printf("\n\t\t\t\t\t\t CLASS-MCA(1st SEM EVENING)\n");
	printf("\n\t\t\t\t\t\t ROLL NUMBER-93\n");
	printf("\t\t\t\t\t\t");
	for(l=0;l<37;l++){
		printf("-");
	}
	printf("\n\t\t\t\t\t\t");
	for(l=0;l<37;l++){
		printf("-");
	}
}	
//end of code
