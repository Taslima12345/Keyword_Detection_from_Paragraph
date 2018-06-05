#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<cmath>

using namespace  std ;

bool switchFound=false, firstIf=true;
string caseCondition[260]={""}, switchExp[260]={""};
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
        if(str[i]!=' ') switchValue=switchValue+str[i];
    }

    if(Found==true && paranthesisFound==true) return true;

    else return false;
}

//==>

void WriteOutput(ofstream &oFile,int caseNo, int caseStart){
    int hasCond=caseNo;
    //cout<<"entered\n";
    for(int i=caseNo; i>caseStart; i--){


        if(caseCondition[i]=="" ){
            if(i<caseNo)switchExp[hasCond]=switchExp[i]+"|| "+switchExp[hasCond];

        }
        else{
            if(i<caseNo) caseCondition[i]=caseCondition[i]+caseCondition[hasCond];
            hasCond=i;
        }
    }
    for(int i=caseStart+1; i<=caseNo; i++){
        if(caseCondition[i]!=""){
            oFile<<"if("+switchExp[i]+"){\n"+caseCondition[i]+"}\n";

            cout<<"if("+switchExp[i]+"){\n"+caseCondition[i]+"}\n";
        }
    }
    //cout<<"left\n";
}


//==>

void ConvertSwitchInto_if_else(ifstream &iFile, ofstream &oFile){
    string str;
    int caseNo=0, caseStart=0;
    string switchExpDefault="else{\n";
    bool defaultFound=false;

    while(getline(iFile,str)){
        //cout<<str<<endl;
        int switchExpPosition=-1;

        bool switchExpFound=false;
        bool IsAcondition=true;
        for(int i=0; str[i]; i++){

            if(defaultFound==true && str[i]=='}' ) {

                oFile<<switchExpDefault+"}\n";
                cout<<switchExpDefault+"}\n";
                switchFound=false;
                defaultFound==false;
                return;
            }
            else if(defaultFound==true && (str[i]=='b'&& str[i+1]=='r'&& str[i+2]=='e'
               &&str[i+3]=='a' &&str[i+4]=='k')){
                IsAcondition=false;
                break;
            }
            else if(defaultFound==false &&str[i]=='b'&& str[i+1]=='r'&& str[i+2]=='e'
               &&str[i+3]=='a' &&str[i+4]=='k'){
                    WriteOutput(oFile,caseNo,caseStart);
                    caseStart=caseNo;
                    IsAcondition=false;
               }
            else if(str[i]==':'){
                switchExpFound=false;
                switchExp[caseNo]= switchValue+"=="+switchExp[caseNo];
                IsAcondition=false;
            }
            else if(str[i]=='c'&& str[i+1]=='a'&& str[i+2]=='s' &&str[i+3]=='e'){
                //switchExpPosition=i+3;
                i+=3;
                switchExpFound=true;
                caseNo++;
                IsAcondition=false;
            }
            else if(switchExpFound==true){
                if(str[i]!=' ') switchExp[caseNo]=switchExp[caseNo]+str[i];
                 IsAcondition=false;
            }

            else if(str[i]=='d'&& str[i+1]=='e'&& str[i+2]=='f'
               &&str[i+3]=='a' &&str[i+4]=='u' &&str[i+5]=='l' &&str[i+6]=='t'){
                //cout<<"enterd\n";
                defaultFound=true;
                IsAcondition=false;
            }

        }
        if(IsAcondition==true &&defaultFound==false)caseCondition[caseNo]=caseCondition[caseNo]+str+"\n";
        else if(IsAcondition==true &&defaultFound==true){
            switchExpDefault=switchExpDefault+str+"\n";
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
