#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>

#include "LZ77encoder.h"

using namespace std;

string test;

long int test_Len;//=test.size();
long int const buf_Size=998;              //buf_size is length of window
char lab[(buf_Size/2)+1]="";            //equal length of sb and lab +1 for '\0'
char sb[(buf_Size/2)+1]="";
int len=0;
int mtch_Len=0;
int file_size=0;


ofstream comp_File;

void lab_upd(){											//To update the look-ahead-buffer(lab) from the original text

    //char test[13]="abracadabrad";
    //char lab[9]="";
    int lab_Len=strlen(lab);
    int empty=(buf_Size/2)-lab_Len;                                     //spaces empty in lab
    if(test_Len-(len+lab_Len)>(empty)){
        for(int i=0;i<empty;i++){                         //char in test are more than the empty spaces left in lab
        lab[lab_Len+i]=test[(len+lab_Len)+i];
        }
    }
    else{
        for(int i=0;i<(empty);i++){            //char left in test is less than empty spaces left in lab  (//for(int i=0;i<(12-(len+lab_Len));i++) may also be used)
        lab[lab_Len+i]=test[(len+lab_Len)+i];
        }
    }

    ///cout<<"new_lab-"<<lab<<endl;
    //cout<<len<<endl;

}

void buf_upd(){                                 //Updating the search buffer and the look-ahead-buffer with the match found

    //char test[13]="abracadabrad";
    //char sb[9]="dacarba";
    //char lab[9]="abrad";
    //int length=0;                               //length of longest match

    if(mtch_Len!=(buf_Size/2)){     			//when sb is not equal to lab
        for(int i=0;i<mtch_Len+1;i++){					//shifting curr elements left in sb
			for(int j=((buf_Size/2)-1);j>0;j--){
				sb[j]=sb[j-1];
			}
		}
        for(int j=0;j<mtch_Len+1;j++){                //placing seq elements from lab in sb
            sb[j]=lab[mtch_Len-j];
        }
        for(int k=mtch_Len+1;k<(buf_Size/2)+1;k++){                //shifting non seq elements right in lab
            lab[k-mtch_Len-1]=lab[k];
        }
    }
    else{					// when the seq in both sb and lab is same
        for(int j=0;j<mtch_Len;j++){                //placing seq elements from lab in sb
            sb[j]=lab[mtch_Len-j-1];
        }
        memset(lab,0,sizeof(lab));
        for(int i=0;i<(buf_Size/2)-1;i++){
            sb[(buf_Size/2)-1-i]=sb[(buf_Size/2)-2-i];
        }
        sb[0]=test[len-1];                                    //assigning luc as the len-1 char of the orig_txt

    }

    //cout<<"sb-"<<sb<<endl;
    //cout<<"lab-"<<lab<<endl;

}

void seq_sb(){            //Searching in SB to find longest match of the look-ahead buffer

    //char sb[9]="";       //Remember that the testcase for sb "must be put in reverse order" from the article
    //char lab[9]="";
    int len_sb=strlen(sb);
    int len_Lab=strlen(lab);
    //int mtch_Len=0;

    mtch_Len=0;
    int lg_Mtch[buf_Size/2]={0};
    char ch=lab[0];

    int offset=0,length=0;
    char luc='\0';                   //luc = last unmatched char

    for(int i=0;i<(buf_Size/2);i++){		//for finding all the string matches starting with lab[0]
        ch=lab[0];
        if(ch==sb[i]){
            length=0;						//using an array(lg_Mtch) for storing the length of match found and the offset of the sequence
            if(len_sb<len_Lab){
                for(int j=0;i-j>-1;j++){
                    ch=lab[j];
                    if(ch==sb[i-j]){
                        if(j==len_Lab-1){
                            length=length+1;
                            lg_Mtch[i]=length;
                        }
                        else{
                            length=length+1;
                            lg_Mtch[i]=length;
                        }
                    }
                    else{
                        lg_Mtch[i]=length;
                        break;
                    }
                }
            }
            else{
                for(int j=0;(j<len_Lab)&&(i-j>-1);j++){
                    ch=lab[j];
                    if(ch==sb[i-j]){
                        if(j==len_Lab-1){
                            length=length+1;
                            lg_Mtch[i]=length;
                        }
                        else{
                            length=length+1;
                            lg_Mtch[i]=length;
                        }
                    }
                    else{
                        lg_Mtch[i]=length;
                        break;
                    }
                }

            }

        }

    }
    //for(int n=0;n<8;n++){
        //cout<<lg_Mtch[n]<<endl;
    //}

    for(int n=0;n<buf_Size/2;n++){					//for finding longest matched length found
        mtch_Len=max(lg_Mtch[n],mtch_Len);
    }
    for(int n=0;n<buf_Size/2;n++){
        if(mtch_Len==0){					//for finding the offset of longest match found
            offset=0;
        }
        else{
            if(mtch_Len==lg_Mtch[n]){
                offset=n+1;
                break;
            } 
        }
    }

     len=len+mtch_Len+1;                                       //len=summation of all prev (longest_match(l)+1) (<o,l,c()>)

    if(mtch_Len==((buf_Size/2))){
        luc=test[len-1];  //summation of all prev (longest_match(l)+1) (<o,l,c()>)     //luc=test[len-1];
    }
    else{
        if(lab[mtch_Len]){
            luc=lab[mtch_Len];			//assigning luc
        }
        else{
            luc='\0';
    	}
    }
		//cout<<offset<<'|'<<mtch_Len<<'|'<<luc<<endl;
     
	if(mtch_Len!=1&&mtch_Len!=0){
		
		comp_File.open("compressed_file.txt",ios::ate|ios::app);
		comp_File<<offset<<','<<mtch_Len<<luc<<'|';				//added separator for offset and length identification
		//cout<<offset<<','<<mtch_Len<<luc<<'|'<<endl;
		file_size=file_size+7;
	    comp_File.close();
	}
	else{	
		if(offset==0) {	//just using luc to signify that offset=length=0
			comp_File.open("compressed_file.txt",ios::ate|ios::app);
		    comp_File<<luc<<'|';				//added separator for offset and length identification
		    //cout<<luc<<'|'<<endl;
		    file_size=file_size+2;
		    comp_File.close();
		}
		else{	//no need to write length when length=1
			comp_File.open("compressed_file.txt",ios::ate|ios::app);
		    comp_File<<offset<<luc<<'|';				//added separator for offset and length identification
		    //cout<<offset<<luc<<'|'<<endl;
		    file_size=file_size+4;
		    comp_File.close();
				
		}			
	}
	//cout<<offset<<'|'<<length<<'|'<<luc<<endl;

}

void encoder(){			//Package function which calls the above functions in the order (lab_upd->seq_sb->buf_upd->lab_upd)

	//cout<<test<<endl;
	
	test_Len=test.size();
	
	//cout<<test_Len<<endl;

    lab_upd();

   

    int lab_Len=strlen(lab);
    
    while(lab_Len!=0){
		
		//cout<<len<<endl;
    	
        seq_sb();
        
        buf_upd();
        
        lab_upd();
        
        lab_Len=strlen(lab);

    }
    
    cout<<file_size<<endl;

}
