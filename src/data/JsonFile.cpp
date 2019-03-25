//
// Created by robin on 25.03.19.
//

#include "JsonFile.h"


void ebox::JsonFile::   createByFile(const std::string &path)
{
    m_data.clear();
    std::ifstream i(path);
    i >> m_data;
}

void ebox::JsonFile::createByMemory(const void *data, size_t size)
{
    m_data.clear();
    std::istringstream i;
    i.rdbuf()->pubsetbuf((char *)data, size);
    i >> m_data;
}

void ebox::JsonFile::createDummyData()
{
    m_data =
            {
                    {"pi", 3.141},
                    {"happy", true},
                    {"name", "Niels"},
                    {"nothing", nullptr},
                    {"answer", {
                                   {"everything", 42}
                           }},
                    {"list", {1, 0, 2}},
                    {"object", {
                                   {"currency", "USD"},
                                 {"value", 42.99}
                           }}
            };
}

void ebox::JsonFile::add(const json &j)
{
    m_data.push_back(j);
}

void ebox::JsonFile::clear()
{
    m_data.clear();
}

bool ebox::JsonFile::hasKey(const std::string &key)
{
    return (m_data.count(key) > 0);
}

size_t ebox::JsonFile::getKeyCount(const std::string &key)
{
    return m_data.count(key);
}

bool ebox::JsonFile::isArray(const std::string &key)
{
    return m_data[key].is_array();
}

void ebox::JsonFile::writeToFile(const std::string &path)
{
    std::ofstream o(path);
    o << std::setw(4) << m_data << std::endl;
}
