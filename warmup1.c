#include<stdlib.h> 
#include"my402list.h" 
#include<stdio.h> 
#include<sys/time.h>
#include<errno.h>
#include<time.h>
#include<string.h> 
#include<sys/stat.h>
typedef struct data
{
	char ttype;
	int ttime;
	int dollar;
	char tdesc[24];
}data;
data *nit1,*nit2,*nit3,*nit4,*nit5,*nit6,*obj1,*temp;
My402ListElem *smallest,*elem1,*elem2,*elem3,*elem4,*elem5;
int i,j,l,m,len,p,n,o,q,s,leng,balleng,shft,balshft,t,u,v,w,x,y,z,length,balance,current_time;
float previous;
char buf[1024],tbuf[15],amtdollarbuf[20],amtcentbuf[10],descbuf[25],*start_ptr,*tab_ptr,*timearr,output[15],bal[14];
FILE* fp = NULL;
time_t transtime;
 
 	
//--------------------------sort function------------------------------------------
static void sort(My402List *anc)
{
	
	elem1=My402ListFirst(anc);
	len=My402ListLength(anc);
	
	for(m=0;m<len-1;m++)
	{
		smallest=elem1;
		elem2=My402ListNext(anc,elem1);
		while(elem2 != &(anc->anchor))
		{
		
			nit1=(data *)smallest->obj;
			nit2=(data *)elem2->obj;
			if(nit1->ttime > nit2->ttime)
			{
				temp=nit1;
				nit1=nit2;
				nit2=temp;
				smallest->obj=nit1;
				elem2->obj=nit2;	
				
			}
		
			elem2 = elem2->next;
	
		}
	
	
		elem3=My402ListFirst(anc);
		nit3=(data *)elem3->obj;
	
		elem1=elem1->next;
	}
	elem3=My402ListFirst(anc);
	elem5=elem3->next;
	while(elem5 != &(anc->anchor))
	{
		nit3=(data *)elem3->obj;
		nit6=(data *)elem5->obj;
		if(nit3->ttime == nit6->ttime)
		{
			fprintf(stdout,"\nTime Stamp Equal");
			exit(1);
		}
		elem3=elem3->next;
		elem5=elem5->next;
	}
}

