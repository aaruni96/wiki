/*

This file compiles all aspects of the project into a single file. Lets just hope it doesn't get messy.

Version 1.0

Author : Aaruni Kaushik ( aaruni@krow.me | http://u.krow.me/1197 ).

Collaborators : None (so far).

Acknowledgements : 	Vineet Kumar : counsel
			Smit Shah : counsel
			Ashish Kaushik : counsel
			em gee ell ae : counsel
			http://cplusplus.com/ : reference
			some more people : content/source
			
Carpe Diem!

*/

#include<iostream>	//for basic IO operations
#include<fstream>	//for file IO operations
#include<unistd.h>	//for getpass()
#include<string.h>	//for stringtype related operations
#include<cstdlib>	//for system call operations
#include<ctype.h>	//for character type related operations
#include<time.h>	//for timestamps/logs

using namespace std;	//to avoid writing std::cin, std::cout, std::fstream, etc.

int hash1();		//required for register
int hash2();		//required for login
int hashi();		//required for initializing the password database
int index();		//required for search
int login();		//login function
int read();		//read file function
int registeR();		//new user register function
int search();		//search function
int write();		//write/append file function
int prindex();		//prints the content of index file to screen
int convert (char *);	//required for hash1 and hash2

int hash[256];		//required for hash1 and hash2

int main()
{			
	int ch,logged=1;			
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	
	time (&rawtime);			//pre-requisite section
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Begin logging to file "<<endl;
	index();		
	
	cout<<"\n\n\t\tWelcome to Twiki!\n\n\n";		
	while(1)
	{
		cout<<"\t\tMenu\n";		
		cout<<"\t1.Sign Up\n\t2.Sign In\n\t3.List Files\n\t4.View File\n\t5.Write File\n\t6.Search File\n\t7.Exit\n\n";
		cin>>ch;
		switch (ch)
		{
			case 1:
				registeR();
				break;
			case 2:
				logged=login();		//to ascertain whether the user has logged in
				break;
			case 3:
				prindex();
				break;
			case 4:
				read();
				break;
			case 5:
				if(!logged)
				{
					write();
				}	
				else
				{
					cout<<"Please log in to open the file in edit mode\n\n";
					time (&rawtime);
					timeinfo = localtime (&rawtime);
					log<<asctime(timeinfo)<<'\t'<<"Write blocked. User not logged in "<<endl;
					
				}
				break;
			case 6:
				search();
				break;
			case 7:
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"End of log "<<endl;
				return 0;
		}
	}
}


int hash1()
{
	//Hashing algorithm is simple. Converts each caracter to its ascii value, adds an '0x' between them, and stores them in a text file
	char name[256], pass[256];
	ofstream obj("./content/user/pass.db",ios::app);
	
	cout<<"login:\t";
	cin.getline(name, 256);
	strcpy(pass,getpass("password:\t"));
	convert(pass);	
	for(unsigned int i=0; i<strlen(pass) ;i++)
	{
		obj<<hash[i]<<"0x";
	}
	obj<<endl;
	
	return 0;
}

int convert (char p[256])		//hash depends on this function
{
	int l=strlen(p);
	for (int i=0; i<l; i++)
	{
		hash[i]=int(p[i]);
	}
	return 0;
}

int index()		//linux specific. makes an "index.out" with names of all file in the directory.
{
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	fstream obj;
	ofstream ob;
	
	system("ls ./content/data/ > index.out");
	obj.open("./content/user/user.db",ios::in);
	if(!obj)
	{
		ob.open("./content/user/user.db");
		ob<<"admin"<<endl;
	}
	ob.close();
	obj.close();
	obj.open("./content/user/pass.db",ios::in);
	if(!obj)
	{
		ob.open("./content/user/pass.db");
		hashi();
	}
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Index successfuly created "<<endl;
	
	return 0;
}

int hash2()		//same as the first hash function, just works on a different file.
{
	char pass[1024];
	ofstream obj("temp.db");
	
	strcpy(pass,getpass("password:\t"));
	convert(pass);	
	for(unsigned int i=0; i<strlen(pass) ;i++)
	{
		obj<<hash[i]<<"0x";
	}
	obj<<endl;
	
	return 0;
}

int hashi()		//basicall same as the first and second hash functions, just works on a different file.
{
	char pass[]="password";
	ofstream obj("./content/user/pass.db");
	
	convert(pass);	
	for(unsigned int i=0; i<strlen(pass) ;i++)
	{
		obj<<hash[i]<<"0x";
	}
	obj<<endl;
	
	return 0;
}

int login()
{
	char in[1024],com[1024],pass[1024];
	int k=0;
	ifstream ob1("./content/user/pass.db"), ob2("./content/user/user.db");
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	
	cout<<"login\t";
	cin.getline(in,1024);		//to clear write buffer
	cin.getline(in,1024);
	for(int i=0;in[i]!='\0';i++)
	{
		in[i]=tolower(in[i]);
	}
	while(!ob2.eof())
	{
		ob2.getline(com,1024);
		if(!strcmp(in,com))
		{
			k=0;
			break;
		}
		k=1;
	}
	if(!k)
	{
		hash2();
		ifstream ob3("temp.db");
		ob3.getline(pass,1024);
		while(!ob1.eof())
		{
			ob1.getline(com,1024);
			if(!strcmp(pass,com))
			{
				cout<<"Login Succesful\n";
				remove("temp.db");
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Successfully looged in "<<in<<endl;
				return 0;
			}
		}
		remove("temp.db");
		cout<<"Bad Password\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"User "<<in<<" submitted wrong password."<<endl;
		return 1;
	}
	cout<<"User not registered\n";
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"User "<<in<<" not registered"<<endl;
	return 2;
}

