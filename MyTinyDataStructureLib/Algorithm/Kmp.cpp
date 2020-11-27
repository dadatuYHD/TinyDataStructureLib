#include "Kmp.h"
#include <cstring>
#include <cstdlib>

namespace MyTiny_DSLib {

int * MakePmt(const char * src)
{
    int len = strlen(src);

    int * pmt = static_cast<int *>(malloc(sizeof(int) * len));

    if (pmt)
    {
        int ll = 0;

        pmt[0] = 0;

        for (int i = 1; i < len; i++)
        {
            while ((src[i] != src[ll]) && ll > 0)
            {
                ll = pmt[ll - 1];
            }

            if (src[i] == src[ll])
            {
                ll++;
            }

            pmt[i] = ll;
        }
    }

    return pmt;
}

int kmp(const char * ds, const char * src)
{
    int ret = -1;
    int dsLen = strlen(ds);
    int srcLen = strlen(src);
    int * pmt = MakePmt(src);

    for (int i = 0, j = 0; i < dsLen; i++)
    {
        while ((j > 0) && (ds[i] != src[j]))
        {
            j = pmt[j - 1];
        }

        if (ds[i] == src[j])
        {
            j++;
        }

        if (j == srcLen)
        {
            ret = i + 1 - srcLen;
            break;
        }
    }

    free(pmt);

    return ret;
}

}
