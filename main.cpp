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
    read_file("everybodys_socials.txt", myArr);
    int * hash_table;
    hash_table = new int[M];


    for(int i=0;i<M;i++)
    {
        hash_table[i]=0;
    }
    int my_int;
    while(!(my_int < 450000000 && my_int > 0))
    {
    cout<<"Enter a number between 1 and 450,000,000: ";
    cin>>my_int;
    }

    for (int i = 0; i < M; i++)
    {
        //cout<<myArr[i]<<endl;
        index = some_function(myArr[i]);

        if (hash_table[index] == 0)
        {
            hash_table[index] = myArr[i];
        }
        else
        {
            //cout << "COLLISION! Fear not... I'll resolve it!\n";
            quadratic_probe(myArr[i], hash_table, my_int/*M*/);
        }
    }
    ofstream out;
    out.open("hashed_socials.txt");
    for (int i = 0; i <M; i++)
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
int some_function(int val)
{
    int third, fifth, seventh, eighth;
    eighth = (val % 100)/10;
    seventh = (val % 1000)/100;
    fifth = (val % 100000)/10000;
    third = (val % 10000000)/1000000;
    char * e = new char [1];
    char * s = new char [1];
    char * f = new char [1];
    char * t = new char [1];
    sprintf(e, "%i", eighth);
    sprintf(s, "%i", seventh);
    sprintf(f, "%i", fifth);
    sprintf(t, "%i", third);
    char * string1 = strcat(t, f);
    char * string2 = strcat(string1, s);
    char * string3 = strcat(string2, e);
    int hash = atoi(string3);
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
    for(int i= (pos+(i*i)%M); i != pos; i++){
        if (hash_table[i] == 0) {
            hash_table[i] = key;
            return true;
        }
    }
    return false;
}
