/*

TWiki! The Small Wiki!

This file is a port from scratch of mainwithlcass.cpp for DOS.

Version 1.3

Author : Aaruni Kaushik ( aaruni@krow.me | http://u.krow.me/1197 )

Ramirez! Port to DOS!

*/

#include<iostream.h>	//for basic IO operations
#include<conio.h>	//DOS only. For console related IO operations. also for getpass().
#include<fstream.h>	//for file related IO operations.
#include<string.h>	//for stringtype related operations
#include<stdlib.h>	//for system call operations
#include<ctype.h>	//for charactertype related operations
#include<time.h>	//for timestamps/logs
#include<stdio.h>	//for "remove" or "delete" or something similar

char uname[1024];	//for logging user name
int hash[256];		//required for hash1 and hash2

int hash1();		//required for register
int hash2();		//required for login
int hashi();		//required for initializing the password database
int index();		//required for search
int login();		//login function
int logout();		//logout function
int registeR();		//new user register function
int convert (char *);	//required for hash1 and hash2

class io
{
	char out[1024],in[4096],ch,ttl[1024],fint[4096];	//large sizes because I have plent of RAM to spare.
	int flag;
	fstream outfile;					//fstream object because I use ios::in to check whether or not the file exists.
	ifstream infile;
	ifstream obj;
	ofstream log;	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;							//for timestamps for logfile
	struct tm * timeinfo;						//for timestamps for logfile
	
	public:
		io()
		{
			strcpy(in,"\0");
			strcpy(ttl,"\0");
			ch='\0';
			strcpy(fint,".\\content\\data\\");
			flag=0;
			infile.open("index.out");
			obj.open("index.out");
			log.open(".\\content\\logs\\log.log",ios::app);
		}
		
		int write();
		int read();
		int prindex();
		int search();
};

int main()
{			
	int ch,logged=1;			
	io obj;
	strcpy(uname,"\0");
	ofstream log(".\\content\\logs\\log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
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
		cout<<"\t1.Sign Up\n\t2.Sign In\n\t3.Logout\n\t4.List Files\n\t5.View File\n\t6.Write File\n\t7.Search File\n\t8.Exit\n\n";
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
				logged=logout();
				break;
				
			case 4:
				obj.prindex();
				break;
			case 5:
				obj.read();
				break;
			case 6:
				if(!logged)
				{
					obj.write();
					index();
				}	
				else
				{
					cout<<"Please log in to open the file in edit mode\n\n";
					time (&rawtime);
					timeinfo = localtime (&rawtime);
					log<<asctime(timeinfo)<<'\t'<<"Write blocked. User not logged in "<<endl;
					
				}
				break;
			case 7:
				obj.search();
				break;
			case 8:
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"End of log "<<endl;
				return 0;
				
			default:
				cout<<"Please input a valid chooice\n";
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Invalid choice entered by user";
				if(!logged)
				{
					cout<<"\t"<<uname<<endl;
				}
				else 
					cout<<endl;
				break;
		}
	}
}

