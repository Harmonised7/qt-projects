#include "util.h"

QMap<QString, double> Util::unitRatios =
{
    {
        "Meters", 1
    },
    {
        "Inches", 39.3701
    },
    {
        "Kilograms", 1
    },
    {
        "Pounds", 2.20462
    }
};

QMap<QString, double> Util::prefixMultipliers =
{
    {
        "M", 1000000
    },
    {
        "k", 1000
    },
    {
        "d", 0.1
    },
    {
        "", 1
    },
    {
        "c", 0.01
    },
    {
        "m", 0.001
    },
    {
        "μ", 0.000001
    }
};

double Util::cap( double input, double min, double max )
{
    return Util::min( max, Util::max( min, input ) );
}

double Util::min( double a, double b )
{
    return a > b ? b : a;
}

double Util::max( double a, double b )
{
    return a > b ? a : b;
}

double Util::getConvertedUnit( double input, QString inputUnit, QString outputUnit, QString inputPrefix, QString outputPrefix )
{
    return input / unitRatios[ inputUnit ] * unitRatios[ outputUnit ] * prefixMultipliers[ inputPrefix ] / prefixMultipliers[ outputPrefix ];
}
