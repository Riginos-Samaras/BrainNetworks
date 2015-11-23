/* 
 * 
 * File:   main.cpp
 * Author: Riginos
 * 
 * Created on October 27, 2015, 5:40 PM
 * 
 */
#include <cstdlib>
#include <math.h>
#include <stdio.h>  
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream> 

//#include "GUI.h"
 
using namespace std;
std::ifstream infile("output1.dat"); 

std::string line;
/*
 * 
 */
//brew install qt
string getWord(int j, string word){
    string token="";
    for(int i=0; i<word.size(); i++){
        if(word[i]==' '){
            j--;
            continue;
        }
        if(j==0){
            token.push_back(word[i]);
        }
    }
    return token;

}



string ctoString(int j, string word){
      string token;
      for(int i=0; i<j; i++){
          token.push_back(word[i]);
      }
      return token;
}


int main(int argc, char** argv) {  

        string line; 
        string token; 
        std::string::size_type sz; 
        float colleration;
        string file_name;
        
         
        line="1 2";
       
        
         
            while (std::getline(infile, line))
            {

                token = getWord(2,line); 
                colleration = std::stof (token,&sz);
                if(colleration<=0)
                    continue;
                char buffer [50];
                int remp=0;
                remp=sprintf (buffer,"%f", colleration);
                std::ofstream outfile; 

                string f(buffer);

                file_name="data/"+ctoString(5,f);

                outfile.open(file_name, std::ios_base::app);
                outfile << line<<"\n"; 
                std::istringstream iss(line); 

                int a, b;
                if (!(iss >> a >> b)) { break; } // error

                // process pair (a,b)
            } 
        
        
        return 0;
        
}

