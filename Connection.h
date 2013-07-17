#ifndef CONNECTION_H
#define CONNECTION_H

/*
 * Serialization (Boost)
 */
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>

#include "Login.h"
#include "User.h"
#include "AccessPermissionList.h"
#include "Participant.h"
#include "Questionnaire.h"

#include <QDebug>
#include <QString>

#include <string>

class Connection
{
public:
    Connection();

    /*
     * Read & Write Calls
     */
    void read(std::string input) ;
    std::string write() ;

    /*
     * RE Header
     */
    std::string getInboundHeader() ;
    void setInboundHeader(std::string header) ;
    std::string getOutboundHeader() ;
    void setOutboundHeader(std::string header) ;

    /*
     * RE Message
     */
    std::string getInboundMessage() ;
    void setInboundMessage(std::string message) ;
    std::string getOutboundMessage() ;
    void setOutboundMessage(std::string message) ;

    void setOutboundMessage(Login login) ;
    void setOutboundMessage(AccessPermissionList apl) ;
    void setOutboundMessage(std::vector<AccessPermissionList>& apls) ;
    void setOutboundMessage(User user) ;
    void setOutboundMessage(std::vector<User>& users) ;
    void setOutboundMessage(Participant participant) ;
    void setOutboundMessage(std::vector<Participant>& participants) ;
    void setOutboundMessage(Questionnaire questionnaire) ;
    void setOutboundMessage(std::vector<Questionnaire>& questionnaires) ;

    AccessPermissionList readAccessPermissionList() ;
    std::vector<AccessPermissionList> readAccessPermissionLists() ;

    User readUser() ;
    std::vector<User> readUsers() ;

    Participant readparticipant() ;
    std::vector<Participant> readParticipants() ;

    Questionnaire readQuestionnaire() ;
    std::vector<Questionnaire> readQuestionnaires() ;

private:
    int HEADER_START ; //= 0 ;
    int HEADER_END ; //= 8 ;
    int MESSAGE_START ; //= HEADER_END ;
    int MESSAGE_END ; //= -1 ;

    std::string inboundHeader ;
    std::string inboundMessage ;

    std::string outboundHeader ;
    std::string outboundMessage ;

    void coupleMessage(std::string header, std::string message) ;
    void decoupleMessage(std::string messageIn) ;

    void clear() ;

    void login() ;



};

#endif // CONNECTION_H
