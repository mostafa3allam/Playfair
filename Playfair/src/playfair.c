#include<stdio.h>
#define size 100
#define ksize 30
//call the function responsible for editing the plain text
void plainedit(char plain[]){
	char newplain[size];
	int x=0;
	for(int i=0;plain[i]!='\0';i++){
		//if there is an i or j in the string, it's replaced by a j letter
		if(plain[i]==105||plain[i]==106)
			plain[i]=106;
		//if there are spaces between the words of the plain text,
		//they won't be copied to the string newplain
		if(plain[i]!=32){
			newplain[x]=plain[i];
			x++;
		}
	}
	newplain[x]='\0';
	for(int i=0;newplain[i]!='\0';i=i+2){
		//we cipher 2 letters by 2 letters. if the 2 letters consists of the same letter,
		//these instructions are responsible for putting an 'x' between the 2 letters
		if(newplain[i]==newplain[i+1]){
			for(int j=x;j>i;j--)
				newplain[j+1]=newplain[j];
			newplain[i+1]='x';
			x++;
		}
	}
	//if the number of plain letters is odd, it adds an 'x' to the end
	if(x%2!=0){
			newplain[x]='x';
			x++;
		}
	newplain[x]='\0';
	//copies the string newplain to the string plain
	for(int i=0;newplain[i]!='\0';i++)
		plain[i]=newplain[i];
	plain[x]='\0';
}
/* a function responsible for
putting the string of the key and alphabets in the matrix*/
void matrixx(char key[],char cmatrix[5][6]){
			int z=0;
			for(int x=0;x<5;x++){
				for(int y=0;y<6;y++){
					//at the end of any string, there must be a '\0' operator to
					//indicate the end of the string
					if(y==5)
						cmatrix[x][y]='\0';
					else {
						//Enters the characters into the 2D array
						if(key[z]!='\0'){
							cmatrix[x][y]=key[z];
							z++;
						}
					}
				}
			}
}
/* a function responsible for
making the key distinct and adding the rest of the alphabets to it*/
void makedistinct(char key[]){
		char newkey[ksize];
		char n=0;
		int x=0;
		//Get a char and compare it to the rest of the string
		for(int i=0;key[i]!='\0';i++){
			char current=key[i];
			//if there is an i or j in the string, it's replaced by a j letter
			if(current==105||current==106)
				current=106;
			for(int m=0;key[m]!='\0';m++){
				//checks if the character exists in another position in the entered string (key)
				if(current==key[m]&&m!=i)
					//if it's, a flag is changed
					n=1;
			}
			//if the character isn't found, it's added to the string newkey
			if(n==0){
				newkey[x]=current;
				x++;
			}
			else{
				//if the character is found in the entered string, it checks whether
				//it's in the string newkey or not
				int xyz=0;
				for(int j=0;j<x;j++)
					if(current==newkey[j])
						xyz++;
				//if the character isn't is the string newkey, it's added to it
				if(xyz==0){
					newkey[x]=current;
					x++;
				}
				//sets the flag to 0 again
				n=0;
			}
		}
		//this part until the end of the function is responsible for adding the rest of
		//the alphabets to the string newkey
		char b=97;
		char bool;
		while(b<123){
			bool=0;
			//it adds the 2 letters i and j as the letter j
			if(b==105||b==106)
				b=106;
			//checks if the character b in the string newkey
			for(int j=0;j<x;j++)
				if(b==newkey[j])
					bool=1;
			//if it's not found ,it's added to the string
			if(bool==0){
				newkey[x]=b;
				b++;
				x++;
			}
			else{
				b++;
			}
		}
		//end of string
		newkey[x]='\0';
		//copy the string newkey to the string key
		for(int i=0;newkey[i]!='\0';i++)
			key[i]=newkey[i];
		key[x]=newkey[x];
}
//the ciphering function
void playfair(char plain[],char cmatrix[5][6]){
	char cipher[size];
	int a,b,c,d,x;
	for(int i=0;plain[i]!='\0';i=i+2){
		//gets the indexes of each letter(in the 2D matrix) of the 2 letters we cipher at a time
		for(int n=0;n<5;n++)
			for(int m=0;m<5;m++){
				if(plain[i]==cmatrix[n][m]){
					a=n;
					b=m;
				}
				if(plain[i+1]==cmatrix[n][m]){
					c=n;
					d=m;
				}
			}
		//if the 2 letters in the same row, each letter is moved right by 1
		//if one of the letters is already at the rightmost position of the row, then we have
		//the leftmost of the row
		if(a==c){
			if(b<4)
				b++;
			else
				b=0;
			if(d<4)
				d++;
			else
				d=0;
		}
		//if the 2 letters in the same column, each letter is moved down by 1
		//if one of the letters is already at the end of the column, then we have
		//the top of the column
		else if(b==d){
			if(a<4)
				a++;
			else
				a=0;
			if(c<4)
				c++;
			else
				c=0;
		}
		//if it forms a rectangular, we swap the letters with the ones in each corner
		//of the rectangular(each letter must be swapped with the one in its row)
		else{
			int temp=d;
			d=b;
			b=temp;
		}
		//get the letters from the matrix into the cipher string
		cipher[i]=cmatrix[a][b];
		cipher[i+1]=cmatrix[c][d];
		x=i+2;
	}
	cipher[x]='\0';
	//prints the cipher text
	puts("CipherText is:");
	puts(cipher);
}
int main(){
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		char plain[size],key[ksize];
		//Get the original text and the key
		puts("Enter the plain text: \n");
		gets(plain);
		puts("Enter the key: \n");
		gets(key);
		//prints the original plain text before editing
		puts("PlainText is: ");
		puts(plain);
		/*call the function responsible for
		making the key distinct and adding the rest of the alphabets to it*/
		makedistinct(key);
		char cmatrix[5][6]={0};
		/*call the function responsible for
		putting the string of the key and alphabets in the matrix*/
		matrixx(key,cmatrix);
		//call the function responsible for editing the plain text
		plainedit(plain);
		//call the ciphering function
		playfair(plain,cmatrix);
		//End of the program
		return 0;
}
