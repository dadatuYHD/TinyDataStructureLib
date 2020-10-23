#ifndef QUEUESOLUTION_H
#define QUEUESOLUTION_H

#include <iostream>
#include <cstring>
#include "Object/Object.h"
#include "List/LinkList.h"

using namespace std;

namespace DSLib {


//Eight Queens problem solution by Backtracking
#define CHESSBOARD_FREE_SPACE 0
#define QUEUE                 1
#define CHESSBOARD_BOUNDARY   2

template <int SIZE>
class QueueSolution : public Object
{
protected:
    enum {N = SIZE + 2};

    struct Pos : public Object
    {
        Pos(int px = 0, int py = 0): x(px), y(py) {}
        int x;
        int y;
    };

    int m_chessboard[N][N];    //Define the chessboard
    Pos m_direction[3];        //Direction array. Used to determine whether there is a queen in the direction
    LinkList<Pos> m_solution;  //Storage solution
    int m_count;               //The number of solution

    void init(void)
    {
        m_count = 0;

        for (int x = 0; x < N; x += (N - 1))
        {
            for (int y = 0; y < N; y++)
            {
                m_chessboard[x][y] = CHESSBOARD_BOUNDARY;
                m_chessboard[y][x] = CHESSBOARD_BOUNDARY;
            }
        }

        for (int x = 1; x <= SIZE; x++)
        {
            for (int y = 1; y <= SIZE; y++)
            {
                m_chessboard[x][y] = CHESSBOARD_FREE_SPACE;
            }
        }

        m_direction[0].x = -1;
        m_direction[0].y = -1;
        m_direction[1].x = 0;
        m_direction[1].y = -1;
        m_direction[2].x = 1;
        m_direction[2].y = -1;
    }

    void printChessboard(void)
    {
        for (m_solution.move(0); !m_solution.end(); m_solution.next())
        {
            cout << "(" << m_solution.current().x << "," << m_solution.current().y << ")";
        }

        cout << endl;

        for (int x = 0; x < N; x++)
        {
            for (int y = 0; y < N; y++)
            {
                switch(m_chessboard[x][y])
                {
                    case CHESSBOARD_FREE_SPACE:
                        cout << " ";
                        break;
                    case QUEUE:
                        cout << "#";
                        break;
                    case CHESSBOARD_BOUNDARY:
                        cout << "*";
                        break;
                }
            }

            cout << endl;
        }
        cout << endl;
    }

    bool CheckQueue(int x, int y, int direction)
    {
        bool flag = true;

        do
        {
            x += m_direction[direction].x;
            y += m_direction[direction].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }
        while (flag);

        return (m_chessboard[x][y] == 2);
    }

    void run(int y)
    {
        if (y <= SIZE)
        {
            for (int x = 1; x <= SIZE; x++)
            {
                if (CheckQueue(x, y, 0) && CheckQueue(x, y, 1) && CheckQueue(x, y, 2))
                {
                    m_chessboard[x][y] = QUEUE;
                    m_solution.insert(Pos(x, y));

                    run(y + 1);

                    m_chessboard[x][y] = CHESSBOARD_FREE_SPACE;
                    m_solution.remove(m_solution.length() - 1);
                }
            }
        }
        else
        {
            m_count++;

            printChessboard();
        }
    }
public:
    QueueSolution()
    {
        init();
    }

    void ChessStart(void)
    {
        run(1);

        cout << "Total: " << m_count << endl;
    }
};

}

#endif // QUEUESOLUTION_H
