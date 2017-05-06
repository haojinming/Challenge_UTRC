//Define a class representing the social network graph.

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class SocialNetworkGraph
{
public:
    SocialNetworkGraph();
    ~SocialNetworkGraph();

    unordered_map<string, int> GetMember();
    void SetMember(unordered_map<string, int> &inputMember);
    vector<vector<int>> GetAdjacentMatric();
    void SetAdjacentMatrix(vector<vector<int>> &inputMatrix);

    int GetSize();
    int GetMinDistance(const string inputA, const string inputB, vector<string> &path);
private:
    unordered_map<string, int> member;
    vector<vector<int>> adjacentMatrix;
};