int read()
{
	char out[80],ttl[1024],fint[4096]="./content/data/";
	ifstream infile;
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile

	cout<<"Please enter the filename to be opened\n";
	cin.getline(ttl,1024);
	cin.getline(ttl,1024);
	strcat(fint,ttl);
	infile.open(fint);
	if(infile)
	{	
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"File "<<ttl<<" succesfully opened for reading."<<endl;
		infile.getline(out,80);
	}
	else
	{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Error : File "<<ttl<<" does not exist."<<endl;
		cout<<"File does not exist\n";
		return 1;
	}
		
	while(!infile.eof())
	{  
		cout<<out<<endl;
		infile.getline(out,80);
	}
	cout<<endl;
	return 0;
}

int prindex()
{
	ifstream obj("index.out");
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	char out[1024];
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	if(!obj)
	{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Fatal error : index could not be opened\n";
		cout<<"Could not open index file for content listing\n";
		return 1;
	}
	
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Index successfully opened\n";
	obj.getline(out,80);
	while(!obj.eof())
	{
		cout<<out<<endl;
		obj.getline(out,80);
	}
	cout<<endl;
	return 0;
}
	

int registeR()
{
	char in[1024],out[1024];
	int sflag=0;
	ofstream outp("./content/user/user.db",ios::app);
	ifstream check("./content/user/user.db",ios::in);
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	
	
	cout<<"Please enter name for registry\n";
	cin.getline(in,1024);
	cin.getline(in,1024);
	for(int i=0;in[i]!='\0';i++)
	{
		in[i]=tolower(in[i]);
	}
	check.getline(out,1024);
	while(!check.eof())
	{ 
		for(int j=0;out[j]!='\0';j++)
		{
			out[j]=tolower(out[j]);
		}
		if(!strcmp(in,out))
		{
			sflag=0;
			break;
		}
		sflag=1;
		check.getline(out,1024);
	}
	
	check.close();
	if (!sflag)
	{
		cout<<"The username is already registered\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"User creation failed. User already exists."<<endl;
		return 1;
	}
	outp<<in<<endl;
	hash1();
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Created user"<<endl;
	return 0;
}

int search()
{
	char in[256],out[256];
	int flag=0;
	ifstream infile("index.out");
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	
	if(!infile)
	{
		cout<<"The programmer messed up, and the index isn't created. Go sue him and/or update your copy of the wiki\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Fatal error : index file not found "<<endl;
		return 1;
	}
	
	cout<<"Please enter the name of file to be searched\n";
	cin.getline(in,256);
	cin.getline(in,256);
	while(!infile.eof())
	{
		infile.getline(out,256);
		if(strcmp(in,out))
		{
			flag=1;
		}
		else
		{
			cout<<"File "<<out<<" exists!\n";
			time (&rawtime);
			timeinfo = localtime (&rawtime);
			log<<asctime(timeinfo)<<'\t'<<"Search function found a match for "<<in<<endl;
			return 0;
		}
	}
	if(flag)
	{
		cout<<"File does not exist\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Search function did not find "<<in<<endl;
		return 0;
	}
	return 0;
}

int write()
{
	char in[4096],ch,ttl[1024],fint[4096]="./content/data/";		//large sizes because I have plent of RAM to spare.
	int flag=0;
	fstream outfile;			//fstream object because I use ios::in to check whether or not the file exists.
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//for timestamps for logfile
	struct tm * timeinfo;			//for timestamps for logfile
						
	cout<<"Please enter the title of the file\n";
	cin.getline(ttl,1024);
	cin.getline(ttl,1204);
	strcat(fint,ttl);
	outfile.open(fint,ios::in);
	if(!outfile)				// if open fails, the stream objects stores Null(zero) value.
	{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Created file "<<ttl<<endl;
		outfile.open(fint,ios::out);
	}
	else
	{
		outfile.open(fint,ios::in);
		if(!outfile)
		{
			cout<<"The file exists. Replace file?\n";
			cin>>ch;
			flag=1;
			if(toupper(ch)=='Y')
			{
				outfile.close();		//may not be needed. will test later
				outfile.open(fint,ios::out);	//ios::out replaces the good file
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Opened file for overwriting"<<endl;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Overwrote file "<<ttl<<endl;
			}
			else
			{
				outfile.close();			//may not be needed. will test later
				outfile.open(fint,ios::out|ios::app);	//ios::app appends to the file. we aint replacing stuff.
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Opened file for appending"<<endl;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Appending to file "<<ttl<<endl;
			}
		}
		else
		{
			;	//because the program refuses to run without this, or so I think
		}
	}
	cout<<"Please enter file contents (Enter to submit)\n";
	if(flag)
	cin.getline(in,4096);			//this is simply to flush out the input buffer from the previous cin operation
	cin.getline(in,4096);			//this one actually gets the input
	outfile<<in<<endl;
	outfile.close();
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Closed file after output operation "<<ttl<<endl;
	return 0;
}
