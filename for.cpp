#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace  std ;

string after[15]={""};
int nestedLoop=0;
bool forFound= false, forOpen[15]={false};

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


int main(){
    ifstream iFile;
    iFile.open("For4.cpp");

    ofstream oFile;
    oFile.open("output1.txt");

    string str;

    if(iFile.is_open()){


        while(getline(iFile,str)){

            forFound=CheckForLoop(str);
            if(forOpen[nestedLoop]==true) str=CloseIfCurlyBraceFound(str);


            if(forFound==false){
                oFile<<str<<"\n";
                cout<<str<<endl;
            }
            else if(forFound==true){
                nestedLoop++;
                forOpen[nestedLoop]=true;

                str=ConvertToWhile(str);

                oFile<<str<<"\n";
                cout<<str<<endl;

                forFound=false;
            }

        }
        iFile.close();
    }

    return 0;
}
