#include<iostream>
#include<string>
#include<fstream>
#include<sstream>

using namespace  std ;
char **arr;
string str;
string line[10000],word[10000];
int num[10000];
int len=0;

void Now_Merge( int left, int middle, int right)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 =  right - middle;
    string temp;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = num[left + i];

    for (j = 0; j < n2; j++)
        R[j] = num[ (middle +1) + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            num[k] = L[i];

            temp = word[k];
            word[k] = word[i];
            word[i] = temp;

            i++;
        }
        else
        {
            num[k] = R[j];

            temp = word[k];
            word[k] = word[j];
            word[j] = temp;

            j++;
        }
        k++;
    }

    while (i < n1)
    {
        num[k] = L[i];

        temp = word[k];
        word[k] = word[i];
        word[i] = temp;

        i++;
        k++;
    }

    while (j < n2)
    {
        num[k] = R[j];

        temp = word[k];
        word[k] = word[i];
        word[i] = temp;

        j++;
        k++;
    }
}


void Do_MergeSort( int left, int right)
{
    if (left < right)
    {
        int middle = left+(right-left)/2;

        Do_MergeSort( left, middle);
        Do_MergeSort( middle+1, right);

        Now_Merge( left, middle, right);
    }
}

int StringLength(string str)
{
    int i;
    for ( i = 0; str[i] ; i++);

    return i;

}

string PunctuationCleaningAndLowercasing(string  str,int len)

{
	string habijabi = ",./?'\"':;{}[]\\*()%#@!&+-";
	for(int i=0; i<len; i++)
	{
        if ( str[i] >= 'A' && str[i] <= 'Z' ){
            str[i] = str[i] + 32;
            continue;
        }
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

    iFile.open("TextToRead1.txt");
    string str;

    if(iFile.is_open())
    {

        int LineNo=0 ;

        while(getline(iFile,str))
        {

            len = StringLength(str);

            str = PunctuationCleaningAndLowercasing(str,len) ;

            string s ;
            line[LineNo] = str;

            LineNo++;

        }
        iFile.close();

        ifstream iff;

        oFile.open("pureWords.txt");

        string WordFromTextLine, StopWord;
        int TotalWord = 0;

        for(int j =0 ; j < LineNo ; j++){

            stringstream ss(line[j]);

            while(ss>>WordFromTextLine){

                bool found=false;

                iff.open("stopWords.txt");

                if(iff.is_open()){

                    while(iff>>StopWord){

                        if(StopWord==WordFromTextLine){

                            found=true;
                            break;
                        }
                    }
                }
                iff.close();

                if(found==false){

                    oFile<<WordFromTextLine<<" ";
                    word[TotalWord]=WordFromTextLine;
                    TotalWord++;
                }
            }

        }
        /*ifstream fl;
        fl.open("pureWords.txt");
        string st;
        */
        cout<<"\n\nWORD\t\tNUMBER OF PRESENCE\n\n";

        for(int i=0; i<TotalWord; i++){

            int WordCount=1;
            if(word[i]!="-1"){

                for(int k=i+1; k<TotalWord; k++){

                    if(word[i]==word[k]){
                        word[k]="-1";
                        WordCount++;
                    }
                }
            }
            if(word[i]!="-1"){
                num[i]=WordCount;

            }
        }
        Do_MergeSort( 0, TotalWord-1 );

        for(int i=0; i<TotalWord; i++){
            if(word[i]!="-1")
                cout<<word[i]<<"\t\t"<<num[i]<<endl;
        }

    }
    return 0;
}
