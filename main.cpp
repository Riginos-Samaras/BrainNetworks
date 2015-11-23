/* 
 * 
 * File:   main.cpp
 * Author: Riginos
 * 
 * Created on October 27, 2015, 5:40 PM
 * 
 */

#include "node.h"
#include "nodeGraph.h"
#include "dataio.h"   
#include <cstdlib>
#include <math.h>
#include <stdio.h> 
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>   
#include <dirent.h>
#include <iomanip>

//#include "GUI.h"
 
std::ifstream infile("output.dat"); 

std::string line;
using namespace std;
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
    
    
//    GUI form;
//    form.show();
        string token; 
        std::string::size_type sz; 
        float colleration;
        string file_name;
        
         
        line="1 2";
       
        
        dataio dataInputOutput;  
        int sizeofGraph;
        dataInputOutput.findfilesindirectory("data");
        dataInputOutput.readParameters(); 
        cout<<"........Checking if size of the whole network is calculated:";
        if(dataInputOutput.get_SIZEOFGRAPH()<=0)
        { 
            sizeofGraph=dataInputOutput.findtotalNumberofNodesinData();
            cout<<"\nSize:"<<sizeofGraph;
        }
        else
            cout<<"\nAlready calculated:"<<dataInputOutput.get_SIZEOFGRAPH()<<endl;
         
        
        
        std::set<int> nodeNames;
        int leftNode;
        int rightNode; 
        string line;
        int k;
        
        
        

        
//        for (int i = 0; i < 162904; i++) {
//        
//            nodeNames.insert(i);
//        }
//          for (int i = 0; i < 52904; i++) {
//        
//            nodeNames.insert(i);
//        }
//       
        nodeGraph nodeG;
        int sizeBefore; 
        int leftPos;
        int rightPos;
        
         
            
           
 //       int left=nodeG.insertNodeBinarySearch(2); 
 //       int right=nodeG.insertNodeBinarySearch(4);    
