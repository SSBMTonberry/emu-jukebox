//
// Created by robin on 20.01.19.
//

#include "FileDialog.h"

ebox::FileDialog::FileDialog(const DialogType &dialogType, std::string id, std::string title, std::string imguiId) :
        Popup(std::move(id), std::move(title), std::move(imguiId))
{
    m_dialogType = dialogType;
    initialize();
}

ebox::FileDialog::FileDialog(const DialogType &dialogType, const sf::Vector2<int> &position, const sf::Vector2<int> &size,
                            std::string id, std::string title, std::string imguiId) : Popup(position, size, std::move(id), std::move(title),
                                                                                            std::move(imguiId))
{
    m_dialogType = dialogType;
    initialize(m_position, m_size);
}

void ebox::FileDialog::initialize(const std::optional<sf::Vector2<int>> &position, const std::optional<sf::Vector2<int>> &size)
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    if(!size.has_value()) setSize({(int)desktop.width / 3, (int)desktop.height / 3});
    if(!position.has_value()) setPosition({((int)desktop.width / 2) - (m_size.x / 2), ((int)desktop.height / 2) - (m_size.y / 2)});
    setFormFlags(ebox::FormFlags::NoResize | ebox::FormFlags::NoCollapse | ebox::FormFlags::AlwaysAutoResize);// | ebox::FormFlags::NoScrollbar);

    setPath(fs::current_path());

    //registerOnFileChosenCallback(std::bind(&ProgramManager::onChosenNewProject, this, std::placeholders::_1));
    initializePopups();

    createLayout();
    update();
}

void ebox::FileDialog::createLayout()
{
    m_upperLabel.setHasTitle(false);
    m_upperLeftChild.setSize({(int)(m_size.x * 0.05f), (int)(m_size.y * 0.07f)});
    m_upperLeftChild.addReference(&m_upperLabel);

    m_upperMiddleChild.setSize({(int)(m_size.x * 0.8f), (int)(m_size.y * 0.07f)});
    m_upperMiddleChild.setOnSameLine(true);
    m_filepathtext.setHasLabel(false);
    m_filepathtext.setValue(getPath().string());
    m_upperMiddleChild.addReference(&m_filepathtext);

    m_upperRightChild.setSize({(int)(m_size.x * 0.15f), (int)(m_size.y * 0.07f)});
    m_upperRightChild.setOnSameLine(true);
    m_upperRightChild.addReference(&m_refreshbtn);

    m_upperGroup.addReference(&m_upperLeftChild);
    m_upperGroup.addReference(&m_upperMiddleChild);
    m_upperGroup.addReference(&m_upperRightChild);

    m_midRightChild.setSize({-1, (int)(m_size.y * 0.7f)});
    m_midRightChild.setHasBorder(true);
    m_midRightChild.addReference(&m_fileTable);

    m_midGroup.addReference(&m_midRightChild);

    m_bottomchildleft.setSize({(int)(m_size.x * 0.1f), (int)(m_size.y * 0.18f)});
    m_filenameLabel.setHasTitle(false);
    m_filetypeLabel.setHasTitle(false);
    m_bottomchildleft.addReference(&m_filenameLabel);
    m_bottomchildleft.addReference(&m_filetypeLabel);

    m_bottomchildmid.setSize({(int)(m_size.x * 0.74f), (int)(m_size.y * 0.18f)});
    m_bottomchildmid.setOnSameLine(true);
    m_filenametext.setHasLabel(false);
    m_fileTypeCombo.setHasLabel(false);
    m_bottomchildmid.addReference(&m_filenametext);
    m_bottomchildmid.addReference(&m_fileTypeCombo);

    m_bottomchildright.setSize({(int)(m_size.x * 0.2f), (int)(m_size.y * 0.18f)});
    m_bottomchildright.setOnSameLine(true);
    m_okBtn.setLabel(getOkBtnText());
    m_okBtn.setSize({(int)(m_size.x * 0.1f), (int)(m_size.y * 0.045f)});
    m_cancelBtn.setSize({(int)(m_size.x * 0.1f), (int)(m_size.y * 0.045f)});
    m_bottomchildright.addReference(&m_okBtn);
    m_bottomchildright.addReference(&m_cancelBtn);

    m_bottomGroup.addReference(&m_bottomchildleft);
    m_bottomGroup.addReference(&m_bottomchildmid);
    m_bottomGroup.addReference(&m_bottomchildright);

    addReference(&m_upperGroup);
    addReference(&m_midGroup);
    addReference(&m_bottomGroup);

    setFileTypes(FileTypeMode::EmuFiles);
}

