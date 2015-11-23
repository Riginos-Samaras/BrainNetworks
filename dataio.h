/* 
 * File:   dataio.h
 * Author: Riginos
 *
 * Created on October 29, 2015, 12:25 PM
 */

#ifndef DATAIO_H
#define	DATAIO_H

#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <dirent.h>
#include <fstream> 
#include <sstream>  
#include "node.h"

using namespace std;


 
 
    class dataio{
    private:
        std::vector<std::string> dataList;
        int SIZEOFGRAPH=-1;
    public:

        dataio();
        int findfilesindirectory(const char *);
        void readparameters();
        void printdirectory();
        std::vector<std::string> getdataList();      
        int findtotalNumberofNodesinData();
        void readParameters();
        void writetoParameters(std::string name,int value);       
        std::string getWord(int, std::string );     
        int get_SIZEOFGRAPH();
        //void createGML(std::vector<node>);
    };


 

#endif	/* DATAIO_H */

