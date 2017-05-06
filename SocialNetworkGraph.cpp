/*
This is a social network graph class, stroring the member with number and adjacent map relation.
The method is solve the mininum distance is:
1. Traverse all lines in the file and build a map between people and number.
2. Build a map of direct friend, this is a multimap.
3. Use graph BFS algorithm to traverse all members until the destination is found. 
   Because the weight of every relation is one and no direction, the path should be the mininum.
4. To get the path from A to B, record the parent-child relation when get the adjacent node.

To get a better performance,befor BFS, we can identify whether two given people are direct friends or not,
if yes, the distance is one. If not, then call BFS.

*********All maps are uing hash map to improve performance.***********
*/

#include "SocialNetworkGraph.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

SocialNetworkGraph::SocialNetworkGraph()
{
    allMembers.clear();
    adjacentMap.clear();
}

SocialNetworkGraph::~SocialNetworkGraph()
{
}

int SocialNetworkGraph::GetSize()
{
    return this->allMembers.size();
}

// Split the input string in one single line to two strings conatining the first name and second names.
// Return true if success, false if fails or conatains more than two names.
bool SplitLineToNames(string &inputLine, vector<string> &names)
{
    names.clear();
    string subStr;
    stringstream ss(inputLine);
    while (getline(ss, subStr, ','))
    {
        names.push_back(subStr);
    }
    if (2 == names.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Get all lines and members.
// Line: unordered_map<int, pair<string, string>>
// Memeber: unordered_map<string, int>
// If input nameA and nameB are direct friend, set directFriedn as true.
void SocialNetworkGraph::GetAllLinesAndMembers
(
const string fileName,
unordered_map<int, pair<string, string>> &allLines,
const string nameA,
const string nameB,
bool &directFriend
)
{
    ifstream inFile;
    try
    {
        inFile.open(fileName);
        if (inFile.is_open())
        {
            string line;
            vector<string> names;
            names.reserve(2);
            int iName = 0;
            int iLine = 0;
            while (getline(inFile, line))
            {
                if (SplitLineToNames(line, names))
                {
                    if ((nameA == names[0] && nameB == names[1]) || (nameB == names[0] && nameA == names[1]))
                    {
                        directFriend = true;
                    }
                    allLines.insert(std::make_pair(iLine, std::make_pair(names[0], names[1])));
                    iLine++;
                    if (allMembers.find(names[0]) == allMembers.end())
                    {
                        allMembers.insert(std::make_pair(names[0], iName));
                        iName++;
                    }
                    if (allMembers.find(names[1]) == allMembers.end())
                    {
                        allMembers.insert(std::make_pair(names[1], iName));
                        iName++;
                    }
                }
                else
                {
                    throw "There not illegal content in the file.";
                }
            }
        }
        else
        {
            throw "File can not be opened.";
        }
    }
    catch (const char* &e)
    {
        cout << e << endl;
    }
    inFile.close();
}

// Get the relation map of the social network. Stroed with multimap.
void SocialNetworkGraph::CalulateRelationMap(unordered_map<int, pair<string, string>> &allLines)
{
    if (allLines.empty() || allMembers.empty())
    {
        return;
    }
    for (auto iter : allLines)
    {
        int numA = allMembers.find(iter.second.first)->second;
        int numB = allMembers.find(iter.second.second)->second;
        adjacentMap.insert(std::make_pair(numA, numB));
        adjacentMap.insert(std::make_pair(numB, numA));
    }
}

//Find direct friend relation of given name's number
void SocialNetworkGraph::FindAdjacentNode
(
const int input,                                          // I: number to serach
const unordered_map<int, bool> &visited,                  // I: cached visited value
unordered_set<int> &adjResult,                            // O: adjacent result
unordered_map<int, int> &parentRelation                   // O: record the parent
) const
{
    auto iter = adjacentMap.equal_range(input);
    for (auto iter2 = iter.first; iter2 != iter.second; ++iter2)
    {
        if (!visited.find(iter2->second)->second)
        {
            adjResult.insert(iter2->second);
            parentRelation.insert({ iter2->second, input });
        }
    }
}

// Find the path with parent relation.
void FindPath(const int numA, const int numB, unordered_map<int, int> &parentRelation, vector<int> &path)
{
    path.push_back(numB);
    if (numB == numA || parentRelation.find(numB) == parentRelation.end())
    {
        return;
    }
    FindPath(numA, parentRelation[numB], parentRelation, path);
}

// Get the distance between two given values.
// The distance between two members of the network can be defined as
// the minimum number of ties required to connect two people in the social network.

// Breadth-first search(BFS).
// Return -1 if the given string is not in the graph.
// Return 0 if the two given strings are equal.
int SocialNetworkGraph::GetMinDistanceWithBFS
(
const string inputA,                                // I: search original
const string inputB,                                // I: search destination
vector<string> &path                                // O: search path if found
) const
{
    if (allMembers.find(inputA) == allMembers.end() || allMembers.find(inputB) == allMembers.end())
    {
        return -1;
    }
    if (inputA == inputB)
    {
        return 0;
    }
    //Cache the visited status
    unordered_map<int, bool> visited;
    for (auto iter : allMembers)
    {
        visited.insert(std::make_pair(iter.second, false));
    }
    // A ---->B
    int numA = allMembers.find(inputA)->second;
    int numB = allMembers.find(inputB)->second;
    queue<int> searchQ;
    unordered_map<int, int> parentRelation;
    searchQ.push(numA);
    visited[numA] = true;
    bool found = false;
    while (!searchQ.empty())
    {
        int searchNum = searchQ.front();
        if (searchNum == numB)
        {
            break;
        }
        searchQ.pop();

        unordered_set<int> adjSet;
        FindAdjacentNode(searchNum, visited, adjSet, parentRelation);
        for (auto iter : adjSet)
        {
            searchQ.push(iter);
            visited[iter] = true;
        }
    }
    vector<int> pathInt;
    FindPath(numA, numB, parentRelation, pathInt);

    unordered_map<int, string> reversedMembers;
    for (auto iter : allMembers)
    {
        reversedMembers.insert(std::make_pair(iter.second, iter.first));
    }
    for (unsigned int ii = 0; ii < pathInt.size(); ii++)
    {
        path.push_back(reversedMembers.find(pathInt[ii])->second);
    }
    return path.size() - 1;
}
