#ifndef VERSION_H
#define VERSION_H


// VERSION PARAMETERS

static const int V_YEAR = 2016;
static const int V_MONTH = 06;
static const int V_DAY = 22;

static const QString currentversion = QStringLiteral("%1-").arg(V_YEAR)+QStringLiteral("%1-").arg(V_MONTH)+QStringLiteral("%1").arg(V_DAY);

static const int cvid = (V_YEAR-2000)*1000+V_MONTH*100+V_DAY;

#endif // VERSION_H
