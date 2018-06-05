#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace  std ;

bool switchFound=false, firstIf=true;
string caseStatement[260]={""}, caseCondition[260]={""};
string switchValue="";

//==>
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
            oFile<<"if("+caseCondition[i]+"){\n"+caseStatement[i]+"}\n";

            cout<<"if("+caseCondition[i]+"){\n"+caseStatement[i]+"}\n";
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

                oFile<<DefaultStatement+"}\n";
                cout<<DefaultStatement+"}\n";
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

int main(){
    ifstream iFile;
    iFile.open("switch4.cpp");

    ofstream oFile;
    oFile.open("outputswitch.txt");

    string str;

    if(iFile.is_open()){


        while(getline(iFile,str)){

            switchFound=CheckForSwitch(str);

            if(switchFound==true){
                ConvertSwitchInto_if_else(iFile, oFile);
            }
            else if(switchFound==false){
                oFile<<str<<"\n";
                cout<<""<<str<<endl;
            }

        }
        iFile.close();
    }

    return 0;
}
