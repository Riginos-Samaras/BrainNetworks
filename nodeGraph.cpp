    #include "nodeGraph.h" 
    #include "node.h" 
    #include <iterator>
    using std::cout;
    using std::endl;

    nodeGraph::nodeGraph() {
    }

    int nodeGraph::insertNode(int nodeName) {
        node *inputNode = new node(nodeName);

        nodeList.push_back(*inputNode);
        return nodeList.size() - 1;
    }

    int nodeGraph::insertNodeBinarySearch(int nodeName) {

        int pos = 0;

        if (nodeList.size() == 0) {
            node *inputNode = new node(nodeName);
            nodeList.push_back(*inputNode);
            return nodeList.size() - 1;
        } else {
            pos = findPlaceBinarySearch(nodeName);
            if (pos > nodeList.size()) {
                pos = nodeList.size();
            }
            node *inputNode = new node(nodeName);
            nodeList.insert(nodeList.begin() + pos, *inputNode);
            return pos;
        }

        return -1;


    }
    

    void nodeGraph::insertLink(int leftName, int rightName, int lP, int rP) {
        int leftPos = lP;
        int rightPos = rP;

        if (leftPos == -1)
            leftPos = findPlaceBinarySearch(leftName);
        if (rightPos == -1)
            rightPos = findPlaceBinarySearch(rightName);

        nodeList[leftPos].insertLinkedNode(rightName);
        nodeList[rightPos].insertLinkedNode(leftName);

    }

    int nodeGraph::findPlaceBinarySearch(int target) {
        int lo = 0;
        int hi = nodeList.size() - 1;
        int mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (nodeList[mid].getName() == target)
                return mid;
            else if (nodeList[mid].getName() < target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return lo;
    }
    //       

    int nodeGraph::BinarySearch(int target) {
        int lo = 0;
        int hi = nodeList.size();
        int mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (nodeList[mid].getName() == target)
                return mid;
            else if (nodeList[mid].getName() < target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return -1;
    }

    node* nodeGraph::findNode(int target) {
        int lo = 0;
        int hi = nodeList.size();
        int mid;
        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (nodeList[mid].getName() == target)
                return &nodeList[mid];
            else if (nodeList[mid].getName() < target)
                lo = mid + 1;
            else
                hi = mid - 1;
        }
        return 0;
    } 

    void nodeGraph::printNodes() {
        std::cout << "RW::Weight::Name->(Edges)\n-------------------";

        for (int i = 0; i < nodeList.size(); ++i) {
            std::cout << "\n";
            std::cout << "::" << nodeList[i].getName();
            for (int j = 0; j < nodeList[i].linkedNodes.size(); ++j) {
                if (j == 0)
                    std::cout << "->(";
                if (j == nodeList[i].linkedNodes.size() - 1)
                    std::cout << nodeList[i].linkedNodes[j] << ")";
                else
                    std::cout << nodeList[i].linkedNodes[j] << ",";
            }
        }
    }

    void nodeGraph::BFScreatecomponent(int nodeID) {

        node* myNode = findNode(nodeID);
        node* tempNode;
        myNode->setinGiantComponent(1);
        
        for (int i = 0; i < myNode->linkedNodes.size(); i++) {
            tempNode = findNode(myNode->linkedNodes[i]);
            if (tempNode->getinGiantComponent() == 1) {
                continue;
            }
            BFScreatecomponent(myNode->linkedNodes[i]);

        }       
    }

    void nodeGraph::eraseNonGiantComponentsNodes(){
    
            int nodeListSize=nodeList.size();
        for(int i=0; i<nodeListSize; i++){
            
            if(nodeList[i].getinGiantComponent()==0){
                //std::cout<<" erased"<<nodeList[i].getName()<<"now:";
                nodeList.erase(nodeList.begin() + i); 
               // std::cout<<nodeList[i].getName()<<"\n";
                nodeListSize--;
                i--;
            }
            //std::cout<<"i:"<<i<<" Size:"<<nodeListSize<<endl;
        }
    
    
    }
    int nodeGraph::BFScountnodes(int nodeID) {


        int sum = 0;
        node* myNode = findNode(nodeID);
        node* tempNode;

        myNode->setVisited(1);
        // std::cout<<nodeID<<"->("; 
        for (int i = 0; i < myNode->linkedNodes.size(); i++) {


            tempNode = findNode(myNode->linkedNodes[i]);

            if (tempNode->getVisited() == 1) {
                continue;
            }

            //                    if(i==myNode->linkedNodes.size()-1)
            //                          std::cout<<myNode->linkedNodes[i];
            //                    else
            //                         std::cout<<myNode->linkedNodes[i]<<",";

            int tempSum;

            tempSum = BFScountnodes(myNode->linkedNodes[i]);
            sum = sum + tempSum;

        }
        //  std::cout<<")";
        //tempNode->setVisited(1); 
        //        for (std::set<node*>::iterator i = sum.begin(); i != sum.end(); i++) {
        //  
        //            
        //            node* nd = *i;
        //            total_sum_RPW+=nd->getValue();
        //            
        //        }
        //      myNode->setRPW(total_sum_RPW+myNode->getValue()+tempRPG);

        sum = sum + 1;
        return sum;

    }

    std::vector<node > nodeGraph::getNodeList() {

        return nodeList;

    }

    void nodeGraph::printNodesTemp() {
        //std::cout << "YOYO";
        for (int i = 0; i < nodeList.size(); ++i) {
            std::cout << "\n";
            std::cout << "::" << nodeList[i].getName();

        }
    }
    
     
    
   
   void nodeGraph::calculateKmean(){
       float sum=0;
       int maxdegree=0;
       int mindegree=10000;
       int nodeDegree;
       int neighborDegree;
       int sumofNeighborsDegrees=0; 
       int numberoftriangles=0;
       float clustering_value=0;
       float totalClustering=0;
       for (int i = 0; i < nodeList.size(); i++) {
          // std::cout<<nodeList[i].linkedNodes.size();
           nodeDegree=nodeList[i].linkedNodes.size();
           
           clustering_value=0;
           if(nodeDegree>1){
                numberoftriangles = clustering_coefficient(nodeList[i].getName(),nodeList[i].linkedNodes);
                clustering_value=2*(float)numberoftriangles/(float)(nodeDegree*(nodeDegree-1));
           }
           
           totalClustering+=clustering_value;
          // cout<<nodeList[i].getName()<<": "<<clustering_value<<"("<<nodeDegree<<")"<<endl;
           
           for (int j = 0; j<nodeList[i].linkedNodes.size(); j++){
                
               node* myNode = findNode(nodeList[i].linkedNodes[j]);
               
               neighborDegree=myNode->linkedNodes.size();
               sumofNeighborsDegrees=sumofNeighborsDegrees+neighborDegree;             
           
           }
           
           if(knn_map[nodeList[i].linkedNodes.size()]==NULL)        
             knn_map[nodeList[i].linkedNodes.size()]=sumofNeighborsDegrees/nodeList[i].linkedNodes.size();
           else        
             knn_map[nodeList[i].linkedNodes.size()]=
                            knn_map[nodeList[i].linkedNodes.size()]+sumofNeighborsDegrees/nodeList[i].linkedNodes.size();
           
           
           if(degree_distribution_map[nodeList[i].linkedNodes.size()]==NULL)        
             degree_distribution_map[nodeList[i].linkedNodes.size()]=1;
           else        
             degree_distribution_map[nodeList[i].linkedNodes.size()]=
                            degree_distribution_map[nodeList[i].linkedNodes.size()]+1;
           
           
           if(clustering_coefficient_map[nodeList[i].linkedNodes.size()]==NULL)        
             clustering_coefficient_map[nodeList[i].linkedNodes.size()]=clustering_value;
           else        
             clustering_coefficient_map[nodeList[i].linkedNodes.size()]=
                            clustering_coefficient_map[nodeList[i].linkedNodes.size()]+clustering_value;
           
           sumofNeighborsDegrees=0;
           sum=sum+nodeDegree;
           
           if(maxdegree<nodeDegree)
               maxdegree=nodeDegree;
           if(mindegree>nodeDegree)
               mindegree=nodeDegree;
               
           
       }
       avClustering=totalClustering/nodeList.size();
       ofstream degreedistributionfile;
       ofstream knn_file;
       ofstream cl_coef_file;
       degreedistributionfile.open ("plots/averageDegreeDistribution.dat");
       knn_file.open ("plots/averageKnn_n.dat");
       cl_coef_file.open ("plots/clusteringCoefficient.dat");
       for(int i = 0; i<=maxdegree; ++i){
           
            if(degree_distribution_map[i]==NULL){
                //cout<<i<<"->"<<0<<endl;//do nothing
            }
            else{
                degreedistributionfile<<i<<" "<<(float)degree_distribution_map[i]<<endl;
                knn_file<<i<<" "<<(float)knn_map[i]/(float)degree_distribution_map[i]<<endl;
                if((float)clustering_coefficient_map[i]/(float)degree_distribution_map[i]>0)
                cl_coef_file<<i<<" "<<(float)clustering_coefficient_map[i]/(float)degree_distribution_map[i]<<endl;
                //cout<<i<<" "<<(float)knn_map[i]<<endl;
            }
                
       }
       
        
        degreedistributionfile.close();
        knn_file.close();
        cl_coef_file.close();

        
       
       
       
       Kmean=sum/nodeList.size();
       maxDegree=maxdegree;
       minDegree=mindegree;
   }
   
   int nodeGraph::clustering_coefficient(int name,std::vector<int> neighborList){
       
       int common_neighbors=0;
       int numberoftriangles=0;
       for(int i = 0; i<neighborList.size(); ++i){
           node* myNode = findNode(neighborList[i]);
           common_neighbors=common_neighbors+common_elements(neighborList,myNode->linkedNodes);
       
       }
       numberoftriangles=(float)common_neighbors/2;
       return numberoftriangles;
   }
   int nodeGraph::common_elements(std::vector<int> sorted_full,std::vector<int> sorted_sub){
   
       int full_ix=0;
       int sub_ix=0;
       int common_elems=0;
       
       if(sorted_full.size()==0||sorted_sub.size()==0){
           return 0;
       }
       while(full_ix<sorted_full.size() && sub_ix<sorted_sub.size())
       {
           int curr_full=sorted_full[full_ix];
           int curr_sub=sorted_sub[sub_ix];
           
           if(curr_full==curr_sub)
           {
               //cout<<"comon id"<<
               common_elems++;
               full_ix++;
               sub_ix++;
               continue;
           }
           if(curr_full<curr_sub)
           { 
               full_ix++;  
           }
           else
           {
                sub_ix++;
           }
       
       }
       return common_elems;
   
   }
   
   float nodeGraph::getKmean(){
            return Kmean;
   }
   
   float nodeGraph::getavClustering(){
            return avClustering;
   } 
   int nodeGraph::getmaxDegree(){
            return maxDegree;
   }
   
   int nodeGraph::getminDegree(){
            return minDegree;
   }