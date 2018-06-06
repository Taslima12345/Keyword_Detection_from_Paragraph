#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace  std ;

//For for loop
string after[15]={""};
int nestedLoop=0;
bool forFound= false, forOpen[15]={false};

//For switch
bool switchFound=false, firstIf=true;
string caseStatement[260]={""}, caseCondition[260]={""};
string switchValue="";

//functions started For for loop... *

bool CheckForLoop(string str){

    int length=0;
    bool paranthesisFound=false, Found=false;
    for(int i=0; str[i]; i++){
        length++;
    }

    for(int i=0; i<length; i++){
        if(str[i]=='f'&& str[i+1]=='o'&& str[i+2]=='r'){
            Found=true;
        }
        if(Found==true && str[i]=='('){
            paranthesisFound=true;
            break;
        }
    }

    if(Found==true && paranthesisFound==true) return true;

    else return false;
}

string ConvertToWhile(string str){

    string before="", middle="", loopStart="while(";
    int bracketIndex1, bracketIndex2, semiColon;

    bool CurlyBraceFound=false;

    for(int i=0; str[i]; i++){
        if(str[i]=='(') bracketIndex1=i;
        if(str[i]==')') bracketIndex2=i;
        if(str[i]=='{') CurlyBraceFound=true;
    }


    for(int i=bracketIndex1+1; str[i]; i++){

            if(str[i]!=';') before= before+str[i];
            else if(str[i]==';'){
                semiColon=i;
                break;
            }

    }

    for(int i=semiColon+1; str[i]; i++){

        if(str[i]!=';') middle= middle+str[i];
        else if(str[i]==';'){
            semiColon=i;
            break;
        }


    }

    for(int i=semiColon+1; i<bracketIndex2; i++){

         after[nestedLoop]= after[nestedLoop]+str[i];

    }

    bool b=false, m=false, a=false;

    for(int i=0; before[i]; i++)
        if((before[i]>65 &&before[i]<90) || (before[i]>97 &&before[i]<122) ){ b=true; break; }


    for(int i=0; after[nestedLoop][i]; i++)
        if((after[nestedLoop][i]>65 &&after[nestedLoop][i]<90) ||
            (after[nestedLoop][i]>97 &&after[nestedLoop][i]<122) ){ a=true; break; }

    for(int i=0; middle[i]; i++)
        if((middle[i]>65 &&middle[i]<90) || (middle[i]>97 &&middle[i]<122) ){ m=true; break; }


    string modString="",extension;
    if(CurlyBraceFound==true) extension="){";
    else extension=")";


    if(a==false){
        forOpen[nestedLoop]=false;
        after[nestedLoop]="";
        nestedLoop--;
    }
    if(m==false){

        if(b==false) modString=loopStart+"true"+extension+"\n";
        else modString=before+";\n"+loopStart+"true"+extension+"\n";
    }

    else  modString= before+";\n"+loopStart+middle+extension+"\n";

    return modString;
}




string CloseIfCurlyBraceFound(string str){
    for(int i=0; str[i]; i++){
        if(str[i]=='}'){
            str="\t"+after[nestedLoop]+";\n"+str+"\n";

            forOpen[nestedLoop]=false;
            after[nestedLoop]="";
            nestedLoop--;

            break;
        }
    }
    return str;
}
 //...functions ended For for loop...*
 /*----------------------------------------------*/

 //functions started For switch...*

 bool CheckForSwitch(string str){

    int length=0, bracketIndex;
    bool paranthesisFound=false, Found=false;

    for(int i=0; str[i]; i++){
        length++;
    }

    for(int i=0; i<length; i++){
        if(str[i]=='s'&& str[i+1]=='w'&& str[i+2]=='i' &&
           str[i+3]=='t'&& str[i+4]=='c'&& str[i+5]=='h'){
            Found=true;
        }
        if(Found==true && str[i]=='('){
            bracketIndex=i;
            paranthesisFound=true;
            break;
        }
    }

    for(int i=bracketIndex+1; i<length; i++){
        if(str[i]==')')break;
         switchValue=switchValue+str[i];
    }

    if(Found==true && paranthesisFound==true) return true;

    else return false;
}

//==>

