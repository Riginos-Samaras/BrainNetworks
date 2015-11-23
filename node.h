/* 
 * File:   node.h
 * Author: Riginos
 *
 * Created on October 29, 2015, 11:28 AM
 */

#ifndef NODE_H
#define	NODE_H

 
#include <vector>
#include <string>
#include <iostream>
#include <set>
#ifdef	__cplusplus
extern "C" {
#endif
class node{

 private: 
    int name;   
    int visited=0;   
    int inGiantComponent=0;   
 public:
    std::vector<int> linkedNodes; 
    
    node();
    node(int); 
    int getName();   
    void setVisited(int); 
    int getVisited();   
    void setinGiantComponent(int); 
    int getinGiantComponent();   
    void insertLinkedNode(int); 
    int findPlaceBinarySearch(int);
    void printLinks();
};

#ifdef	__cplusplus
}
#endif


#endif	/* NODE_H */