void ebox::FileDialog::handleEvents()
{
    if(m_open)
    {
        if (m_refreshbtn.isPressed() || m_filepathtext.isChanged())
        {
            m_path = (m_filepathtext.isChanged()) ? fs::path(m_filepathtext.getValue())
                                                  : m_fileTable.getLastOpenedPath();
            if (m_refreshbtn.isPressed())
                m_filepathtext.setValue(m_path.string());

            if (fs::exists(m_path))
            {
                m_fileTable.listFilesByDirectory(m_path,
                                                 (m_path.has_parent_path()) ? m_path.parent_path() : fs::path(""));
            }
        }

        if (m_fileTable.canCallPathOpening())
        {
            const auto pathToOpen = m_fileTable.getPathToOpen();

            if (fs::exists(pathToOpen) && fs::is_directory(pathToOpen))
            {
                m_filepathtext.setValue(pathToOpen.string());
                m_path = pathToOpen;
                m_fileTable.listFilesByDirectory(pathToOpen,
                                                 (pathToOpen.has_parent_path()) ? pathToOpen.parent_path()
                                                                                : fs::path(""));
            }
            m_fileTable.resetPathOpeningCall();
        }

        if (m_fileTypeCombo.valueHasBeenChosen())
        {
            std::string filter = m_filetypeFilter[m_fileTypeCombo.getValue()];
            m_fileTable.setFileFilter(filter);
        }

        if (m_fileTable.canCallRowChangeEvent())
        {
            std::string selectedFile = m_fileTable.getSelectedFile();
            if (selectedFile.length() > 0)
            {
                m_filenametext.setValue(selectedFile);
                m_fileTable.resetRowChangeCall();
            }
        }

        if (m_cancelBtn.isPressed())
        {
            m_open = false;
            for (auto &callback : m_callbackOnClose)
                callback();
        }


        if (m_okBtn.isPressed())
        {
            handleFileChosen();
        }
    }
}

const fs::path &ebox::FileDialog::getPath() const
{
    return m_path;
}

void ebox::FileDialog::setPath(const fs::path &path)
{
    m_path = path;
}

void ebox::FileDialog::onOpen()
{
    if(!fs::exists(m_path))
        m_path = m_filepathtext.getValue();
    else
        m_filepathtext.setValue(m_path.string());

    if(fs::exists(m_path))
    {
        m_fileTable.listFilesByDirectory(m_path, (m_path.has_parent_path()) ? m_path.parent_path() : fs::path(""));
    }
}

std::string ebox::FileDialog::getOkBtnText() const
{
    switch(m_dialogType)
    {
        case DialogType::OpenDirectory:
        case DialogType::OpenFile:
            return "Open";

        case DialogType::SaveFile:
        case DialogType::SaveDirectory:
            return "Save";
    }

    return "<undefined>";
}

void ebox::FileDialog::assignEnvironmentMap(unordered_map<string, string> *env)
{
    m_environmentMap = env;
}

std::string ebox::FileDialog::getEnv(const std::string_view &id)
{
    if(m_environmentMap != nullptr && m_environmentMap->count(id.data()) > 0)
        return m_environmentMap->at(id.data());

    return "";
}

