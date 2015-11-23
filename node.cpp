#include "node.h" 

node::node() {
}

node::node(int nam) {
    name = nam;
}

int node::getName() {
    return name;
}

void node::insertLinkedNode(int n) {
    int pos=0;
    if (linkedNodes.size() == 0) {
            linkedNodes.push_back(n);
        } else {
            pos = findPlaceBinarySearch(n);
            if (pos > linkedNodes.size()) {
                pos = linkedNodes.size();
            }
            linkedNodes.insert(linkedNodes.begin() + pos, n);
           
        }
    
    
}





void node::setVisited(int v) {
    visited = v;
}

int node::getVisited() {
    return visited;
} 

void node::setinGiantComponent(int v) {
    inGiantComponent = v;
}

int node::getinGiantComponent() {
    return inGiantComponent;
}


int node::findPlaceBinarySearch(int target) {
        int lo = 0;
        int hi = linkedNodes.size() - 1;
        int mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (linkedNodes[mid] == target)
                return mid;
            else if (linkedNodes[mid] < target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return lo;
}



void node::printLinks(){


for (int i = 0; i < linkedNodes.size(); ++i) {
            
            std::cout << "::" << linkedNodes[i];

        }

}