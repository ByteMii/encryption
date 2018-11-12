#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

class encryption
{
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
	string.print();
}
