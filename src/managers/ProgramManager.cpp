//
// Created by robin on 10.01.19.
//

#include "ProgramManager.h"

ebox::ProgramManager::ProgramManager(int argc, char **argv, char** envp)
{

}

void ebox::ProgramManager::initialize(const std::string &title, const sf::Vector2<uint> &resolution, sf::Uint32 style,
                                      const sf::ContextSettings &settings)
{

}

void ebox::ProgramManager::initializeArgs(int argc, char **argv, char **envp)
{
    m_args.reserve(argc);
    while (*argv)
    {
        m_args.emplace_back(*argv++);
    }

    //Parse environment variables
    while (*envp)
    {
        std::vector<std::string> splitalini = ebox::tools::string::SplitString(*envp, '=');
        if(splitalini.size() > 1)
        {
            m_environmentMap[splitalini[0]] = splitalini[1];
        }
        //*envp++;
        m_environmentList.emplace_back(*envp++);
    }
}

void ebox::ProgramManager::run()
{

}

