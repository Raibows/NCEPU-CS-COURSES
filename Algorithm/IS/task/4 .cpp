#include <iostream>
#include <string>
#include <queue>

using namespace std;

string ss[35];
int maze[35][55];
int dir[4][2] = { { 1, 0 }, { 0, -1 }, { 0, 1 }, { -1, 0 } };
char letter[4] = { 'D', 'L', 'R', 'U' };
int cnt = 10000;
bool vis[35][55];
 
struct node
{
    int x;
    int y;
    string s;
    int step;
    node(int xx, int yy, string ss, int st)
    {
        x = xx;
        y = yy;
        s = ss;
        step = st;
    }
};

bool in(int x, int y)
{
    if (x < 30 && x >= 0 && y < 50 && y >= 0)
    {
        return true;
    }
    return false;
}

void bfs(int x, int y, string s, int step)
{
    queue<node> q;
    q.push(node(x, y, s, step));
    while (!q.empty())
    {
        node now = q.front();
        q.pop();

        vis[now.x][now.y] = true;

        if (now.x == 29 && now.y == 49)
        {
            if (now.step < cnt)
            {
                cnt = now.step;
                cout << now.step << " : " << now.s << endl;
                
            }
            continue;
        }

        for (int i = 0; i < 4; i++)
        {
            int tx = now.x + dir[i][0];
            int ty = now.y + dir[i][1];

            if (maze[tx][ty] != 1 && !vis[tx][ty] && in(tx, ty))
            {
                q.push(node(tx, ty, now.s + letter[i], now.step + 1));
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 30; i++)
    {
        cin >> ss[i];
    }

    for (int i = 0; i < 30; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            maze[i][j] = (ss[i][j] - '0');
        }
    }

    int step = 0;
    string s = "";
    bfs(0, 0, s, step);

    return 0;
}
