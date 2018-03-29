#include<iostream>
#include<string>

using namespace  std ;

string str = " I , ! . !!! am a Ullock rrrt ";

int StringLength(string str)
{
    int i;
    for ( i = 0; str[i] != '\0'; i++);

        return i;

}

/*void cleanup(string  str,int len)
//void cleanup(string &s)
{
	string habijabi = "$#&,.!";
	for(int i=0; i<len; i++)
	{
		for(int j=0;j<6;j++)
		{
			if(str[i]==habijabi[j]) str[i] = ' ';
		}t main()
{
        //string str =  " I , ! . !!! am a Ullock rrrt ";
    //string str = " I , ! . !!! am a Ullock rrrt ";
	int i=0, len, j;

    len = StringLength(str);
	cleanup(str,len);
	cout<<str<<endl;
	cout << len << endl;



	/*cout << len <<endl;
	char s[100];
	int ct=0;
	for(int i=0; i<len; i++)
	{
		if(str[i]!=' ')
		{
		    s[ct]=str[i];
		    ct++;
		}
	}

	for(int i=0;i<ct;i++)
        cout<<s[i];
*/
}
