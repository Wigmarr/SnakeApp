#include "nopathexception.h"

NoPathException::NoPathException(QString message) : message(message)
{
}

QString NoPathException::what()
{
    return message;
}
