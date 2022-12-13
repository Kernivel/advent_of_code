#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> packetToIntVector(string packet);
bool comparePackets(string packet1,string packet2);

vector<pair<string,string>> getInput(const string path)
{
    vector<pair<string,string>> readInput;
    ifstream myFile;
    myFile.open(path);
    if(myFile.is_open() == false)
    {
        cerr << "Couldn't read file : "<< path << "\n";
        return readInput;
    }
    string line;
    while(getline(myFile,line))
    {
        if(line == "")
        {
            getline(myFile,line);
        }
        string packet1 = line;
        getline(myFile,line);
        string packet2 = line;
        pair<string,string> packetPair(packet1,packet2);
        readInput.push_back(packetPair);
    }
    myFile.close();
    return readInput;
}

string getNextValue(string& packet)
{
    vector<char> brackets;
    string nextVal = "";
    if(packet == "")
    {
        return nextVal;
    }else
    {
        string packetCopy = packet;
        if(packet[0] =='[')
        {
            //remove outer bracket
            packetCopy = packet.substr(1,packet.length()-2);
        }
        //cout <<"Packet copy : "<< packetCopy << "\n";

        if(packetCopy[0] == '[')
        {
            //Next packet is still a list
            brackets.push_back('[');
            int pos = 1;
            while (brackets.size()>0 && pos<packetCopy.length())
            {
                //cout << "At : " << packetCopy[pos]<<"\n";
                //cout << "Size : " << brackets.size()<<"\n";
                if(packetCopy[pos] == ']')
                {
                    //cout << "Pop !";
                    brackets.pop_back();
                }else if(packetCopy[pos] == '[')
                {
                    brackets.push_back('[');
                }
                pos+=1;
            }
            packet = packetCopy.substr(pos);
            nextVal = packetCopy.substr(0,pos);
        }else
        {
            //Next packet is the values
            int pos = 0;
            while (pos < packetCopy.size() && packetCopy[pos]!='[' && packetCopy[pos]!=']')
            {
                pos+=1;
            }
            nextVal = packetCopy.substr(0,pos);
            packet = packetCopy.substr(pos);
        }
    }
    if(packet.length()>0){
        packet = packet.substr(1);
    }
    if(nextVal[nextVal.length()-1] == ','){
        nextVal = nextVal.substr(0,nextVal.length()-1);
    }
    cout << "New packet is : " << nextVal<<"\n";
    cout << "Rest packet is : " << packet<<"\n";
    return nextVal;
}

void printInput(vector<pair<string,string>> input)
{
    for(auto it = input.begin();it!=input.end();it++)
    {
        pair<string,string> packetPair = *it;
        cout << "New pair\n";
        cout << packetPair.first << " : " << packetPair.second<<"\n";
    }
}

int part1(vector<pair<string,string>> input)
{
    int res = 0; 
    for(auto i = 0;i<input.size();i++)
    {
        bool ordered = true;
        pair<string,string> packetPair = input[i];
        cout << "OG first packet : " << packetPair.first << "\n";
        cout << "OG second packet : " << packetPair.second << "\n";
        while(packetPair.first.length()>0 || packetPair.second.length()>0)
        {
            string firstPacket = getNextValue(packetPair.first);
            string secondPacket = getNextValue(packetPair.second);
            //cout << "Returned first packet : " << firstPacket << "\n";
            //cout << "Modified first packet : " << packetPair.first << "\n";
            //cout << "Returned second packet : " << secondPacket << "\n";
            //cout << "Modified second packet : " << packetPair.second << "\n";
            if(!comparePackets(firstPacket,secondPacket))
            {
                ordered = false;
                break;
            }
        }
        if(ordered)
        {
            cout << "Packet : " << i+1 << " was in order\n";
            res +=i+1;
            cout << "Res is now : " <<res <<"\n";
        }else
        {
            cout << "Packet : " << i+1 << " was not in order\n";
        }
    }
    return res;
}

bool comparePackets(string packet1,string packet2)
{
    cout <<"Comparing |" << packet1 << "| to |" << packet2 << "|\n";
    if(packet1.length()> 0 && packet2.length()> 0)
    {
        cout << "Packets same size \n";
        if(packet1[0] == '[' && packet2[0] == '[')
        {
            return comparePackets(getNextValue(packet1),getNextValue(packet2));
        }else if(packet1[0] == '[')
        {
            packet2 = "["+packet2+"]";
            return comparePackets(getNextValue(packet1),getNextValue(packet2));
        }else if(packet2[0] == '[')
        {
            packet1 = "["+packet1+"]";
            return comparePackets(getNextValue(packet1),getNextValue(packet2));
        }else
        {
            vector<int> packetInt1 = packetToIntVector(packet1);
            vector<int> packetInt2 = packetToIntVector(packet2);
            int pos = 0;
            while(1)
            {
                if(pos>=packetInt1.size() && pos>=packetInt2.size())
                {
                    return true;
                }else if(pos>=packetInt1.size())
                {
                    return true;
                }else if(pos>=packetInt2.size())
                {
                    return false;
                }

                if(packetInt1[pos]>packetInt2[pos])
                {
                    return false;
                }else if(packetInt1[pos]<packetInt2[pos])
                {
                    return true;
                }
                pos++;
            }
        }
    }else if(packet1.length()> 0)
    {
        cout << "Packet 2 smaller size \n";
        return false;
    }else if(packet2.length()> 0)
    {
        cout << "Packet 1 smaller size \n";
        return true;
    }
    cerr<<"Received empty packets\n";
    return false;
}


vector<int> packetToIntVector(string packet)
{
    vector<int> packetInt;
    for(unsigned int i = 0;i<packet.length();i++)
    {
        if(packet[i] != ',')
        {
            packetInt.push_back(packet[i] - '0');
        }
    }
    return packetInt;
}

int main()
{
    vector<pair<string,string>> input = getInput("./files/day13/input.txt");
    int res1 = part1(input);
    cout <<"Res 1 : "<< res1 << "\n";
    //printInput(input);
    return EXIT_SUCCESS;
}