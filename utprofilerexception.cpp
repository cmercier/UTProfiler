#include "utprofilerexception.h"

UTProfilerException::UTProfilerException(const QString &info, const QString &fileName, unsigned int line):
    info_(info),
    file_(fileName),
    line_(line)
{
}
