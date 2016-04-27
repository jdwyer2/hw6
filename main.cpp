#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <stdlib.h>
#include<array>

using namespace std;

bool read_file(char * file_name,int  w[]);
bool quadratic_probe(int key, int *& hash_table, int M);
int file_length(char * file_name);
int some_function(int val);

int main()
{
    int  myArr[65000];
    int M = 65000;//file_length("everybodys_social.txt");
    int index;
    //myArr = new int[M];
    read_file("everybodys_socials.txt", myArr); //read file into array
    int * hash_table;  //dynamically allocate hastable
    hash_table = new int[M];

    //fill hashtable with 0s
    for(int i=0;i<M;i++)
    {
        hash_table[i]=0;
    }
    //get int from user to use mod with
    int my_int;
    while(!(my_int < 450000000 && my_int > 0))
    {
    cout<<"Enter a number between 1 and 450,000,000: ";
    cin>>my_int;
    }
    //go through array of ssns, hash
    for (int i = 0; i < M; i++)
    {
        //cout<<myArr[i]<<endl;
        index = some_function(myArr[i]); //retrieve index where ssn belongs

        if (hash_table[index] == 0) //test if its empty
        {
            hash_table[index] = myArr[i]; //place ssn
        }
        else //ssn has already been placed here
        {
            //cout << "COLLISION! Fear not... I'll resolve it!\n";
            quadratic_probe(myArr[i], hash_table, my_int/*M*/); //find a new place for ssn
        }
    }
    ofstream out;
    out.open("hashed_socials.txt");
    for (int i = 0; i <M -1; i++) //write hashtable to new file, dont add comma at the end
    {
        if (i != 64999)
        {
            out<<hash_table[i]<<",";
        }
        else
        {
            out<<hash_table[i];
        }
    }
    out.clear();
    out.close();
}
//hash function
int some_function(int val)
{
    int third, fifth, seventh, eighth;
    eighth = (val % 100)/10; //get the eighth digit of ssn
    seventh = (val % 1000)/100; //get the seventh digit of ssn
    fifth = (val % 100000)/10000; //get the fifth digit of ssn
    third = (val % 10000000)/1000000; //get the third digit of ssn
    char * e = new char [1]; //declare new chars
    char * s = new char [1];
    char * f = new char [1];
    char * t = new char [1];
    sprintf(e, "%i", eighth); //place digits into chars
    sprintf(s, "%i", seventh);
    sprintf(f, "%i", fifth);
    sprintf(t, "%i", third);
    char * string1 = strcat(t, f); //concatenate chars into one char
    char * string2 = strcat(string1, s);
    char * string3 = strcat(string2, e);
    int hash = atoi(string3); //turn chars into int to be used as an index
    return hash;
}

bool read_file(char * file_name,int w[])
{
    int i = 0;
    //char comma = ',';
    ifstream in;
    in.open(file_name);
    if(!in.is_open()) return false;
    char * word = new char [100];
    int s_word;
    while(in.peek()!=EOF)
    {
        in.getline(word,100,',');
        s_word=atoi(word);
        w[i] = s_word;
        i++;
    }
    in.clear();
    in.close();
    return true;
}
int file_length(char * file_name)
{
    int count = 0;
    ifstream in;
    in.open(file_name);
    if (!in.is_open()) return false;
    char * word = new char [100];
    while (in.peek()!=EOF)
    {
        in.getline(word,100, ' ');
        count ++;
    }
    in.clear();
    in.close();
    return count;
}

bool quadratic_probe(int key, int *& hash_table, int M) {
    int pos;
    pos = some_function(key);
    for(int i= (pos+(i*i)%M); i  != 0; i++){ //start at pos...add i^2 where i increments after each loop
        if (hash_table[i] == 0) { //test if new pos is empty
            hash_table[i] = key; //place ssn
            return true;
        }
    }
    return false;
}