void WriteOutput(ofstream &oFile,int caseNo, int caseStart){
    int hasCond=caseNo;
    //cout<<"entered\n";
    for(int i=caseNo; i>caseStart; i--){


        if(caseStatement[i]=="" ){
            if(i<caseNo)caseCondition[hasCond]=caseCondition[i]+"|| "+caseCondition[hasCond];

        }
        else if(caseStatement[i]!=""){
            if(i<caseNo) caseStatement[i]=caseStatement[i]+caseStatement[hasCond];
            hasCond=i;
        }
    }
    for(int i=caseStart+1; i<=caseNo; i++){
        if(caseStatement[i]!=""){
            oFile<<"if("+caseCondition[i]+"){\n"+caseStatement[i]+"\t}\n";

            cout<<"if("+caseCondition[i]+"){\n"+caseStatement[i]+"\t}\n";
        }
    }
    //cout<<"left\n";
}


//==>

void ConvertSwitchInto_if_else(ifstream &iFile, ofstream &oFile){
    string str;
    int caseNo=0, caseStart=0;
    string DefaultStatement="else{\n";
    bool defaultFound=false;

    while(getline(iFile,str)){
        //cout<<str<<endl;
        //int switchExpPosition=-1;

        bool caseCondFound=false;
        bool IsAStatement=true;
        for(int i=0; str[i]; i++){

            if(defaultFound==true && str[i]=='}' ) {

                oFile<<DefaultStatement+"\t}\n";
                cout<<DefaultStatement+"\t}\n";
                switchFound=false;
                defaultFound==false;
                return;
            }
            else if(defaultFound==true && (str[i]=='b'&& str[i+1]=='r'&& str[i+2]=='e'
               &&str[i+3]=='a' &&str[i+4]=='k')){
                IsAStatement=false;
                break;
            }
            else if(defaultFound==false &&str[i]=='b'&& str[i+1]=='r'&& str[i+2]=='e'
               &&str[i+3]=='a' &&str[i+4]=='k'){

                    WriteOutput(oFile,caseNo,caseStart);
                    caseStart=caseNo;
                    IsAStatement=false;
               }
            else if(caseCondFound==true &&str[i]==':'){
                caseCondFound=false;
                caseCondition[caseNo]= switchValue+"=="+caseCondition[caseNo];
                 //cout<<caseCondition[caseNo]<<endl;
                IsAStatement=false;
            }
            else if(str[i]=='c'&& str[i+1]=='a'&& str[i+2]=='s' &&str[i+3]=='e'){
                //switchExpPosition=i+3;
                i+=3;
                caseCondFound=true;
                caseNo++;
                IsAStatement=false;
            }
            else if(caseCondFound==true){
                if(str[i]!=' ') caseCondition[caseNo]=caseCondition[caseNo]+str[i];  //pblm
                 IsAStatement=false;
            }

            else if(str[i]=='d'&& str[i+1]=='e'&& str[i+2]=='f'
               &&str[i+3]=='a' &&str[i+4]=='u' &&str[i+5]=='l' &&str[i+6]=='t'){
                //cout<<"enterd\n";
                defaultFound=true;
                IsAStatement=false;
            }

        }
        if(IsAStatement==true &&defaultFound==false){
                 //cout<<str<<endl;
                caseStatement[caseNo]=caseStatement[caseNo]+str+"\n";
        }
        else if(IsAStatement==true &&defaultFound==true){
             //cout<<str<<endl;
            DefaultStatement=DefaultStatement+str+"\n";
        }
    }
}

//...functions ended For switch...*

int main(){
    ifstream iFile;
    iFile.open("input1.cpp");

    ofstream oFile;
    oFile.open("output1.txt");

    string str;

    if(iFile.is_open()){


        while(getline(iFile,str)){

            forFound=CheckForLoop(str);
            switchFound=CheckForSwitch(str);

            if(forOpen[nestedLoop]==true) str=CloseIfCurlyBraceFound(str);


            if(forFound==false && switchFound==false){
                oFile<<str<<"\n";
                cout<<str<<endl;
            }
            else if(forFound==true &&switchFound==false){
                nestedLoop++;
                forOpen[nestedLoop]=true;

                str=ConvertToWhile(str);

                oFile<<str<<"\n";
                cout<<str<<endl;

                forFound=false;
            }
            else if(switchFound==true &&forFound==false){
                ConvertSwitchInto_if_else(iFile, oFile);
            }

        }
        iFile.close();
    }

    return 0;
}