//---------------------finction display----------------------------------

	void static display(My402List * anc)
	{	
	fprintf(stdout,"+-----------------+--------------------------+----------------+----------------+");
	fprintf(stdout,"\n|       Date      | Description              |         Amount |        Balance |");
	fprintf(stdout,"\n+-----------------+--------------------------+----------------+----------------+");
	
	
	elem4=My402ListFirst(anc);
	
	while(elem4 != &(anc->anchor))
	{
		nit4=(data *)elem4->obj;
		
		transtime=(time_t)nit4->ttime;
		timearr=ctime(&transtime);
		*(timearr+11)=*(timearr+20);
		*(timearr+12)=*(timearr+21);
		*(timearr+13)=*(timearr+22);
		*(timearr+14)=*(timearr+23);
		*(timearr+15)='\0';
		
		length=strlen(nit4->tdesc);
		for(t=length;t<24;t++)
		{
			nit4->tdesc[t]=' ';
		}		
			nit4->tdesc[24]='\0';
		
		memset(output,'\0',sizeof(output));
		
		sprintf(output,"%0.2f",(float)(nit4->dollar)/100);
		
		if(nit4->ttype == '+')
		{
			leng=strlen(output);
			if(leng == 3)
			{
				output[3]=' ';				
				output[4]=' ';
				output[5]=' ';
				output[6]=' ';
				output[7]=' ';
				output[8]=' ';
				output[9]=' ';
							
			}
			if(leng == 4)
			{
				output[4]=' ';
				output[5]=' ';
				output[6]=' ';
				output[7]=' ';
				output[8]=' ';
				
			}
			if(leng == 5)
			{
				output[5]=' ';
				output[6]=' ';
				output[7]=' ';
			}
			if(leng == 6)
			{
				output[6]=' ';
			}			

			if(leng>10)
			{
				for(p=0;p<13;p++)
				{
					output[p]='?';
					output[10]='.';
					output[13]=' ';
				}
			}
			else
			{
				shft=14-leng;
				for(n=1;n<=leng;n++)
				{
					output[13-n]=output[leng-n];
					output[leng-n]=' ';
				}
				if(leng>6)
				{
					for(o=shft-1;o<7;o++)
					{
						output[o-1]=output[o];
					}
					output[6]=',';
					
				}
				if(leng>9)
				{
					output[1]=output[2];
					output[2]=',';		
				}
	 							
			}
			output[13]=' ';
		}


		if(nit4->ttype == '-')
		{
			leng=strlen(output);
			if(leng == 3)
			{
				output[3]=' ';				
				output[4]=' ';
				output[5]=' ';
				output[6]=' ';
				output[7]=' ';
				output[8]=' ';
				output[9]=' ';			
			}
			if(leng == 4)
			{
				output[4]=' ';
				output[5]=' ';
				output[6]=' ';
				output[7]=' ';
				output[8]=' ';
			}
			if(leng == 5)
			{
				output[5]=' ';
				output[6]=' ';
				output[7]=' ';
			}
			if(leng == 6)
			{
				output[6]=' ';
			}
			if(leng>10)
			{
				for(p=1;p<13;p++)
				{
					output[p]='?';
					output[10]='.';
				}
				output[0]='(';
				output[13]=')';
			}
			else
			{
				shft=14-leng;
				for(n=1;n<=leng;n++)
				{
					output[13-n]=output[leng-n];
					output[leng-n]=' ';
				}
				output[0]='(';
				output[13]=')';
				
				if(leng>6)
				{
					for(q=shft-2;q<6;q++)
					{
						output[q]=output[q+1];
					}
					output[6]=',';
				}
				
				if(leng>9)
				{
					output[1]=output[2];
					output[2]=',';
				}
			}
			
		}
	
		output[14]='\0';	
			
			
			if(elem4 == My402ListFirst(anc))			
			{
				if(nit4->ttype == '+')
				balance=nit4->dollar;

				if(nit4->ttype == '-')
				balance=-(nit4->dollar);
			}
			else
			{
				if(nit4->ttype == '+')
				{
										
					balance=balance+nit4->dollar;
				}
				if(nit4->ttype == '-')
				{
										
					balance=balance-nit4->dollar;
				}
			}

		if(balance > 0)
		{
			memset(bal,'\0',sizeof(bal));
			sprintf(bal,"%d",balance);
			balleng=strlen(bal);
	
			bal[balleng]=bal[balleng - 1];
			bal[balleng - 1]=bal[balleng - 2];
			bal[strlen(bal) - 3] = '.';
			
			balleng=strlen(bal);
			if(balleng == 3)
			{
				bal[3]=' ';				
				bal[4]=' ';
				bal[5]=' ';
				bal[6]=' ';
				bal[7]=' ';
				bal[8]=' ';
				bal[9]=' ';
							
			}
			if(balleng == 4)
			{
				bal[4]=' ';
				bal[5]=' ';
				bal[6]=' ';
				bal[7]=' ';
				bal[8]=' ';
				
			}
			if(balleng == 5)
			{
				bal[5]=' ';
				bal[6]=' ';
				bal[7]=' ';
				
			}
			if(balleng == 6)
			{
				bal[6]=' ';
				
			}

			if(balleng>10)
			{
				for(u=0;u<13;u++)
				{
					bal[u]='?';
					bal[10]='.';
					bal[13]=' ';
				}
			}
			else
			{
				balshft=14-balleng;
				for(v=1;v<=balleng;v++)
				{
					bal[13-v]=bal[balleng-v];
					bal[balleng-v]=' ';
				}
				if(balleng>6)
				{
					for(w=balshft-1;w<7;w++)
					{
						bal[w-1]=bal[w];
					}
					bal[6]=',';
					
				}
				if(balleng>9)
				{
					bal[1]=bal[2];
					bal[2]=',';		
				}
	 							
			}
			bal[13]=' ';
		}

		if(balance < 0)
		{
			memset(bal,'\0',sizeof(bal));
			sprintf(bal,"%d",balance);
			
			for(s=0;s<strlen(bal)-1;s++)
			{
				bal[s]=bal[s+1];
			}
				bal[s]='\0';
			balleng=strlen(bal);
			bal[balleng]=bal[balleng - 1];
			bal[balleng - 1]=bal[balleng - 2];
			bal[strlen(bal) - 3] = '.';
			balleng=strlen(bal);
			if(balleng == 3)
			{
				bal[3]=' ';				
				bal[4]=' ';
				bal[5]=' ';
				bal[6]=' ';
				bal[7]=' ';
				bal[8]=' ';
				bal[9]=' ';			
			}
			if(balleng == 4)
			{
				bal[4]=' ';
				bal[5]=' ';
				bal[6]=' ';
				bal[7]=' ';
				bal[8]=' ';
			}
			if(balleng == 5)
			{
				bal[5]=' ';
				bal[6]=' ';
				bal[7]=' ';
			}
			if(balleng == 6)
			{
				bal[6]=' ';
			}
			if(balleng>10)
			{
				for(x=1;x<13;x++)
				{
					bal[x]='?';
					bal[10]='.';
				}
				bal[0]='(';
				bal[13]=')';
			}
			else
			{
				balshft=14-balleng;
				for(y=1;y<=balleng;y++)
				{
					bal[13-y]=bal[balleng-y];
					bal[balleng-y]=' ';
				}
				bal[0]='(';
				bal[13]=')';
				if(balleng>6)
				{
					for(z=balshft-2;z<6;z++)
					{
						bal[z]=bal[z+1];
					}
					bal[6]=',';
				}
				if(balleng>9)
				{
					bal[1]=bal[2];
					bal[2]=',';
				}
			}
		}

			
			fprintf(stdout,"\n| %s | %s | %s | %s |",timearr,nit4->tdesc,output,bal);
			elem4=elem4->next;					
				
	}

	fprintf(stdout,"\n+-----------------+--------------------------+----------------+----------------+\n");
	}
