#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h> 
using namespace std;


class Node
{
    private:
        Node* parent;
        vector<Node*> children;
        vector<string> files;
        int dataSize;
        string directory;

    public:
        Node(string _directory)
        {
            this->parent = nullptr;
            //this->children;
            this->dataSize = 0;
            this->directory = _directory;
        }

        Node(string _directory,Node * _parent)
        {
            this->parent = _parent;
            this->dataSize = 0;
            this->directory = _directory;
        }

        Node * getParent()
        {
            return this->parent;
        }

        vector<Node*> getChildren()
        {
            return this->children;
        }

        void listChildren()
        {
            cout << this->getDirectory() << " child's are :\n";
            for(auto it = children.begin();it!= children.end();it++){
                Node * child = *it;
                cout << child->getDirectory()<<"\n";
            }
        }

        Node * goToChild(string childDirectory)
        {
            for(auto it = children.begin();it!= children.end();it++){
                Node * child = *it;
                if(child->directory == childDirectory)
                {
                    return child;
                }
            }
            return nullptr;
        }

        int getDataSize() 
        {
            return this->dataSize;
        }

        void addToDataSize(int fileSize)
        {
            this->dataSize+=fileSize;
        }

        string getDirectory() 
        {
            return this->directory;
        }

        void addChild(Node * child)
        {
            this->children.push_back(child);
        }
};

pair<string,string> parseInput(string input)
{

    string command = input.substr(0,input.find(' '));
    if(command == "cd")
    {
        string dir = input.substr(input.find(' ')+1);
        cout << command << " : " << dir <<"\n";
        return make_pair(command,dir);
    }
    cout << command <<"\n";
    return make_pair(command,"");
}

void parseOutput(string output,Node * currDir)
{

    string part1 = output.substr(0,output.find(' '));
    string part2 = output.substr(output.find(' ')+1);
    //cout <<"Output "<< part1 << " : " << part2 <<"\n";
    if(part1 == "dir")
    {
        cout << "Adding dir "<<part2<<"\n";
        currDir->addChild(new Node(part2,currDir));
    }else{
        cout << "Adding file : " << part2<<"\n";
        currDir->addToDataSize(stoi(part1));
    }
}

unsigned int completeTree(Node * node)
{
    vector<Node*>children = node->getChildren();
    unsigned int sizeToAdd = 0;
    for(auto it = children.begin();it!= children.end();it++){
        Node * child = *it;
         sizeToAdd += completeTree(child);
        //cout << child->getDirectory()<<"\n";
    }
    node->addToDataSize(sizeToAdd);
    return node->getDataSize();
}


unsigned int nodeBelow100k(Node * node)
{
    unsigned int res = 0;
    
    if(node->getDataSize()<100000){
        res += node->getDataSize();
    }
    vector<Node*>children = node->getChildren();
    for(auto it = children.begin();it!= children.end();it++)
    {
        Node * child = *it;
        res+=nodeBelow100k(child);
    }
    return res;
}

unsigned int bestMemory(Node * node,unsigned int memory)
{
    unsigned int res = node->getDataSize()>=memory?node->getDataSize():0;
    vector<Node*>children = node->getChildren();
    cout<< node->getDirectory() << "weighs : " << node->getDataSize()<<"\n";
    for(auto it = children.begin();it!= children.end();it++)
    {
        Node * child = *it;
        unsigned int possibleRes = bestMemory(child,memory);
        if(res == 0)
        {
            res = possibleRes;
        }else if(possibleRes>0)
        {
            res = min(res,possibleRes);
        }
    }
    return res;
}

Node * buildTree(string path)
{
    ifstream myFile;
    myFile.open(path);
    
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file : " << path << "\n"; 
        return nullptr;
    }
    Node * root = new Node("/");
    Node * currNode = root;
    string line;
    unsigned int res = 0;
    while(getline(myFile,line))
    {
        reprise:
        cout << "At dir : " <<currNode->getDirectory()<<"\n";
        cout << "Command is : " <<line<<"\n";
        pair<string,string> command = parseInput(line.substr(2));
        if(command.first == "cd")
        {
            if(command.second == "/")
            {
                cout<<"Moving to root\n";
                currNode = root;
            }else if(command.second == "..")
            {
                cout<<"Moving back\n";
                currNode = currNode->getParent();
            }else
            {
                cout<<"Moving down to "<< command.second <<"\n";
                currNode = currNode->goToChild(command.second);
            }

        }else{
            cout <<"adding from ls\n";
            while (getline(myFile,line) && line[0] != '$')
            {
                parseOutput(line,currNode);
            }
            cout<<" finished ls\n";
            currNode->listChildren();
            if(!myFile.eof())
            {
                goto reprise;
            }
            
        }
        
    }
    myFile.close();
    completeTree(root);

    return root;
}

unsigned int part1(Node * root)
{
    unsigned int res = 0;
    res = nodeBelow100k(root);
    return res;
}

unsigned int part2(Node * root)
{
    unsigned int res = 0;
    unsigned int updateSize = 30000000;
    unsigned int totalAvailable = 70000000;

    unsigned int currentMemoryUsed = root->getDataSize();
    unsigned int availableSpace = totalAvailable-currentMemoryUsed;
    unsigned int memoryNeeded = -(availableSpace-updateSize);
    cout << "Need : " << memoryNeeded << " space\n";
    res = bestMemory(root,memoryNeeded);
    return res;
}


int main()
{
    string path = "./files/day7/input.txt";
    Node * root = buildTree(path);
    unsigned int res1 = part1(root);
    unsigned int res2 = part2(root);
    cout << "Res 1 is : " << res1 << "\n";
    cout << "Res 2 is : " << res2 << "\n";
    return EXIT_SUCCESS;
}