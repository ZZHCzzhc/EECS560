#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class myGraph
{
private:
    struct Node{
        public:
            Node(int tonode, int tonodedistance)
            {
                to = tonode;
                distance = tonodedistance;
            };
            int to;
            int distance;
    };
    std::vector<std::vector<Node>> s;

public:
    myGraph(std::string filename)
    {
        // s.resize(0, std::vector<int>(0));
        std::ifstream InFile;
        InFile.open(filename);
        if (InFile.is_open())
        {
            char ch;
            while (InFile >> ch)
            {
                std::string StringToInt;
                while (ch != ',')
                {
                    StringToInt.push_back(ch);
                    InFile >> ch;
                }
                int row = std::stoi(StringToInt);
                StringToInt.clear();

                if (row >= s.size())
                    s.resize(row + 1, std::vector<Node>(row));

                InFile >> ch;
                while (ch != ',')
                {
                    StringToInt.push_back(ch);
                    InFile >> ch;
                }

                std::string StringToInt2;
                while (ch != ',')
                {
                    StringToInt2.push_back(ch);
                    InFile >> ch;
                }
                Node node(row, std::stoi(StringToInt2));
                s[row].push_back(node);
            }
        }
        else
        {
            std::cout << "unable to open file: " << filename << std::endl;
        }

        InFile.close();
    }

    ~myGraph()
    {
        s.clear();
    }

    void print2()
    {
        for (int i = 0; i < s.size(); i++)
        {
            std::cout << i << ": ";

            for (int j = 0; j < s[i].size(); j++)
            {
                std::cout << s[i][j].distance;
                if (j + 1 < s[i].size())
                    std::cout << ' ';
            }

            std::cout << std::endl;
        }
    }

    void dijkstra(int source)
    {

    }
    void printPath( int i )
    {

    }
    int computePathCost( int i )
    {

    }
};