#include <thread>         // std::this_thread::sleep_for
#include <chrono>   
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

class encryption {
	private:
		char string[1000] ;
		char key[1000] ;
		
		void copy_string(char *s)
		{
			for( int i = 0 ; i < strlen(s); ++i)
			string[i] = s[i] ;
		}
		
		void copy_key(char *s)
		{
			for( int i = 0 ; i < strlen(s); ++i)
			key[i] = s[i] ;
		}
		
		void shift_r(int i)
		{
			string[strlen(string)+2]=NULL;
			for(int j = strlen(string)+1; j >= i ; j--)
			string[j+1] = string[j] ;
		}
		
		void shift_l(int i)
		{
			for(int j = i; j <strlen(string)-1; j++)
			string[j] = string[j+1] ;
			string[strlen(string)-1]=NULL;
		}
	public:
		encryption(char *s)
		{
			srand(time(NULL));
			copy_string(s);
			for(int i = 0; i< 2*strlen(string)-1; ++i )
			key[i]='1';
		}
		
		void encrypt()
		{
			for(int i = 0, j = 0 ; j < strlen(key) && i<strlen(string) ; )
			{
				string[i++] += key[j++]-48 ;
				if(key[j] == NULL) break;
				for( int p = 0 ; p < (key[j]-48)%3 ; ++p )
				{
					shift_r(i);
					string[i++] = char(rand()%10+48);
				}				
			}
			
		}
		
		void decrypt()
		{
			for(int i = 0, j = 0 ; j < strlen(key) && i<strlen(string); )
			{
				string[i++] -= key[j++]-48 ;
				if(key[j] == NULL) break;
				for(int p = 0 ; p < (key[j]-48)%3 ; ++p)
				shift_l(i);
			}
		}
		
		void print()
		{
			puts(string);
		}

		void add_key(char *i)
		{
			copy_key(i);
		}
		
};

int main()
{
/*
	char c[1000] ;
	cout << "String za enkripciju: " ;
	gets(c);
//	char k[1000]="111111111" ;
//	gets(k);
	encryption string(c);
	string.print();
//	string.add_key(k);
	string.encrypt();
	string.print();
	string.decrypt();
	string.print();*/



	int option;
	char word[100];
	printf("Enter phrase for encryption:");
	gets(word);
	encryption object1(word);
	while(1){

		printf("Choose option:\n");
		printf("(1) Encrypt\n");
		printf("(2) Decrypt\n");
		printf("(3) Add key\n");
		printf("(4) Print word\n");
		printf("(0) Exit\n");
		printf("Option:");
		scanf("%d",&option);
		if(option==4)object1.print();
		if(option==3){
			printf("Enter number:");
			int key;
			scanf("%d",&key);
			object1.add_key(key);
		}
		if(option==1)object1.encrypt();
		if(option==2)object1.decrypt();

		std::this_thread::sleep_for (std::chrono::seconds(1));
		for(int i=0;i<100;i++)printf("\n");
		if(option==0)break;
	}
	return 0;
}
