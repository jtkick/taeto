#include "Input_System.h"

Input_System::Input_System(shared_ptr<spdlog::logger> l, shared_ptr<Message_Bus> mb)
{
    logger = l;

    message_bus = mb;

    // I'm probably gonna regret this, but let's just hard-code which
    // keys the input system will poll for game input
    keys = { {'q', false},
             {'w', false},
             {'e', false},
             {'a', false},
             {'s', false},
             {'d', false},
             {' ', false}};
}

Input_System::~Input_System()
{

}

void Input_System::handle_message(shared_ptr<Message> message)
{
    // Watch message bus for Poll_Inputs_Message
    switch (message->get_id())
    {
        case POLL_INPUTS:
        {
            logger->info("Polling inputs...");
            poll_inputs();
        }
    }
}

void Input_System::poll_inputs()
{
    // Loop over each input keyboard key engine is watching
    for (int i = 0; i < keys.size(); i++)
    {
        key_entry &key = keys[i];

        // Bro, fuck SFML
        sf::Keyboard::Key sf_key;
        switch (key.key)
        {
            case 'q':
                sf_key = sf::Keyboard::Q;
                break;

            case 'w':
                sf_key = sf::Keyboard::W;
                break;

            case 'e':
                sf_key = sf::Keyboard::E;
                break;

            case 'a':
                sf_key = sf::Keyboard::A;
                break;

            case 's':
                sf_key = sf::Keyboard::S;
                break;

            case 'd':
                sf_key = sf::Keyboard::D;
                break;

            case ' ':
                sf_key = sf::Keyboard::Space;
                break;


        }

        // Poll key
        bool key_pressed = sf::Keyboard::isKeyPressed(sf_key);

        // If key is different from last time
        if (key_pressed != key.pressed)
        {
            // Update entry
            key.pressed = key_pressed;

            // Notify other systems that key state changed
            shared_ptr<Key_Update_Message> kum = make_shared<Key_Update_Message>(key.key, key.pressed);
            message_bus->post_message(std::move(kum));
        }
    }
}
