#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;



class Monkey
{
    public:
    vector<int> items;
    int divVal;
    int trueValue;
    int falseValue;
    unsigned int inspectedItems;
    string oper;
    string secondValOperation;

    Monkey(vector<string> monkeyDescription)
    {
        this->inspectedItems = 0;
        string itemsString;
        string operationString;
        string testString;
        string testTrueString;
        string testFalseString;

        itemsString = monkeyDescription[1].substr(monkeyDescription[1].find(":")+2);
        //cout<<"itemsString is : "<<itemsString<<"\n";
        size_t pos=0;
        string token;
        string delimiter = ", ";
        //cout << "items : ";
        while((pos=itemsString.find(delimiter))!=string::npos)
        {
            token = itemsString.substr(0,pos+delimiter.length()-2);
            //cout << token << ",";
            items.push_back(stoi(token));
            itemsString.erase(0,pos+delimiter.length());
        }
        //cout << itemsString << "\n";

        items.push_back(stoi(itemsString));
        operationString = monkeyDescription[2].substr(monkeyDescription[2].find(":")+2);
        //cout<<"operationString is : "<<operationString<<"\n";
        this->oper = operationString.substr(10,1);
        this->secondValOperation = operationString.substr(12);
        //cout <<"oper : "<<this->oper<<"\n";
        //cout <<"secondValOperation : "<<this->secondValOperation<<"\n";

        testString = monkeyDescription[3].substr(monkeyDescription[3].find(":")+2);
        //cout<<"testString is : "<<testString<<"\n";
        this->divVal = stoi(testString.substr(13));
        //cout<<"divVal is : "<<this->divVal<<"\n";

        testTrueString = monkeyDescription[4].substr(monkeyDescription[4].find(":")+2);
        //cout<<"testTrueString is : "<<testTrueString<<"\n";
        this->trueValue = stoi(testTrueString.substr(16));
        //cout<<"trueValue is : "<<this->trueValue<<"\n";

        testFalseString = monkeyDescription[5].substr(monkeyDescription[5].find(":")+2);
        //cout<<"testFalseString is : "<<testFalseString<<"\n";
        this->falseValue = stoi(testFalseString.substr(16));
        //cout<<"falseValue is : "<<this->falseValue<<"\n";
    }


    int operation(const unsigned int oldItem)
    {
        if (this->oper == "*")
        {
        
            if(secondValOperation == "old")
            {
                return oldItem*oldItem;
            }else
            {
                return oldItem*stoi(this->secondValOperation);
            }
        }else
        {
            if(secondValOperation == "old")
            {
                return oldItem+oldItem;
            }else
            {
                return oldItem+stoi(this->secondValOperation);
            }
        }
        return -1;
    }

    unsigned int inspectItem(const unsigned int item)
    {   
        
        unsigned int worryLevel = this->operation(item);
        worryLevel = worryLevel/3;
        //cout <<"Inspecting : " << item << " Worry level is now " <<worryLevel <<"\n";
        return worryLevel;
    }

    unsigned int inspectItemStressed(const unsigned int item)
    {   
        
        unsigned int worryLevel = this->operation(item);
        //cout <<"Inspecting : " << item << " Worry level is now " <<worryLevel <<"\n";
        return worryLevel;
    }

    int test(const unsigned int item)
    {
        //cout << "dividing : " << item << "by" << this->divVal << " = " << item/this->divVal; 
        if(item%this->divVal == 0)
        {
            return trueValue;
        }
        return falseValue;
    }
};

void monkeyRound(vector<Monkey>& monkeys)
{
    for(unsigned int i=0;i<monkeys.size();i++)
    {
        //cout << "Monkey " << i << " inspecting\n";
        for(unsigned int j=0;j<monkeys[i].items.size();j++)
        {
            monkeys[i].inspectedItems+=1;
            unsigned int item = monkeys[i].items[j];
            unsigned int worryness = monkeys[i].inspectItem(item);
            int throwTo = monkeys[i].test(worryness);
            //cout << "Throwing " << worryness <<" to  monkey " << throwTo << "\n"; 
            monkeys[throwTo].items.push_back(worryness);
        }
        monkeys[i].items = {};
    }
}

void monkeyRoundStressed(vector<Monkey>& monkeys)
{
    for(unsigned int i=0;i<monkeys.size();i++)
    {
        //cout << "Monkey " << i << " inspecting\n";
        for(unsigned int j=0;j<monkeys[i].items.size();j++)
        {
            monkeys[i].inspectedItems+=1;
            unsigned int item = monkeys[i].items[j];
            unsigned int worryness = monkeys[i].inspectItemStressed(item);
            int throwTo = monkeys[i].test(worryness);
            //cout << "Throwing " << worryness <<" to  monkey " << throwTo << "\n"; 
            monkeys[throwTo].items.push_back(worryness);
        }
        cout <<"Monkey " << i <<" inspected :" << monkeys[i].inspectedItems << "\n";
        monkeys[i].items = {};
    }
}

int part1(const string path,const int rounds,bool stressed)
{
    int monkeyBusiness = 0;
    ifstream myFile(path);
    if(!myFile.is_open())
    {
        cerr << "Couldn't read file at : " << path << " stopping \n";
        return EXIT_FAILURE;
    }
    string line;
    vector<string> monkeyString;
    vector<Monkey> monkeyVector;
    while(getline(myFile,line))
    {
        monkeyString.push_back(line);
        if(line == "")
        {
            for(auto it=monkeyString.begin();it!=monkeyString.end();it++)
            {
                //cout<<*it<<"\n";
            }
            Monkey monkey(monkeyString);
            monkeyVector.push_back(monkey);
            //cout<<"\n";
            monkeyString = {};
        }
    }
    Monkey monkey(monkeyString);
    monkeyVector.push_back(monkey);

    cout << "Monkey rnds\n";
    for(unsigned int i = 0;i<rounds;i++)
    {
        if(stressed)
        {
            monkeyRoundStressed(monkeyVector);
        }else
        {
            monkeyRound(monkeyVector);
        }
    }
    vector<int> orderedInspects;
    for(unsigned int i=0;i<monkeyVector.size();i++)
    {
        Monkey monkey = monkeyVector[i];
        orderedInspects.push_back(monkey.inspectedItems);
    }
    sort(orderedInspects.begin(),orderedInspects.end());
    cout<<"firstMax " << orderedInspects[orderedInspects.size()-1] << " secondMax " << orderedInspects[orderedInspects.size()-2] << "\n";
    monkeyBusiness = orderedInspects[orderedInspects.size()-1]*orderedInspects[orderedInspects.size()-2];
    return monkeyBusiness;
}


int main()
{
    int res1 = part1("./files/day11/input.txt",20,false);
    cout <<"Res 1 is : "<< res1 <<"\n";
    int res2 = part1("./files/day11/input.txt",20,true);
    cout <<"Res 2 is : "<< res2 <<"\n";
    return EXIT_SUCCESS;
}