////
//// Created by robin on 01.05.17.
////
//
//#include "EventManager.h"
//
//ebox::EventManager::EventManager(sf::RenderWindow *renderWindow)
//{
//    initialize(renderWindow);
//}
//
///*!
// * Must be called if the default constructor is ran, otherwise not needed
// * @param renderWindow
// */
//void ebox::EventManager::initialize(sf::RenderWindow *renderWindow)
//{
//    m_window = renderWindow;
//}
//
//ebox::EventManager::~EventManager()
//{
//
//}
//
//
//void ebox::EventManager::update()
//{
//    fillEventList();
//    manageKeyReleased();
//    //std::vector<sf::Event> keyDownEvents = from(events) >> where([](sf::Event evt) { return (evt.type == sf::Event::KeyPressed); }) >> to_vector();
//}
//
//std::vector<sf::Event> ebox::EventManager::getEvents(const sf::Event::EventType &eventType)
//{
//    //std::vector<sf::Event> events = from(m_events) >> where([](sf::Event evt) { return (evt.type == eventType); }) >> to_vector();
//    std::vector<sf::Event> result = from(m_events) >> where([&eventType](sf::Event evt) { return (evt.type == eventType); }) >> to_vector();
//    std::vector<sf::Event> events;// = new std::vector<sf::Event>();
//
//    for (sf::Event evt : result) {
//        events.push_back(evt);
//    }
//
//    return events;
//}
//
//bool ebox::EventManager::isKeyPressed(const sf::Keyboard::Key &key)
//{
//
//    std::vector<sf::Event> keysPressed = getEvents(sf::Event::KeyPressed);
//    std::vector<sf::Event> keyPresses = from(keysPressed) >> where([&key](sf::Event evt) { return (evt.key.code == key); }) >> to_vector();
//
//    if(keyPresses.size() > 0)
//    {
//        for (int i = 0; i < m_pressedKeys.size(); ++i)
//        {
//            if(m_pressedKeys[i] == keyPresses[0].key.code)
//                return false;
//        }
//        m_pressedKeys.push_back(keyPresses[0].key.code);
//    }
//
//
//
//    return (keyPresses.size() > 0) ? true : false;
//}
//
//bool ebox::EventManager::isKeyDown(const sf::Keyboard::Key &key)
//{
//    //std::vector<sf::Event> * keysPressed = getEvents(sf::Event::KeyPressed);
//    //std::vector<sf::Event> keyPresses = from(*keysPressed) >> where([&key](sf::Event evt) { return (evt.key.code == key); }) >> to_vector();
//
//    //return (keyPresses.size() > 0) ? true : false;
//    return (sf::Keyboard::isKeyPressed(key));
//}
//
//bool ebox::EventManager::isKeyReleased(const sf::Keyboard::Key &key)
//{
//    std::vector<sf::Event> keysPressed = getEvents(sf::Event::KeyReleased);
//    std::vector<sf::Event> keyPresses = from(keysPressed) >> where([&key](sf::Event evt) { return (evt.key.code == key); }) >> to_vector();
//
//    return (keyPresses.size() > 0) ? true : false;
//}
//
//void ebox::EventManager::fillEventList()
//{
//    m_events.clear();
//    sf::Event event;
//    while(m_window->pollEvent(event))
//    {
//        m_events.push_back(event);
//    }
//}
//
//void ebox::EventManager::manageKeyReleased()
//{
//    std::vector<sf::Event> keysReleased = getEvents(sf::Event::KeyReleased);
//    //std::vector<sf::Event> keyPresses = from(*keysPressed) >> where([&key](sf::Event evt) { return (evt.key.code == key); }) >> to_vector();
//
//    for (unsigned int i = 0; i < keysReleased.size(); ++i)
//    {
//        for(unsigned int j = 0; j < m_pressedKeys.size(); j++)
//        {
//            sf::Event evt = keysReleased.at(i);
//            sf::Keyboard::Key key = m_pressedKeys[j];
//            if(evt.key.code == key)
//            {
//                m_pressedKeys.erase(m_pressedKeys.begin() + j);
//                j--;
//            }
//
//        }
//    }
//}
//
//std::vector<sf::Event> &ebox::EventManager::getAllEvents()
//{
//    return m_events;
//}
//
//