//          
//        nodeG.insertLink(2,4,left,right);
//        
//        nodeG.insertNodeBinarySearch(9);
//         
//        
//        nodeG.insertNodeBinarySearch(8);  
//        nodeG.insertNodeBinarySearch(1000);  
//       
//        
//        
//        
//        
//        left=nodeG.insertNodeBinarySearch(3); 
//        nodeG.insertLink(3,2,-1,-1);
//        right=nodeG.insertNodeBinarySearch(5);  
//        
//        nodeG.insertLink(3,5,left,right);
//         
//        nodeG.printNodes(); 
        float rc; 
        do{
        rc=0;
        cout<<"Give correlation threshold:\n>";
        cin>>rc;       
        }while(rc<=0||rc>1);
        ///277
        
        for (int i = dataInputOutput.getdataList().size()-1; i >= 0; i--) {
            
            if(stof(dataInputOutput.getdataList()[i])<rc){break;}
            
            cout<<"data/"+dataInputOutput.getdataList()[i]<<":"<<endl;
            std::ifstream datafile("data/"+dataInputOutput.getdataList()[i], std::ios::binary | std::ios::ate);
            std::streamsize size = datafile.tellg();
            datafile.seekg(0, std::ios::beg);
//
//            std::vector<char> buffer(size);
            
            while (std::getline(datafile, line))
            {
                leftNode = stoi(getWord(0,line));
                rightNode = stoi(getWord(1,line));
                k++;
                
                
                leftPos=-1;
                rightPos=-1;
                sizeBefore=nodeNames.size();
                nodeNames.insert(leftNode);
                
                if(nodeNames.size()>sizeBefore){
                    leftPos=nodeG.insertNodeBinarySearch(leftNode);
                }
                sizeBefore=nodeNames.size();
                nodeNames.insert(rightNode);
                
                if(nodeNames.size()>sizeBefore){
                    rightPos=nodeG.insertNodeBinarySearch(rightNode);
                }
                nodeG.insertLink(leftNode,rightNode,leftPos,rightPos);

               
                std::istringstream iss(line); 
                    int a, b;
                    if (!(iss >> a >> b)) { break; } 
            }       
//            if (datafile.read(buffer.data(), size)) {
//                cout << size<<"\n"; /* worked! */
//            }
        }
        
        int nodeName=0;
        int nodeNamewithMaxNodes=0;
        int ComponentSize=0;
        int tempComponentSize=0; 
        
        
        cout<<"........Using BFS to calculate the biggest connected network"<<endl;
        for(int i=0; i<nodeG.getNodeList().size(); i++){           
            nodeName=nodeG.getNodeList()[i].getName();
            
            if(ComponentSize>nodeG.getNodeList().size()/2){
                break;
            }
            if(ComponentSize>nodeG.getNodeList().size()-i){
                break;
            }
            if(nodeG.getNodeList()[i].getVisited()==1){
                continue;
            }
            //cout<<nodeName<<":\n"; 
            tempComponentSize=nodeG.BFScountnodes(nodeName);
            if(tempComponentSize>ComponentSize){
                    ComponentSize=tempComponentSize;
                    nodeNamewithMaxNodes=nodeName;
                       }           
        } 
        
        cout<<"........Creating the giant component"<<endl;
        nodeG.BFScreatecomponent(nodeNamewithMaxNodes);
        cout<<"........Erasing other nodes"<<endl;
        nodeG.eraseNonGiantComponentsNodes();         
        cout<<"........Calculating average Degree distribution"<<endl;   
        cout<<"........Calculating average Clustering"<<endl;   
        nodeG.calculateKmean(); 
        
        cout<<"\n=========="<<endl;
        cout<<"STATISTICS"<<endl;
        cout<<"=========="<<endl;
        
        cout<<"\nCorrelation Coefficent threshold rc':"<<rc;
        cout<<"\nTotal Network size:"<<dataInputOutput.get_SIZEOFGRAPH();
        cout<<"\nGiant Component Size: "<<ComponentSize<<" \nCompared to the Network: "<<setprecision(4)<<(float)ComponentSize/(float)dataInputOutput.get_SIZEOFGRAPH()*100<<"%"<<"\nBFS started from node: "<<nodeNamewithMaxNodes<<"\n";
        
       // cout<<"\nSize of  component is:"<<nodeG.getNodeList().size();     
        //dataInputOutput.createGML(nodeG.getNodeList());
         

        cout<<"\nAverage Degree:"<<nodeG.getKmean()<<endl;
        cout<<"Average Clustering:"<<nodeG.getavClustering()<<endl;
        cout<<"\nmin degree:"<<nodeG.getminDegree()<<endl;
        cout<<"max degree:"<<nodeG.getmaxDegree()<<endl;
        
        
        
        if(false){
            while (std::getline(infile, line))
            {
                
                token = getWord(2,line); 
                colleration = std::stof (token,&sz);
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
        }
        
        
       
        
        char ans;
        cout<<"Wanna create gml file for Gephi? (y/n) It may take some time...";
        cin>>ans;
        if(ans=='y'){
            std::ofstream outfile; 
            outfile.open ("plots/Gephi.gml"); 
            outfile<< "Creator \"Riginos Samaras on Thu Nov 4 20:32:53 2015\"\n";
            outfile <<"graph\n[\n";
            for(int i=0; i<nodeG.getNodeList().size(); i++){
              outfile <<"node\n"
                      "[\n"
                      "id "<<nodeG.getNodeList()[i].getName()<<"\n"
                      "label "<<nodeG.getNodeList()[i].getName()<<"\n"
                      "]\n";

            }
            for(int i=0; i<nodeG.getNodeList().size(); i++){
                node* nnode=nodeG.findNode(nodeG.getNodeList()[i].getName()); 
                cout<<nnode->getName();
                for(int j=0; j<nnode->linkedNodes.size(); j++)
                {   
                    cout<<"edge\n"
                            "[\n"
                            "source "<<nnode->getName()<<"\n"
                            "target "<<nnode->linkedNodes[j]<<"\n"
                            "]\n";
                
                    outfile <<"edge\n"
                            "[\n"
                            "source "<<nnode->getName()<<"\n"
                            "target "<<nnode->linkedNodes[j]<<"\n"
                            "]\n";
                }
            }
            outfile <<"\n]";
            outfile.close(); 
        }
        
        
        return 0;
        
}

