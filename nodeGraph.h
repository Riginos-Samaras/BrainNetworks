/* 
 * File:   nodeGraph.h
 * Author: Riginos
 *
 * Created on February 10, 2015, 8:14 PM
 */

#ifndef NODEGRAPH_H
#define	NODEGRAPH_H

#include "node.h"
#include <algorithm>  
#include <exception>
#include <ext/hash_map> 
#include <iostream>
#include <fstream>
using namespace __gnu_cxx;

class nodeGraph{
    private:
         std::vector<node> nodeList;
         std::vector<node> giantComponent;
         std::vector<node *> queue;
         int maxDegree;
         int minDegree;
         float avClustering;
         float Kmean;
         hash_map<int, int> degree_distribution_map;;
         hash_map<int, int> knn_map;
         hash_map<int, float> clustering_coefficient_map;
    public:  
        nodeGraph();  
        int insertNode(int);
        int insertNodeBinarySearch(int); 
        void insertLink(int,int,int,int);
        void nodeExists(int);
        std::vector<node *> getQueue();
        std::vector<node> getNodeList(); 
        void printNodes();
        void printNodesTemp(); 
        void checkAvailable(); 
        node* findNode(int name);
        int BinarySearch(int target);
        int findPlaceBinarySearch(int name);
        int BFScountnodes(int);
        void BFScreatecomponent(int);
        void eraseNonGiantComponentsNodes();
        void calculateKmean();
        float getKmean();
        int getmaxDegree();
        float getavClustering();
        int getminDegree();
        int clustering_coefficient(int,std::vector<int>);
        int common_elements(std::vector<int>,std::vector<int>);
        //std::set<node*> MFT(int);
};
#endif	/* NODEGRAPH_H */

