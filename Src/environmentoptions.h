#ifndef ENVIRONMENTOPTIONS_H
#define ENVIRONMENTOPTIONS_H
#include "gl_const.h"

class EnvironmentOptions
{
public:
    EnvironmentOptions(bool allowsqueeze, bool allowdiagonal, bool cutcorners,
                       int metrictype = CN_SP_MT_EUCL, int ST = CN_SP_ST_ASTAR, double hweight = 1.0);
    EnvironmentOptions();
    int     metrictype;     //Can be chosen Euclidean, Manhattan, Chebyshev and Diagonal distance
    bool    allowsqueeze;   //Option that allows to move throught "bottleneck"
    bool    allowdiagonal;  //Option that allows to make diagonal moves
    bool    cutcorners;     //Option that allows to make diagonal moves, when one adjacent cell is untraversable
    int     searchtype;
    double  hweight;
};

#endif // ENVIRONMENTOPTIONS_H
