#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace  std ;
char **arr;
string str;
string word[10000],wrd[10000];
int num[10000];
int len=0;
void Sort(string *wrd,int *num ,int x){
    int tmp1;   string tmp2;
    for(int i=0; i<x-1; i++){
        for(int j=i+1; j<x; j++){
            if(num[j]>num[i]){
                tmp1= num[i];   tmp2=wrd[i];
                num[i]=num[j];  wrd[i]=wrd[j];
                num[j]=tmp1;    wrd[j]=tmp2;
            }
        }
    }

}


int StringLength(string str)
{
    int i;
    for ( i = 0; str[i] ; i++);

        return i;

}

string cleanupPuncuation(string  str,int len)

{
	string habijabi = ",./?'\"':;{}[]\\*()%#@!&+-";
	for(int i=0; i<len; i++)
	{
		for(int j=0;j<habijabi.length();j++)
		{
			if(str[i]==habijabi[j]) {
                    str[i] = ' ';
                    break;
			}
		}
	}
	return str;
}

int main()
{
    ifstream iFile;

    ofstream oFile;

    iFile.open("soup.txt");
    string str;

    if(iFile.is_open())
    {

       int k=0,x=0 ;

        while(getline(iFile,str))
        {
            //cout<<"LOLLiPop"<<endl;
            len = StringLength(str);

            str = cleanupPuncuation(str,len) ;
            //cout<<str<<endl;
            string s ;
            word[k] = str;

            k++;

        }
            iFile.close();
            /*for(int j =0 ; j < k ; j++){
                cout << word[j] <<endl;
            }*/
            ifstream iff;

            oFile.open("sp.txt");

            string nw,stw;

            for(int j =0 ; j < k ; j++){

                stringstream ss(word[j]);

                while(ss>>nw){

                        bool found=false;

                        iff.open("stopWord.txt");

                    if(iff.is_open()){

                        while(iff>>stw){

                            if(stw==nw){

                                found=true; break;
                            }
                        }
                    }
                    iff.close();

                    if(found==false){
                        oFile<<nw<<" ";
                        wrd[x]=nw;
                        x++;
                    }
                }
                cout<<endl;
            }
            ifstream fl;
            fl.open("sp.txt");
            string st;
            //int cc=0;
            cout<<"\n\nWORD\t\tNUMBER OF PRESENCE\n\n";
            for(int i=0; i<x; i++){
                   int cc=1;
                   if(wrd[i]!="-1"){
                        for(int k=i+1; k<x; k++){
                            if(wrd[i]==wrd[k]){
                                wrd[k]="-1";
                                cc++;  //break;
                            }
                        }
                   }
                if(wrd[i]!="-1"){
                    num[i]=cc;
                    //cout<<wrd[i]<<"\t\t"<<cc<<endl;
                }
            }
            Sort(wrd,num,x);
            for(int i=0; i<x; i++){
               if(wrd[i]!="-1") cout<<wrd[i]<<"\t\t"<<num[i]<<endl;
            }

    }
}

