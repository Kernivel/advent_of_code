#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
using namespace std;

class SupplyStack
{
    private:
        vector<vector<char>> initStack;
    public:
        SupplyStack()
        {
            initStack = getInitialStacks();
            printStack(initStack);
        }

        vector<vector<char>> getInitialStacks()
        {
            vector<vector<char>> resStack;
            ifstream myFile;
            myFile.open("./files/day5/input.txt");
            if(myFile.is_open() == false)
            {
                cerr << "Error: No files opened\n";
                return resStack;
            }
            streampos firstLine = myFile.tellg();
            string line;
            getline(myFile,line);
            for(unsigned int i = 0;i<line.length();i+=4)
            {
                //Creating correct amount vector<char> in resStack
                resStack.push_back({});
            }
            //Go back to first line
            myFile.seekg(firstLine);
            while(getline(myFile,line) && line != "")
            {
                //cout<<line<<":"<<line.length()<<"\n";
                for(unsigned int i = 0;i<line.length();i+=4)
                {
                    string crate = line.substr(i,4);
                    char content = crate[1];
                    
                    if(content != ' ' && int(content)>=65 && int(content)<=90)
                    {
                        //cout << "Pushed " << content << " in stack " << i/4<<"\n";
                        resStack[i/4].push_back(content);
                    }
                }
                //cout << "\n";
            }

            for(unsigned int i = 0;i<resStack.size();i++)
            {
                reverse(resStack[i].begin(),resStack[i].end());
            }   

            myFile.close();
            return resStack;
        }

        void printStack(const vector<vector<char>> myStack)
        {
            for(unsigned int i = 0;i<myStack.size();i++)
            {
                cout << "Vector " << i << " : "; 
                for(unsigned int j = 0;j<myStack[i].size();j++)
                {
                    cout << myStack[i][j];
                }
                cout << " of size " << myStack[i].size()<< "\n";
            }
        }

        void printMovementVector(const vector<int> movement)
        {
            for(unsigned int i = 0;i<movement.size();i++){
                cout << "["<< movement[i]<< "]";
            }
            cout << "\n";
        }

        vector<vector<char>> moveCratesPart1(const vector<int> movements,vector<vector<char>> supplies)
        {
            //cout << "Old supplies\n";
            //printStack(supplies);
            vector<vector<char>> res = supplies;
            unsigned int moves = movements[0];
            unsigned int from = movements[1]-1;
            unsigned int to = movements[2]-1;
            
            for(unsigned int move = 0;move<movements[0];move++)
            {
                char val = res[from].back();
                res[from].pop_back();
                res[to].push_back(val);
            }
            //cout << "New supplies\n";
            //printStack(res);
            return res;
        }

        vector<vector<char>> moveCratesPart2(const vector<int> movements,vector<vector<char>> supplies)
        {
            //cout << "Old supplies\n";
            //printStack(supplies);
            vector<vector<char>> res = supplies;
            unsigned int moves = movements[0];
            unsigned int from = movements[1]-1;
            unsigned int to = movements[2]-1;
            string slicedSupplies;
            for(unsigned int move = 0;move<movements[0];move++)
            {
                char val = res[from].back();
                res[from].pop_back();
                slicedSupplies.push_back(val);

            }
            reverse(slicedSupplies.begin(),slicedSupplies.end());
            for(unsigned int i = 0;i<slicedSupplies.length();i++)
            {
                res[to].push_back(slicedSupplies[i]);
            }
            //cout << "New supplies\n";
            //printStack(res);
            return res;
        }

        vector<int> parseMovements(string input)
        {
            vector<int> res;
            regex_token_iterator<string::iterator> rend;
            regex match("[0-9]+");
            regex_token_iterator<string::iterator> rt(input.begin(),input.end(),match);
            while(rt != rend)
            {

                //cout << " [" << *rt++ << "]";
                res.push_back(stoi(*rt++));
            }
            //cout << "\n";
            return res;
        }

        string Part1()
        {
            string res;
            ifstream myFile;
            vector<vector<char>> supplies = initStack;
            myFile.open("./files/day5/input.txt");
            if(!myFile.is_open())
            {
                cerr<< "Couldn't open input file\n";
                return res;
            }
            string line;
            while(getline(myFile,line) && line != ""){
                //Skips the first lines that are used to initialize the input
            }
            while(getline(myFile,line)){
                //cout << line << "\n";
                vector<int> movements = parseMovements(line);
                supplies = moveCratesPart1(movements,supplies);
                //printMovementVector(movements);
                //cin >> line;
            }
            
            //printStack(supplies);
            cout<<"Done\n";
            for(unsigned int i = 0;i<supplies.size();i++)
            {
                res.push_back(supplies[i].back());
            }
            myFile.close();
            return res;
        }

        string Part2()
        {
            string res;
            ifstream myFile;
            vector<vector<char>> supplies = initStack;
            myFile.open("./files/day5/input.txt");
            if(!myFile.is_open())
            {
                cerr<< "Couldn't open input file\n";
                return res;
            }
            string line;
            while(getline(myFile,line) && line != ""){
                //Skips the first lines that are used to initialize the input
            }
            while(getline(myFile,line)){
                //cout << line << "\n";
                vector<int> movements = parseMovements(line);
                supplies = moveCratesPart2(movements,supplies);
                //printMovementVector(movements);
                //cin >> line;
            }
            //printStack(supplies);
            cout<<"Done\n";
            for(unsigned int i = 0;i<supplies.size();i++)
            {
                res.push_back(supplies[i].back());
            }
            myFile.close();
            return res;
        }
};




int main(){
    SupplyStack mySuplies;
    string res1 = mySuplies.Part1();
    string res2 = mySuplies.Part2();
    cout <<"Res1 is : " << res1 << "\n";
    cout <<"Res2 is : " << res2 << "\n";
    return EXIT_SUCCESS;
}