void ebox::FileDialog::assignDefaults()
{
    std::string home = getEnv("HOME");
    fs::path homePath = fs::path(home);
    if (home.length() > 0 && fs::exists(homePath))
    {
        m_path = homePath;
        m_filepathtext.setValue(home);
    }
}

/*!
 * Register a callback:
 *
 *
 * @param cb Example of valid parameter: std::bind(&ProgramManager::onChosenProject, this, std::placeholders::_1)
 * Actual function - ebox::ProgramManager::onChosenProject(const std::string &path)
 */
void ebox::FileDialog::registerOnFileChosenCallback(const ebox::func_str &cb)
{
    m_callbackOnFileChosen.emplace_back(cb);
}

void ebox::FileDialog::registerOnCancelCallback(const ebox::func_void &cb)
{
    m_callbackOnClose.emplace_back(cb);
}

void ebox::FileDialog::onMessageResponse(const ebox::Button *btn, const MessagePopupResponse &response)
{
    if(response == MessagePopupResponse::Yes)
    {
        m_open = false;
        for (auto &callback : m_callbackOnFileChosen)
        {
            callback(m_chosenFile.string());
        }
    }
}

const fs::path &ebox::FileDialog::getChosenFile() const
{
    return m_chosenFile;
}

/*!
 * Sets properties for controls based on the dialog type
 */
void ebox::FileDialog::update()
{
    switch(m_dialogType)
    {
        case DialogType::SaveFile:
            //
            break;

        case DialogType::OpenFile:
            m_filenametext.setTextboxFlags(TextboxFlags::ReadOnly);
            break;
    }
}

void ebox::FileDialog::handleFileChosen()
{
    switch(m_dialogType)
    {
        case DialogType::SaveFile:
        {
            string extension = m_fileTable.getFileFilter();
            string filename = m_filenametext.getValue();

            if(filename.length() == 0)
            {
                m_msgPopupNoFileChosen.setOpen(true);
                return;
            }

            if (filename.length() > extension.length() && extension != "*.*")
            {
                std::string sub = filename.substr(filename.length() - extension.length(), filename.length());
                if (sub != extension)
                    filename = filename + extension;
            }
            else if (extension != "*.*")
            {
                filename = filename + extension;
            }
            m_path = m_fileTable.getLastOpenedPath();
            string path = fmt::format("{0}/{1}", m_path.string(), filename);

            if (fs::exists(m_path))
            {
                m_chosenFile = path;
                if (!fs::exists(path))
                {
                    m_open = false;
                    for (auto &callback : m_callbackOnFileChosen)
                        callback(m_chosenFile.string());
                }
                else
                    m_msgPopup.setOpen(true);
            }
        }
            break;

        case DialogType::OpenFile:
        {
            string extension = m_fileTable.getFileFilter();
            string filename = m_filenametext.getValue();

            if(filename.length() == 0)
            {
                m_msgPopupNoFileChosen.setOpen(true);
                return;
            }

            m_path = m_fileTable.getLastOpenedPath();
            string path = fmt::format("{0}/{1}", m_path.string(), filename);

            if (fs::exists(m_path))
            {
                m_chosenFile = path;
                if (fs::exists(path))
                {
                    m_open = false;
                    for (auto &callback : m_callbackOnFileChosen)
                        callback(m_chosenFile.string());
                }
                else
                    m_msgPopupFileDoesNotExist.setOpen(true);
            }
        }
            break;
    }
}

void ebox::FileDialog::initializePopups()
{
    m_msgPopup.setMessage("File already exists!\nAre you sure you want to overwrite \nthe existing file?");
    m_msgPopup.setSize({300, 150});
    m_msgPopup.refresh();
    m_msgPopup.registerOnMsgResponseCallback(std::bind(&FileDialog::onMessageResponse, this, std::placeholders::_1, std::placeholders::_2));

    m_msgPopupNoFileChosen.setMessage("No file chosen!");
    m_msgPopupNoFileChosen.setSize({300, 150});
    m_msgPopupNoFileChosen.refresh();

    m_msgPopupFileDoesNotExist.setMessage("File does not exist!");
    m_msgPopupFileDoesNotExist.setSize({300, 150});
    m_msgPopupFileDoesNotExist.refresh();
}

