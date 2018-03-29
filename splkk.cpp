#include<iostream>
#include<string>
#include<fstream>

using namespace  std ;
char **arr;
string str;

int len=0;
int StringLength(string str)
{
    int i;
    for ( i = 0; str[i] != '\0'; i++);

        return i;

}

string cleanupPuncuation(string  str,int len)

{
	string habijabi = "!@#$%^&*()_-{}[]:;'?.,<>/|~";
	for(int i=0; i<len; i++)
	{
		for(int j=0;j<30;j++)
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

    iFile.open("sp.txt");
    if(iFile.is_open())
    {

       cout << "emu" << endl;

        while(getline(iFile,str))
        {
            len = StringLength(str);

        cout<<cleanupPuncuation(str,len) <<endl;
        cout << len << endl;

        }

    }
}
