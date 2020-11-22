#ifndef NOPATHEXCEPTION_H
#define NOPATHEXCEPTION_H
#include "exception"
#include <QString>
class NoPathException : public std::exception
{
    QString message;
public:
    NoPathException(QString message);
    QString what();
};

#endif // NOPATHEXCEPTION_H
