#include "SocialNetworkGraph.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

SocialNetworkGraph::SocialNetworkGraph()
{
    member.clear();
    adjacentMatrix.clear();
}

SocialNetworkGraph::~SocialNetworkGraph()
{
}

//Getter for member
unordered_map<string, int> SocialNetworkGraph::GetMember()
{
    return this->member;
}
// Setter for member
void SocialNetworkGraph::SetMember(unordered_map<string, int> &inputMember)
{
    this->member = inputMember;
}
//Getter for adjacent matrix
vector<vector<int>> SocialNetworkGraph::GetAdjacentMatric()
{
    return this->adjacentMatrix;
}
//Setter for adjacent matrix
void SocialNetworkGraph::SetAdjacentMatrix(vector<vector<int>> &inputMatrix)
{
    this->adjacentMatrix = inputMatrix;
}
//Size of the member
int SocialNetworkGraph::GetSize()
{
    return this->member.size();
}

static void FindAdjacentNode
(
const int input,                            // I: number to serach
const vector<vector<int>> &matrix,          // I: adjacent matrix
unordered_map<int, bool> &visited,          // I: cached visited value
unordered_set<int> &adjResult,              // O: adjacent result
unordered_map<int, int> &parentRelation      // O: record the parent
)
{
    for (unsigned int ii = 0; ii < matrix[input].size(); ii++)
    {
        if (matrix[input][ii] && matrix[input][ii] != input && !visited[ii])
        {
            adjResult.insert(ii);
            parentRelation.insert({ ii, input });
        }
    }
}

static void FindPath(const int numA, const int numB, unordered_map<int, int> &parentRelation, vector<int> &path)
{
    path.push_back(numB);
    if (numB == numA)
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
int SocialNetworkGraph::GetMinDistance(const string inputA, const string inputB, vector<string> &path)
{
    unordered_map<string, int> member = this->GetMember();
    vector<vector<int>> matrix = this->GetAdjacentMatric();
    if (member.find(inputA) == member.end() || member.find(inputB) == member.end())
    {
        return -1;
    }
    if (inputA == inputB)
    {
        return 0;
    }
    unordered_map<int, bool> visited;
    for (auto iter : member)
    {
        visited.insert(std::make_pair(iter.second, false));
    }
    // A ---->B
    int numA = member.find(inputA)->second;
    int numB = member.find(inputB)->second;
    queue<int> searchQ;
    unordered_map<int, int> parentRelation;
    searchQ.push(numA);
    bool found = false;
    while (!searchQ.empty())
    {
        int searchNum = searchQ.front();
        visited[searchNum] = true;
        if (searchNum == numB)
        {
            break;
        }
        searchQ.pop();

        unordered_set<int> adjSet;
        FindAdjacentNode(searchNum, matrix, visited, adjSet, parentRelation);
        for (auto iter : adjSet)
        {
            searchQ.push(iter);
        }
    }
    vector<int> pathInt;
    FindPath(numA, numB, parentRelation, pathInt);

    unordered_map<int, string> reversedMembers;
    for (auto iter : member)
    {
        reversedMembers.insert(std::make_pair(iter.second, iter.first));
    }
    for (unsigned int ii = 0; ii < pathInt.size(); ii++)
    {
        path.push_back(reversedMembers[pathInt[ii]]);
    }
    return path.size();
}

