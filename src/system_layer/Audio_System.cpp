#include "Audio_System.h"

Audio_System::Audio_System(shared_ptr<spdlog::logger> l,
                           shared_ptr<Message_Bus> mb)
{
    logger = l;
    message_bus = mb;
}

Audio_System::~Audio_System()
{

}

void Audio_System::handle_message(shared_ptr<Message> message)
{
    /*
    switch (message->get_id())
    {
        case KEY_UPDATE:
        {
            logger->error("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH!");
            //music_ptr->play();
        }
        break;
    }
    */
}
