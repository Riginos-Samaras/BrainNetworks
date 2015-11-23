#include "dataio.h" 

 
    std::string dataio::getWord(int j,  std::string word){
                std::string token="";
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

   dataio::dataio(){
   }
   
   int dataio::findfilesindirectory(const char * URL){
        std::vector<std::string> files_in_dir;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir (URL)) != NULL) {
          /* print all the files and directories within directory */
          while ((ent = readdir (dir)) != NULL) {    
                files_in_dir.push_back(ent->d_name);
          }
          closedir (dir);
        } else {
          /* could not open directory */
          perror ("");
          return EXIT_FAILURE;
        }
        for(int i=3; i<files_in_dir.size(); i++)
       {
           dataio::dataList.push_back(files_in_dir[i]);
       }
   }
   
   void dataio::printdirectory(){
   
       for(int i=0; i<dataio::dataList.size(); i++)
       {
           std::cout<<dataList[i]<<"\n";
       }
   
   }
   std::vector<std::string> dataio::getdataList(){
       return  dataio::dataList;
   }


   
   int dataio::findtotalNumberofNodesinData(){
        int leftNode;
        int rightNode;
        std::set<int> nodeNames;
        std::string line; 
        int k=0;
           for (int i = 0; i < dataio::dataList.size(); i++) {
              
            std::ifstream datafile("data/"+dataList[i], std::ios::binary | std::ios::ate);
             
            std::streamsize size = datafile.tellg();
            datafile.seekg(0, std::ios::beg);
            
            while (std::getline(datafile, line))
            { 
                leftNode = std::stoi(getWord(0,line));
                rightNode = std::stoi(getWord(1,line));
                nodeNames.insert(leftNode);
                nodeNames.insert(rightNode);
                k++;
                if(k==100000){
                    std::cout<<"\nfile:"<<dataList[i]<<" Graph size:"<<nodeNames.size()<<std::endl;
                    k=0;
                }
                std::istringstream iss(line); 
                    int a, b;
                    if (!(iss >> a >> b)) { break; } 
                
            } 
        }
        return nodeNames.size();
   }
   
   
   
   void dataio::writetoParameters(std::string name,int value){
   
            std::ifstream datafile("parameters/parameters", std::ios::binary | std::ios::ate);
            std::streamsize size = datafile.tellg();
            std::string paramName;
            std::string line;
            int paramValue;
             while (std::getline(datafile, line))
            { 
                 paramName = getWord(0,line);
                 paramValue = std::stoi(getWord(1,line));
                 
                 std::istringstream iss(line); 
                    int a, b;
                    if (!(iss >> a >> b)) { break; } 
                
            }
   
   }
   
   void dataio::readParameters(){
      
            std::ifstream datafile("parameters/parameters.txt", std::ios::binary | std::ios::ate);
             
            std::streamsize size = datafile.tellg();
            datafile.seekg(0, std::ios::beg);
            std::string name;
            std::string line;
            int value;
            while (std::getline(datafile, line))
            { 
                name = getWord(0,line);
                value = std::stoi(getWord(1,line));
                if(name=="SIZEOFGRAPH")
                    SIZEOFGRAPH = value;
                
                std::istringstream iss(line); 
                    int a, b;
                    if (!(iss >> a >> b)) { break; } 
                
            } 
    }
   
   
    int dataio::get_SIZEOFGRAPH(){
        return SIZEOFGRAPH;     
    }
    
//    
//  void dataio::createGML(std::vector<node> nodeList){
//      
//      
//
////   edge
////  [
////   source B
////   target A
////  ]
//
//      
//
//                
//  
//  
//  }