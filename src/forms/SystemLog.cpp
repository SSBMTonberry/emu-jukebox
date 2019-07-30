//
// Created by robin on 21.01.19.
//

#include "SystemLog.h"


const std::string ebox::SystemLog::ID = "System log";

ebox::SystemLog::SystemLog(const sf::Vector2<int> &sizeOnFirstUse) : m_size {sizeOnFirstUse}
{

}

/*!
 * Pushes a message to the FRONT, making sure the last message is the one you see first.
 * @param text
 * @param color
 */
void ebox::SystemLog::add(const std::string &text, const sf::Color &color)
{
    //m_controls.push_back(std::make_unique<ebox::Label>(fmt::format("debugtext_{0}", m_nextId), text, "Grass ass", ebox::LabelType::OnlyLabel));
    //m_texts.emplace_back(text, color);
    m_texts.emplace(m_texts.begin(), text, color);
    ++m_nextId;
}

void ebox::SystemLog::clear()
{
    m_texts.clear();
    m_nextId = 0;
}

void ebox::SystemLog::addTestTexts()
{
    for(int i = 0; i < 2; ++i)
    {
        addSuccess("AAAAW YEEEEEEAAAA!");
        addInfo("Infolini");
        addWarning("I warned you!");
        addError("Oh, shit!");
        add("It's a nice day to be beaten up", sf::Color::Red);
        add("Ouch!", sf::Color::Blue);
        add("Holy shitfuck! That really did hurt", sf::Color::Magenta);
        add("Eye for an eye, shit for shit", sf::Color::Cyan);
        add("Grimmer than the dimmer", sf::Color::Yellow);
        add("Crabs of crap");
    }
}

bool ebox::SystemLog::process()
{
    bool valueChanged = false;
    if(m_isVisible && m_isOpen)
    {
        if(m_positionHasBeenChanged)
        {
            ImGui::SetNextWindowPos(ImVec2(m_position));
            ImGui::SetNextWindowSize(ImVec2(m_size));
            m_positionHasBeenChanged = false;
        }

        ImGui::SetNextWindowSize(m_size, ImGuiCond_FirstUseEver);
        ImGui::Begin(ID.c_str(), &m_isOpen, 0);
        ImGui::BeginChild("debug_child_1", {-1, 60 * m_scaleFactor}, true, 0);
        if (m_filter.process())
        {
            valueChanged = true;
            m_filteredTexts = getFilteredTexts(m_filter.getValue());
        }
        //ImGui::SameLine();
        if (ImGui::SmallButton("Clear log"))
        {
            clear();
        }
        ImGui::EndChild();

        ImGui::BeginChild("debug_child_2", {-1, -1}, false, 0);
        if (m_filter.getValue().size() > 0)
        {
            for (auto &text : m_filteredTexts)
                //for (auto i = m_filteredTexts.rbegin(); i != m_filteredTexts.rend(); ++i)
            {
                text.process();
                //ImGui::Text(text.c_str());
            }
        }
        else
        {
            for (auto &text : m_texts)
            {
                text.process();
            }
        }
        ImGui::EndChild();
        ImGui::End();
    }
    return valueChanged;
}

bool ebox::SystemLog::isOpen() const
{
    return m_isOpen;
}

std::vector<pmgui::ColoredText> ebox::SystemLog::getFilteredTexts(const std::string &filter)
{
    std::vector<pmgui::ColoredText> filteredTexts;
    /*std::copy_if(m_texts.begin(), m_texts.end(),
                 std::back_inserter(filteredTexts),
                 [&filter](const std::string& s) { return s.find(filter) != std::string::npos; });*/
    std::copy_if(m_texts.begin(), m_texts.end(),
                 std::back_inserter(filteredTexts),
                 [&filter](const pmgui::ColoredText& s) { return s.getText().find(filter) != std::string::npos; });

    return filteredTexts;
}

void ebox::SystemLog::addSuccess(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[SUCCESS] ({0}) - {1}", getTimestamp(), text) : fmt::format("[SUCCESS] {1}", text);
    add(msg, SuccessColor);
}

void ebox::SystemLog::addInfo(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[INFO]    ({0}) - {1}", getTimestamp(), text) : fmt::format("[INFO] {1}", text);
    add(msg, InfoColor);
}

void ebox::SystemLog::addWarning(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[WARNING] ({0}) - {1}", getTimestamp(), text) : fmt::format("[WARNING] {1}", text);
    add(msg, WarningColor);
}

void ebox::SystemLog::addError(const std::string &text, bool useTimestamp)
{
    std::string msg = (useTimestamp) ? fmt::format("[ERROR]   ({0}) - {1}", getTimestamp(), text) : fmt::format("[ERROR] {1}", text);
    add(msg, ErrorColor);
}

void ebox::SystemLog::addDebug(const std::string &text, bool useTimestamp)
{
    #if EBOX_DEBUG
    std::string msg = (useTimestamp) ? fmt::format("[DEBUG]   ({0}) - {1}", getTimestamp(), text) : fmt::format("[DEBUG] {1}", text);
    add(msg, DebugColor);
    #endif
}

std::string ebox::SystemLog::getTimestamp(bool includeDate)
{
    auto now = std::chrono::system_clock::now();
    time_t cftime = std::chrono::system_clock::to_time_t(now);
    std::string timefmt = fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
    return timefmt;
}

void ebox::SystemLog::setOpen(bool open)
{
    m_isOpen = open;
}

void ebox::SystemLog::setIsVisible(bool isVisible)
{
    m_isVisible = isVisible;
}

void ebox::SystemLog::setSize(const sf::Vector2<int> &size)
{
    m_positionHasBeenChanged = true;
    m_size = size;
}

void ebox::SystemLog::setPosition(const sf::Vector2<int> &position)
{
    m_positionHasBeenChanged = true;
    m_position = position;
}

const sf::Vector2<int> &ebox::SystemLog::getSize() const
{
    return m_size;
}

const sf::Vector2<int> &ebox::SystemLog::getPosition() const
{
    return m_position;
}

bool ebox::SystemLog::isVisible() const
{
    return m_isVisible;
}

float ebox::SystemLog::getScaleFactor() const
{
    return m_scaleFactor;
}

void ebox::SystemLog::setScaleFactor(float scaleFactor)
{
    m_scaleFactor = scaleFactor;
}