//---------------------End of Function display----------------------------
//---------------------Function Populate----------------------------------
	void static populate(My402List* anc)
	{
	My402ListInit(anc);

	memset(buf,'\0',sizeof(buf));
	
  
	if(fp == NULL)
	{
		perror("Cannot open file");
		exit(0);
	}
	
	while(fgets(buf,sizeof(buf),fp) != NULL)
	{
		if(strlen(buf) >1024)
		{
			fprintf(stderr,"\nfile length too long,cannot open");
			exit(1);
		}
		
		obj1=(data *)malloc(sizeof(data));
		start_ptr = buf;
		tab_ptr = strchr(start_ptr,'\t');
		if(tab_ptr != NULL)
		{
			obj1->ttype = *start_ptr;
			*tab_ptr++ = '\0';
		}
		else
		{
			fprintf(stderr,"\nLine is Malformed");
			exit(1);
		}
		
		if(obj1->ttype != '+' && obj1->ttype != '-')
		{
			fprintf(stderr,"\nLine is Malformed");
			exit(1);
		}

		start_ptr = tab_ptr;
		tab_ptr = strchr(start_ptr,'\t');
		if(tab_ptr != NULL)
		{

			i=0;
			while(*start_ptr != '\t')
			{
				tbuf[i] = *start_ptr;
				i++;
				start_ptr++;
			}
								
			if(strlen(tbuf) > 10)
			{
				perror("\nTime Stamp is BAD");
				exit(0);
			}
			obj1->ttime = atoi(tbuf);
			current_time = (int)time(NULL);
			if(obj1->ttime > current_time)
			{
				fprintf(stderr,"\nBad Time Stamp");
				exit(1);
			}
			*tab_ptr++ = '\0';
		}
		else
		{
			fprintf(stderr,"\nLine is Malformed");
			exit(1);
		}
		start_ptr = tab_ptr;
		tab_ptr = strchr(start_ptr,'\t');
		if(tab_ptr != NULL)
		{
			j=0;
			memset(amtdollarbuf,'\0',sizeof(amtdollarbuf));
			while(*start_ptr != '\t')
			{	
				
				amtdollarbuf[j] = *start_ptr;
				j++;
				start_ptr++;
			}
			if(amtdollarbuf[j-3] != '.')
			{
				fprintf(stderr,"\nAmount is malformed");
				exit(1);
			}
			
			if(strlen(amtdollarbuf) > 10)
			{
				fprintf(stderr,"\nAmount is malformed");
				exit(1);
			}
		
			amtdollarbuf[strlen(amtdollarbuf) - 3] = amtdollarbuf[strlen(amtdollarbuf) - 2];
			amtdollarbuf[strlen(amtdollarbuf) - 2] = amtdollarbuf[strlen(amtdollarbuf) - 1];
			amtdollarbuf[strlen(amtdollarbuf) - 1] = '\0';
			obj1->dollar = atoi(amtdollarbuf);
			
			if(obj1->dollar < 0)
			{
				fprintf(stderr,"\nAmount is malformed");
				exit(1);
			}
			*tab_ptr++ = '\0';
		}
		else
		{
			fprintf(stderr,"\nLine is Malformed");
			exit(1);
		}
		
		start_ptr = tab_ptr;
		tab_ptr = strchr(start_ptr,'\n');
		if(tab_ptr != NULL)
		{
			l=0;
			memset(descbuf,'\0',sizeof(descbuf));
			while(*start_ptr == ' ')
			{
				start_ptr++;
			}
			while(*start_ptr != '\n')
			{
				if(*start_ptr == '\t')
				{
					fprintf(stderr,"\nLine is Malformed");
					exit(1);
				}
				descbuf[l] = *start_ptr;
				l++;
				start_ptr++;
			}
			
			if(strlen(descbuf) == 0)
			{
				fprintf(stderr,"\nDescription is malformed");
				exit(1);
			}

			strncpy(obj1->tdesc,descbuf,sizeof(obj1->tdesc));

		}
		else
		{
			fprintf(stderr,"\nLine is Malformed");
			exit(1);
		}
		
		if(My402ListAppend(anc,obj1) == FALSE)
		{
			fprintf(stderr,"Error appending to list:%d",errno);
		}
	

	}
	}