int io::read()
{
	cout<<"Please enter the filename to be opened\n";
	cin.getline(ttl,1024);
	cin.getline(ttl,1024);
	strcpy(fint,".\\content\\data\\");
	strcat(fint,ttl);
	infile.close();
	infile.open(fint);
	if(infile)
	{	
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"File\t"<<ttl<<"\tsuccesfully opened for reading."<<endl;
		infile.getline(out,80);
	}
	else
	{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Error : File\t"<<ttl<<"\tdoes not exist."<<endl;
		cout<<"File does not exist\n";
		cout<<fint<<endl;
		cout<<infile<<endl;
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

int io::write()
{						
	cout<<"Please enter the title of the file\n";
	cin.getline(ttl,1024);
	cin.getline(ttl,1204);
	strcpy(fint,".\\content\\data\\");
	strcat(fint,ttl);
	outfile.open(fint,ios::in);
	if(!outfile)				// if open fails, the stream objects stores Null(zero) value.
	{
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Created file\t"<<ttl<<"\tby user\t"<<uname<<endl;
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
				log<<asctime(timeinfo)<<'\t'<<"Opened file for overwriting"<<"\tby user\t"<<uname<<endl;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Overwrote file\t"<<ttl<<"\tby user\t"<<uname<<endl;
			}
			else
			{
				outfile.close();			//may not be needed. will test later
				outfile.open(fint,ios::out|ios::app);	//ios::app appends to the file. we aint replacing stuff.
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Opened file\t"<<ttl<<"\tfor appending by user\t"<<uname<<endl;
				time (&rawtime);
				timeinfo = localtime (&rawtime);
				log<<asctime(timeinfo)<<'\t'<<"Appending to file\t"<<ttl<<"\tby user\t"<<uname<<endl;
			}
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
	log<<asctime(timeinfo)<<'\t'<<"Closed file\t"<<ttl<<"\tafter output operation by user\t"<<uname<<endl;
	return 0;
}

int io::search()
{
	char in[256],out[256];
	ofstream log(".\\content\\logs\\log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	
	strcpy(fint,".\\content\\data\\");
	
	cout<<"Please enter the name of file to be searched\n";
	cin.getline(in,256);
	cin.getline(in,256);
	strcat(fint,in);
	ifstream infile(fint);
	if(!infile)	//if the file doesn't open, infile stores NULL (0).
	{
		cout<<"The file\t"<<in<<"\tdoes not exist!\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"File\t"<<in<<"\tnot found by search function"<<endl;
		return 1;
	}
	else
	{
		cout<<"File\t"<<in<<"\texists!\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"File\t"<<in<<"\tfound by search function"<<endl;
	}
	return 0;
}

int registeR()
{
	char in[1024],out[1024];
	int sflag=0;
	ofstream outp;		//opening a file using the object constructer fails under DOS for some reason. Tested across versions and machines
	outp.open(".\\content\\user\\user.db",ios::app);
	ifstream check(".\\content\\user\\user.db",ios::in);
	ofstream log(".\\content\\logs\\log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
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
		log<<asctime(timeinfo)<<'\t'<<"User creation failed. User\t"<<in<<"\talready exists."<<endl;
		return 1;
	}
	outp<<in<<endl;
	hash1();
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Created user\t"<<in<<'\t'<<endl;
	return 0;
}

int io::prindex()
{
	ifstream obj("index.out");
	ofstream log(".\\content\\logs\\log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
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

int login()
{
	char in[1024],com[1024],pass[1024];
	int k=0;
	ifstream ob1(".\\content\\user\\pass.db"), ob2(".\\content\\user\\user.db");
	ofstream log(".\\content\\logs\\log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
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
				log<<asctime(timeinfo)<<'\t'<<"Successfully looged in\t"<<in<<endl;
				strcpy(uname,in);
				return 0;
			}
		}
		remove("temp.db");
		cout<<"Bad Password\n";
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"User\t"<<in<<"\tsubmitted wrong password."<<endl;
		return 1;
	}
	cout<<"User not registered\n";
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"User\t"<<in<<"\tnot registered"<<endl;
	return 2;
}

int index()		//linux specific. makes an "index.out" with names of all file in the directory.
{
	ofstream log(".\\content\\logs\\log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	fstream obj;
	ofstream ob;
	
	system("dir .\\content\\data/ > index.out");
	obj.open(".\\content\\user\\user.db",ios::in);
	if(!obj)
	{
		ob.open(".\\content\\user\\user.db");
		ob<<"admin"<<endl;
	}
	ob.close();
	obj.close();
	obj.open(".\\content\\user\\pass.db",ios::in);
	if(!obj)
	{
		ob.open(".\\content\\user\\pass.db");
		hashi();
	}
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"Index successfuly created"<<endl;
	
	return 0;
}

int hash1()
{
	//Hashing algorithm is simple. Converts each caracter to its ascii value, adds an '0x' between them, and stores them in a text file
	char name[256], pass[256];
	ofstream obj(".\\content\\user\\pass.db",ios::app);
	
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
	ofstream obj(".\\content\\user\\pass.db");
	
	convert(pass);	
	for(unsigned int i=0; i<strlen(pass) ;i++)
	{
		obj<<hash[i]<<"0x";
	}
	obj<<endl;
	
	return 0;
}

int logout()
{
	ofstream log("./content/logs/log.log",ios::app);	//because you always only append to the logfile. overwriting logfile = phail.
	time_t rawtime;				//timestamps for logfile
	struct tm * timeinfo;			//timestamps for logfile
	if(!strcmp(uname,"\0"))
	{	
		cout<<"Must be logged in to log out!\n";
		
		time (&rawtime);
		timeinfo = localtime (&rawtime);
		log<<asctime(timeinfo)<<'\t'<<"Logout function activated, but, can't logout if not logged in!\n";
		return 2;	//this is both a non-zero value and an error code
	}
	
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"User\t"<<uname<<"\tlogging out\n";
	strcpy(uname,"\0");
	cout<<"User succesfully logged out!\n";
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	log<<asctime(timeinfo)<<'\t'<<"User logged out succesfully\n";
	return 1;	//so that logged variable stores non-zero. is not an error code.
}
