/*

The module serves the 9th function of the wiki, which is just a requisite for the login function.

Creates a hash for password, and stores it in "pass.db".

*/

#include<iostream>  //for basic IO
#include<fstream>   //for file handling
#include<unistd.h>	//for getpass()
#include<string.h>  //for strcmp()

using namespace std;  //to avoid std::cin, etc.

int convert (char *);
int hash[256];

int main()
{
	char name[256], pass[256];
	ofstream obj("pass.db",ios::app);
	cout<<"login:\t";
	cin.getline(name, 256);
	strcpy(pass,getpass("password:\t"));
	convert(pass);	
	for(unsigned int i=0; i<strlen(pass) ;i++)
	{
		obj<<hash[i]<<"0x";   //saves the hashed password to "pass.db" file.
	}
	obj<<endl;
	
	return 0;
}

int convert (char p[256])
{
	int l=strlen(p);
	for (int i=0; i<l; i++)
	{
		hash[i]=int(p[i]);
	}
	return 0;
}
