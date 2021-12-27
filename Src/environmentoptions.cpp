#include "environmentoptions.h"

EnvironmentOptions::EnvironmentOptions()
{
    metrictype = CN_SP_MT_EUCL;
    allowsqueeze = false;
    allowdiagonal = true;
    cutcorners = false;
    searchtype = CN_SP_ST_ASTAR;
    hweight = 1.0;
}

EnvironmentOptions::EnvironmentOptions(bool allowsqueeze, bool allowdiagonal, bool cutcorners,
                                       int metrictype, int serchtype, double hweight)
{
    this->allowsqueeze = allowsqueeze;
    this->allowdiagonal = allowdiagonal;
    this->cutcorners = cutcorners;
    this->metrictype = metrictype;
    this->searchtype = serchtype;
    this->hweight = hweight;
}

