#include "ServerInformation.h"

ServerInformation::ServerInformation(QObject *parent) :
    QObject(parent)
{
    /*
     * Only Called Within Class
     */

    socket = new QTcpSocket(this) ;

    this->ipAddress = "localhost" ;
    this->port = 1234 ;
}

ServerInformation* ServerInformation::_instance = NULL ;

ServerInformation* ServerInformation::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new ServerInformation() ;
    }

    return _instance ;
}

QTcpSocket* ServerInformation::getSocket()
{
    return this->socket ;
}

std::string ServerInformation::getIPAddress()
{
    return this->ipAddress ;
}

int ServerInformation::getPort()
{
    return this->port ;
}