//----------------------End of Function Populate----------------------------


int main(int argc,char* argv[])
{
 
My402List* anc;

  anc=(My402List* )malloc(sizeof(My402List));
  elem1=(My402ListElem *)malloc(sizeof(My402ListElem));
  elem2=(My402ListElem *)malloc(sizeof(My402ListElem));
  elem3=(My402ListElem *)malloc(sizeof(My402ListElem));
  elem4=(My402ListElem *)malloc(sizeof(My402ListElem));
  elem5=(My402ListElem *)malloc(sizeof(My402ListElem));
  smallest=(My402ListElem *)malloc(sizeof(My402ListElem));
 
    
    if(strcmp(argv[1],"sort"))
    {
        fprintf(stderr,"\nmalformed command");
        fprintf(stderr,"\nuse: Warmup1 sort [tfile]");
        exit(1);
    }
    if(argc < 2)
    {
        fprintf(stderr,"\nmalformed command");
        fprintf(stderr,"\nuse: Warmup1 sort [tfile]");
        exit(1);
    }
    if(argc == 2)
    {
        fp = stdin;
    }
    if(argc == 3)
    {
        fp = fopen(argv[2],"r");
	if(fp == NULL)
	{
		perror("\nCannot open file");
		exit(1);
	}
	/********* This part has been referred from http://cboard.cprogramming.com/c-programming/133346-determine-file-type-linux.html ******/
	struct stat buff1;
	stat(argv[2],&buff1);
		if(S_ISDIR(buff1.st_mode))
		{
			fprintf(stderr,"The file %s is a directory\n",argv[2]);
			exit(1);
		}
	/*************** This is the end of the code referred ************************/
    }

    populate(anc);    
    sort(anc);
    display(anc);

return(0);
}

		
