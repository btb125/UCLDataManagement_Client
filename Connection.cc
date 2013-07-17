#include "Connection.h"

Connection::Connection()
{
    HEADER_START = 0 ;
    HEADER_END = 8 ;
    MESSAGE_START = HEADER_END ;
    MESSAGE_END = -1 ;
}

void Connection::read(std::string input)
{
    decoupleMessage(input) ;
}

std::string Connection::write()
{
    /*
     * Output Message
     */
    std::string faoServer = outboundHeader.append(outboundMessage) ;

    /*
     * Clear I/O
     */
    clear() ;

    return faoServer ;
}

std::string Connection::getInboundHeader()
{
    return this->inboundHeader ;
}

void Connection::setInboundHeader(std::string header)
{
    this->inboundHeader = header ;
}

std::string Connection::getOutboundHeader()
{
    return this->outboundHeader ;
}

void Connection::setOutboundHeader(std::string header)
{
    /*
     * Ensure Header is EXACTLY 8 Characters long
     */
    if (header.length() < 8)
    {
        while (header.length() < 8)
        {
            header.append(" ") ;
        }
    }
    else if (header.length() > 8)
    {
        header = header.append(header, 0, 8) ;
    }

    this->outboundHeader = header ;
}

std::string Connection::getInboundMessage()
{
    return this->inboundMessage ;
}

void Connection::setInboundMessage(std::string message)
{
    this->inboundMessage = message ;
}

std::string Connection::getOutboundMessage()
{
    return this->outboundMessage ;
}

void Connection::setOutboundMessage(std::string message)
{
    this->outboundMessage = message ;
}

void Connection::setOutboundMessage(Login login)
{
    //Serialize & Update Outbound Data
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << login ;

        //Update Outbound
        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(AccessPermissionList apl)
{
    //Serialize & Update Outbound Data
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << apl ;

        //Update Outbound
        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(std::vector<AccessPermissionList>& apls)
{
    //Serialize APLs To Be Deleted
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(apls) ;

        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(User user)
{
    //Serialize & Update Outbound Data
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << user ;

        //Update Outbound
        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(std::vector<User>& users)
{
    //Serialize Users To Be Deleted
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(users) ;

        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(Participant participant)
{
    //Serialize & Update Outbound Data
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << participant ;

        //Update Outbound
        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(std::vector<Participant>& participants)
{
    //Serialize Participants To Be Deleted
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(participants) ;

        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::coupleMessage(std::string header, std::string message)
{
    header = message ; //Hide Warning
}

void Connection::decoupleMessage(std::string messageIn)
{
    this->inboundHeader = messageIn.substr(HEADER_START, HEADER_END) ;
    this->inboundMessage = messageIn.substr(MESSAGE_START, messageIn.length()-MESSAGE_END) ;
}

void Connection::clear()
{
    inboundHeader = " " ;
    inboundMessage = " " ;

    outboundHeader = " " ;
    outboundMessage = " " ;
}

User Connection::readUser()
{
    User user ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> user ;
    }

    return user ;
}

std::vector<User> Connection::readUsers()
{
    std::vector<User> users ;

    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(users) ;
    }

    return users ;
}

AccessPermissionList Connection::readAccessPermissionList()
{
    AccessPermissionList apl ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> apl ;
    }

    return apl ;
}

std::vector<AccessPermissionList> Connection::readAccessPermissionLists()
{
    std::vector<AccessPermissionList> apls ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(apls) ;
    }

    return apls ;
}

Participant Connection::readparticipant()
{
    Participant participant ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> participant ;
    }

    return participant ;
}

std::vector<Participant> Connection::readParticipants()
{
    std::vector<Participant> participants ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(participants) ;
    }

    return participants ;
}

void Connection::setOutboundMessage(Questionnaire questionnaire)
{
    //Serialize & Update Outbound Data
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << questionnaire ;

        //Update Outbound
        setOutboundMessage(archiveStream.str()) ;
    }
}

void Connection::setOutboundMessage(std::vector<Questionnaire>& questionnaires)
{
    //Serialize Questionnaire Info
    {
        std::ostringstream archiveStream ;
        boost::archive::text_oarchive archive(archiveStream) ;
        archive << BOOST_SERIALIZATION_NVP(questionnaires) ;

        //Set Outbound Message to Serialized Info
        this->outboundMessage = archiveStream.str() ;
    }
}

Questionnaire Connection::readQuestionnaire()
{
    Questionnaire questionnaire ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> questionnaire ;
    }

    return questionnaire ;
}

std::vector<Questionnaire> Connection::readQuestionnaires()
{
    qDebug() << "a" ;
    std::vector<Questionnaire> questionnaires ;
    {
        std::istringstream archiveStream(inboundMessage) ;
        boost::archive::text_iarchive archive(archiveStream) ;
        archive >> BOOST_SERIALIZATION_NVP(questionnaires) ;
    }

    qDebug() << "b" ;
    return questionnaires ;
}
