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
    int * myArr;
    int M = 65000;//file_length("everybodys_social.txt");
    int index;
    myArr = new int[M];
    read_file("everbodys_social.txt", myArr);
    int * hash_table;
    hash_table = new int[M];


    for(int i=0;i<M;i++)    //initialize the hash table to contain 0s
        hash_table[i]=0;

    for (int i = 0; i < M; i++)
    {
        index = some_function(myArr[i]);
        if (hash_table[index] == 0)
        {
            hash_table[some_function(myArr[i])] = myArr[i];
        }
        else
        {
            cout << "COLLISION! Fear not... I'll resolve it!\n";
            cout<<"\n"<<quadratic_probe(myArr[i], hash_table, M);
        }
    }
    for (int i = 0; i < 100; i++)
    {
        cout<<myArr[i]<<" "<< hash_table[some_function(myArr[i])]<<endl;
    }
}

int some_function(int val)
{
    int third, fifth, seventh, eighth;
    eighth = val % 100;
    seventh = val % 1000;
    fifth = val % 100000;
    third = val % 10000000;
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
    ifstream in;
    in.open(file_name);
    if(!in.is_open()) return false;
    char * word = new char [100];
    int s_word;
    while(in.peek()!=EOF)
    {
        in.getline(word,100,' ');
        s_word=atoi(word);
        //s_word=(int)word;
        //w.push_back(s_word);
        //w.push_back(word);
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
bool quadratic_probe(int key, int *& hash_table, int M)
{
    int pos = some_function(key) + 1;
    int i = 1;
   while (hash_table[pos] != 0)
   {
       pos = (pos + (i *i)) % M;
       i++;
   }
}
