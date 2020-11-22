#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int INF = 1000000000;

class myGraph
{
private:
    struct Node{
        public:
            Node()
            {
                to = 0;
                distance = 0;
            }
            Node(int tonode, int tonodedistance)
            {
                to = tonode;
                distance = tonodedistance;
            };
            int to;
            int distance;
    };
    std::vector<std::vector<Node>> s;
    std::vector<std::vector<int>> graph;
    std::vector<int> dis;
    std::vector<int> pass;
    int current;

    void rec_printPath(int i)
    {
        if (pass[i] != -1)
            rec_printPath(pass[i]);

        std::cout << i;
        if (i != current)
            std::cout << ' ';
    }

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
                    s.resize(row + 1, std::vector<Node>(0));

                InFile >> ch;
                while (ch != ',')
                {
                    StringToInt.push_back(ch);
                    InFile >> ch;
                }

                std::string StringToInt2;
                InFile >> ch;
                while (ch != ',')
                {
                    StringToInt2.push_back(ch);
                    InFile >> ch;
                }
                Node node(std::stoi(StringToInt), std::stoi(StringToInt2));
                s[row].push_back(node);
            }

            graph.resize(s.size(), std::vector<int>(s.size(), INF));
            for(int i = 0; i < s.size(); i++)
            {
                graph[i][i] = 0;
                for(int j = 0; j < s[i].size(); j++)
                {
                    graph[i][s[i][j].to] = s[i][j].distance;
                    // graph[s[i][j].to][i] = s[i][j].distance; // here is the problem
                }
            }

            dis.resize(s.size(), INF);
            pass.resize(s.size(), 0);
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
        //固定大小
        const int size = s.size();
        //初始化3个
        std::vector<bool> vis(size, false);
        fill(dis.begin(), dis.end(), INF);
        fill(pass.begin(), pass.end(), -1);
        //把原点距离原点设为0
        dis[source] = 0;
        //process start
        for(int i = 0; i < size; i++)
        {
            int Min = INF;
            int medium= -1;
            for(int j = 0; j < size; j++)
            {
                if(!vis[j] && dis[j] < Min)
                {
                    medium = j;
                    Min = dis[j];
                }
            }

            if(medium == -1)
                return;

            vis[medium] = true;

            for (int j = 0; j < size; j++)
            {
                if(!vis[j] && dis[medium]+graph[medium][j] < dis[j])
                {
                    dis[j] = dis[medium] + graph[medium][j];
                    pass[j] = medium;
                }
            }
        }
    }

    void printPath( int i )
    {
        //记录当前处理位数
        current = i;
        rec_printPath(current);
    }

    int computePathCost(int i)
    {
        return dis[i];
    }
};