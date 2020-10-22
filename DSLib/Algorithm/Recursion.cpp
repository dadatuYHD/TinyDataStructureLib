#include "Recursion.h"
#include <iostream>
#include <cstring>
#include "Object/Object.h"
#include "List/LinkList.h"

using namespace std;

namespace DSLib {


/************************************************************
 * FUNCTION:HanoiTower()
 * Description:Move the wooden block on the A pillar to the C pillar,
 * and the small wooden block cannot be under the big wooden block
 * during the moving process
 * Arguments[n][In]:Number of wood blocks
 * Arguments[a、b、c][In]:pillar
 * return:void
 * *********************************************************/
void HanoiTower(int n, char a, char b, char c) // a:src b:middle c:dest
{
    if (n == 1)
    {
        cout << a << "-->" << c << endl;
    }
    else
    {
        HanoiTower(n-1, a, c, b);
        HanoiTower(1, a, b, c);
        HanoiTower(n-1, b, a, c);
    }
}

/************************************************************
 * FUNCTION:permutation()
 * Description:Full array of strings
 * Arguments[s][In]:string
 * Arguments[e][In]:Point to the first address of the string array
 * return:void
 * *********************************************************/
void permutation(char *s, char * e)
{
    if (*s == '\0')
    {
        cout << e << endl;
    }
    else
    {
        int len = strlen(s);

        for (int i = 0; i < len; i++)
        {
            if ((i != 0) && (s[0] == s[i])) continue;

            swap(s[0], s[i]);
            permutation(s + 1, e);
            swap(s[0], s[i]);
        }
    }
}

}


