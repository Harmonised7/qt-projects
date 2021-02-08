#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <QMap>

class Util
{
public:
    //Objects
    static QMap<QString, double> unitRatios;
    static QMap<QString, double> prefixMultipliers;

    //Methods
    static double cap( double input, double min, double max );
    static double min( double a, double b );
    static double max( double a, double b );

    static double getConvertedUnit( double input, QString inputUnit, QString outputUnit, QString inputPrefix, QString outputPrefix );
};

#endif // UTIL_H
