#include "moos_inputmanager.h"
#include "moos_eventhub.h"
#include "moos_logger.h"

DEFINE_NAMESPACE_MOOS_BEGIN

MoosRawEvent S_RAWEVENTS[32];

MoosInputReader::MoosInputReader(MoosEventHub* hub_)
    : MoosThread()
    , m_eventHub(hub_)
{

}



bool MoosInputReader::threadRun()
{
    size_t _s = m_eventHub->getEvents(S_RAWEVENTS, 32);
    MOOS_DEBUG_LOG("input event size: ", _s);
    if (_s > 0) {
        SIG_RAWEVENTS.emit(S_RAWEVENTS, std::move(_s));
    }
    return true;
}

MoosInputManager::MoosInputManager()
{
    m_eventHub = new MoosEventHub();
    m_inputreader = new MoosInputReader(m_eventHub);
}

void MoosInputManager::start()
{
    m_eventHub->scanDevices();
    m_inputreader->start();
}





DEFINE_NAMESPACE_MOOS_END

