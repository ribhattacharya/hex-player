#include "include/graph/graph.hpp"

Graph::Graph(int s) : SIZE(s), nodes(SIZE, node_vect(SIZE))
{
    cout << "Initialized board with size = " << SIZE << ".\n\n";

    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = new Node(i, j, i * SIZE + j);

    createEdges();
}

Graph::Graph(const Graph &other) : SIZE(other.SIZE)
{
    // Create a new vector of nodes with the same size
    nodes = vector<node_vect>(SIZE, node_vect(SIZE));

    // Copy the content of each node from the other graph
    // Assuming Node has its own copy constructor or clone method
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = new Node(*other.nodes[i][j]);

    createEdges();
}

/// @brief Graph destructor, deletes all nodes.
Graph::~Graph()
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            nodes[i][j] = (delete nodes[i][j], nullptr);
}

/// @brief Create edges between all nodes.
void Graph::createEdges()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            // 6 directions
            vector<vector<int>> directions{
                {i, j - 1},
                {i - 1, j},
                {i - 1, j + 1},
                {i, j + 1},
                {i + 1, j},
                {i + 1, j - 1}};

            node_vect neighbours;
            for (const auto dir : directions)
            {
                int ii = dir[0], jj = dir[1];
                if (ii >= 0 && ii < SIZE && jj >= 0 && jj < SIZE)
                    neighbours.push_back(nodes[ii][jj]);
            }
            nodes[i][j]->SetNeighbours(neighbours);
        }
    }
}

int Graph::GetSize() { return SIZE; }

Node *Graph::GetNode(Pair idx) const
{
    return nodes[idx.first][idx.second];
}

bool Graph::IsAvailable(Pair idx) const
{
    return GetNode(idx)->GetPlayer() == Player::NONE;
}

void Graph::SetPlayer(Pair idx, Player playertype)
{
    // cout << "setting " << idx << " to be " << playertype << "\n";
    GetNode(idx)->SetPlayer(playertype);
    // cout << "set " << idx << " to be " << GetNode(idx)->GetPlayer() << "\n";
}

template <typename T>
bool Graph::IsInSet(T node, unordered_set<T> &set) const
{
    return set.find(node) != set.end();
}

bool Graph::IsBridgeFormed(node_set STARTS, node_set GOALS, Player playertype) const
{
    /*
    If one start node branches into a tree, then it will not lead to a goal iff
    it is a detached tree. In that case, all the nodes will be addeed to CLOSED
    and OPEN will be empty.

    But a case arises if one start node tree contains another start node.
    If the other start node could lead to a target/goal, it would during the same run.
    If not, then going through it again wouldn't help. So we can skip start nodes if they
    are part of CLOSED already.
    */
    // cout << "\n\ninside brige function\n\n";
    // for (auto start : STARTS)
    //     cout << start->GetIDX() << " ";
    // cout << '\n';
    // for (auto goal : GOALS)
    //     cout << goal->GetIDX() << " ";
    // cout << '\n';

    // for (auto row : nodes)
    //     for (auto node : row)
    //         cout << node << " " << node->GetIDX() << " has " << node->GetPlayer() << '\n';

    queue<Node *> OPEN;
    node_set CLOSED;

    for (auto start : STARTS)
    {
        // cout << "\nexpanding node " << start->GetIDX() << " " << start << " of type " << start->GetPlayer() << '\n';
        // for (auto neighbour : start->GetNeighbours())
        //     cout << "node " << start->GetIDX() << " is " << start->GetPlayer()
        //          << " and has neighbour " << neighbour->GetIDX() << " of type " << neighbour->GetPlayer() << '\n';

        if (start->GetPlayer() != playertype || IsInSet(start, CLOSED))
            continue;
        // cout << "\nfirst step cleared";
        OPEN.push(start);
        while (!OPEN.empty())
        {
            // cout << "\ninside while loop";
            Node *nodeToExpand = OPEN.front();
            OPEN.pop();
            CLOSED.insert(nodeToExpand);
            // cout << "\nexpanding " << nodeToExpand->GetIDX();

            if (GOALS.find(nodeToExpand) != GOALS.end())
                return true;
            // cout << "\nisnt in GOALS";
            for (auto neighbour : nodeToExpand->GetNeighbours())
            {
                // cout << nodeToExpand->GetIDX() << " has neighbour " << neighbour->GetIDX() << '\n';
                // cout << neighbour->GetIDX() << " has " << neighbour->GetPlayer() << '\n';
                if (neighbour->GetPlayer() != playertype || IsInSet(neighbour, CLOSED))
                    continue;

                OPEN.push(neighbour);
            }
        }
    }

    return false;
}

void Graph::printGraph() const
{

    unordered_map<Player, char> symbols = {
        {Player::HUMAN, 'X'},
        {Player::COMP, 'O'},
        {Player::NONE, '.'}};

    cout << string(3, ' ');
    for (int col = static_cast<int>('a'), j = 0; j < SIZE; j++, col++)
    {
        cout << '|' << static_cast<char>(col) << '|';
        if (j != SIZE - 1)
            cout << string(1, ' ');
    }
    cout << "\n";

    for (int margin = 0, i = 0, row = static_cast<int>('a'); i < SIZE; i++, row++)
    {
        cout << string(margin++, ' ');
        cout << '|' << static_cast<char>(row) << '|' << string(1, ' ');
        for (int j = 0; j < SIZE; j++)
        {
            Pair idx = std::make_pair(i, j);
            Player p = GetNode(idx)->GetPlayer();
            const char player_symbol = symbols[p];

            cout << player_symbol;
            if (j != SIZE - 1)
                cout << " - ";
        }
        cout << '\n';
        if (i != SIZE - 1)
        {
            cout << string(margin++ + 4, ' ');
            for (int j = 0; j < SIZE - 1; j++)
            {
                cout << "\\ / ";
            }
            cout << "\\" << '\n';
        }
    }
}