void ebox::FileDialog::setFileTypes(const ebox::FileTypeMode &mode)
{
    switch(mode)
    {
        case FileTypeMode::None:
            m_fileTypeCombo.clear();
            break;

        case FileTypeMode::EmuFiles:
        {
            m_fileTypeCombo.clear();
            m_fileTypeCombo.addValue("All (*.*)");
            m_fileTypeCombo.addValue("ZX Spectrum/Amstrad CPC (*.ay)");
            m_fileTypeCombo.addValue("Nintendo Game Boy (*.gbs)");
            m_fileTypeCombo.addValue("Sega Genesis/Mega Drive (*.gym)");
            m_fileTypeCombo.addValue("NEC TurboGrafx-16/PC Engine (*.hes)");
            m_fileTypeCombo.addValue("MSX Home Computer/other Z80 systems (*.kss)");
            m_fileTypeCombo.addValue("Nintendo NES/Famicom (*.nsf)");
            m_fileTypeCombo.addValue("Nintendo NES/Famicom Extended (*.nsfe)");
            m_fileTypeCombo.addValue("Atari systems (*.sap)");
            m_fileTypeCombo.addValue("Super Nintendo/Super Famicom (*.spc)");
            m_fileTypeCombo.addValue("Videogame Music (*.vgm)");

            m_filetypeFilter["All (*.*)"] = "*.*";
            m_filetypeFilter["ZX Spectrum/Amstrad CPC (*.ay)"] = ".ay";
            m_filetypeFilter["Nintendo Game Boy (*.gbs)"] = ".gbs";
            m_filetypeFilter["Sega Genesis/Mega Drive (*.gym)"] = ".gym";
            m_filetypeFilter["NEC TurboGrafx-16/PC Engine (*.hes)"] = ".hes";
            m_filetypeFilter["MSX Home Computer/other Z80 systems (*.kss)"] = ".kss";
            m_filetypeFilter["Nintendo NES/Famicom (*.nsf)"] = ".nsf";
            m_filetypeFilter["Nintendo NES/Famicom Extended (*.nsfe)"] = ".nsfe";
            m_filetypeFilter["Atari systems (*.sap)"] = ".sap";
            m_filetypeFilter["Super Nintendo/Super Famicom (*.spc)"] = ".spc";
            m_filetypeFilter["Videogame Music (*.vgm)"] = ".vgm";
            m_fileTypeCombo.setValue(0);
            std::string filter = m_filetypeFilter[m_fileTypeCombo.getValue()];
            m_fileTable.setFileFilter(filter);
        }
            break;

        case FileTypeMode::Sprites:
        {
            m_fileTypeCombo.clear();
            m_fileTypeCombo.addValue("Portable Network Graphics (*.png)");
            m_fileTypeCombo.addValue("Joint Photographic Experts Group (*.jpg)");
            m_fileTypeCombo.addValue("Bitmap (*.bmp)");
            m_fileTypeCombo.addValue("All (*.*)");
            m_filetypeFilter["Portable Network Graphics (*.png)"] = ".png";
            m_filetypeFilter["Joint Photographic Experts Group (*.jpg)"] = ".jpg";
            m_filetypeFilter["Bitmap (*.bmp)"] = ".bmp";
            m_filetypeFilter["All (*.*)"] = "*.*";
            m_fileTypeCombo.setValue(0);
            std::string filter = m_filetypeFilter[m_fileTypeCombo.getValue()];
            m_fileTable.setFileFilter(filter);
        }
            break;
    }
}

bool ebox::FileDialog::customDraw()
{
    m_msgPopup.draw();
    m_msgPopupNoFileChosen.draw();
    m_msgPopupFileDoesNotExist.draw();
    return true;
}