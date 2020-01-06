//
// Created by robin on 10.01.19.
//

#include "ProgramManager.h"

const std::string ebox::ProgramManager::DOCK_ROOT_ID = "EmuJukeboxDockRoot";
const std::string ebox::ProgramManager::DOCKSPACE_ID = "EmuJukeboxDockspaceNode";

ebox::ProgramManager::ProgramManager(int argc, char **argv, char** envp)
{
    initializeArgs(argc, argv, envp);
}

void ebox::ProgramManager::initialize(const std::string &title, const sf::Vector2<uint32_t> &resolution, sf::Uint32 style,
                                      const sf::ContextSettings &settings)
{
    m_window.create(sf::VideoMode(resolution.x, resolution.y), title, style, settings);
    m_window.setView(sf::View(sf::FloatRect(0.f, 0.f, resolution.x, resolution.y)));
    m_window.setFramerateLimit(60);
    m_window.setVerticalSyncEnabled(true);
    m_window.resetGLStates(); // call it if you only process ImGui. Otherwise not needed.

    m_fileDialogFile.assignEnvironmentMap(&m_environmentMap);
    m_fileDialogFile.assignDefaults();
    m_fileDialogFile.createFileTypeCollection("EmuFiles", {".ay", ".gbs", ".gym", ".hes", ".kss", ".nsf", ".nsfe", ".sap", ".spc", ".vgm"});
    m_fileDialogFile.setFileTypeCollection("EmuFiles", true);
    m_fileDialogFile.setFileType("*.*");
    //m_fileDialogFile.setUseFileIcons(true);

    m_fileDialogFolder.assignEnvironmentMap(&m_environmentMap);
    m_fileDialogFolder.assignDefaults();
    //m_fileDialogFolder.createFileTypeCollection("Folder", {"directory"}); //FileTypeMode::Folder
    //m_fileDialogFolder.setFileTypeCollection("Folder", false);
    //m_fileDialogFolder.setFileType("directory");
    //m_fileDialogFolder.setFileTypes(FileTypeMode::Folder);

    m_fileDialogSavePlaylist.assignEnvironmentMap(&m_environmentMap);
    m_fileDialogSavePlaylist.assignDefaults();
    m_fileDialogSavePlaylist.addFileType({".epl", "Emu Playlist (*.epl)"});
    m_fileDialogSavePlaylist.createFileTypeCollection("EmuPlaylists", {".epl"});
    m_fileDialogSavePlaylist.setFileTypeCollection("EmuPlaylists", false);
    m_fileDialogSavePlaylist.setFileType(".epl");
    //m_fileDialogSavePlaylist.setFileTypes(FileTypeMode::EmuPlaylists);

    m_fileDialogOpenPlaylist.assignEnvironmentMap(&m_environmentMap);
    m_fileDialogOpenPlaylist.assignDefaults();
    m_fileDialogOpenPlaylist.addFileType({".epl", "Emu Playlist (*.epl)"});
    m_fileDialogOpenPlaylist.createFileTypeCollection("EmuPlaylists", {".epl"});
    m_fileDialogOpenPlaylist.setFileTypeCollection("EmuPlaylists", false);
    m_fileDialogOpenPlaylist.setFileType(".epl");
    //m_fileDialogOpenPlaylist.setFileTypes(FileTypeMode::EmuPlaylists);

    bool openLastOpenedItemOnStartup = initializeFiles();

    m_events.initialize(&m_window);
    m_formManager.initialize(&m_window, &m_events, &m_iniFile);
    m_formManager.showImguiDemoWindow(false);
    createMenu();
    registerCallbacks();

    m_preferences.setIniFile(&m_iniFile);
    m_preferences.initialize({(int)(resolution.x / 3), (int)(resolution.y / 2)});
    m_about.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_about.initialize({(int)(resolution.x / 2.5f), (int)(resolution.y / 2.5f)});
    m_fileExporter.initialize({(int)(resolution.x / 3), (int)(resolution.y / 2.4f)});

    if(openLastOpenedItemOnStartup)
    {
        if(m_iniFile.isLastItemFolder() && fs::is_directory(m_iniFile.getLastOpenedFolder()))
            onFolderChosen(m_iniFile.getLastOpenedFolder());
        else if(!m_iniFile.isLastItemFolder() && fs::is_regular_file(m_iniFile.getLastOpenedFile()))
            onFileChosen(m_iniFile.getLastOpenedFile());
    }
    else
    {
        if (m_args.size() > 1)
        {
            fs::path currentPath = fs::path(m_args[1]);
            if (fs::is_directory(currentPath))
                onFolderChosen(m_args[1]);
            else if(fs::is_regular_file(currentPath))
                onFileChosen(m_args[1]);
        }
    }
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

bool ebox::ProgramManager::initializeFiles()
{
    m_iniFile.load();

    if(!m_iniFile.getLastOpenedFolder().u8string().empty())
    {
        if(!m_iniFile.getLastOpenedFolder().empty())
        {
            m_fileDialogFile.setPath(m_iniFile.getLastOpenedFolder());
            m_fileDialogFolder.setPath(m_iniFile.getLastOpenedFolder());
            m_fileDialogSavePlaylist.setPath(m_iniFile.getLastOpenedFolder());
            m_fileDialogOpenPlaylist.setPath(m_iniFile.getLastOpenedFolder());
        }
    }

    return (m_iniFile.openLastOpenedItemOnStartup()) ? true : false;
}

void ebox::ProgramManager::run()
{
    sf::Clock deltaClock;

    while (m_window.isOpen())
    {
        m_window.clear(m_iniFile.getBackgroundColor());
        update();
        handleEvents();
        draw();
        handleActions();
        processHotkeys();
        //if(ImGui::IsKeyPressed(sf::Keyboard::Key::Escape))
        //    m_window.close();

        if(m_firstRun)
        {
            //m_clipboard.update(); //Update clipboard once on first run!
            m_iniFile.getFontManager()->initialize();
            m_iniFile.applyTheme();
            std::string fontName = m_iniFile.getCurrentFont();
            m_iniFile.getFontManager()->setCurrentFontByName(fontName);
            applyIniFileToProgram();
            m_firstRun = false;

            //Maybe it can solve the problem where you have to unfocus and then re-focus the application (#58)
            m_window.resetGLStates();
        }

        m_window.display();
    }
    m_formManager.shutdown();
    m_iniFile.write();
}

void ebox::ProgramManager::handleEvents()
{
    for(auto &event : m_events.getAllEvents())
    {
        switch(event.type)
        {
            case sf::Event::EventType::GainedFocus:
                SystemLog::get()->addDebug("Window got focus!");
                Hotkeys::get()->setActive(true);
                break;

            case sf::Event::EventType::LostFocus:
                SystemLog::get()->addDebug("Window lost focus!");
                Hotkeys::get()->setActive(false);
                break;

            default:
                break;
        }
    }
}

void ebox::ProgramManager::update()
{
    m_events.update();
    m_formManager.update();
    handleClipboard();
    updateViewMenu();
}

void ebox::ProgramManager::handleClipboard()
{
    if(m_clipboardDelay.getElapsedTime() > std::chrono::milliseconds(100))
    {
        m_clipboard.update();
        m_clipboardDelay.end();
        m_clipboardDelay.reset();
    }

    if(Hotkeys::get()->isProgramHotkeyPressed(Hotkeys::ProgramHotkey::Copy))
        m_clipboardDelay.start();
    else if(Hotkeys::get()->isProgramHotkeyPressed(Hotkeys::ProgramHotkey::Paste))
        m_clipboard.update();
}

void ebox::ProgramManager::handleActions()
{
    m_formManager.handleEvents();
    m_fileDialogFile.handleEvents();
    m_fileDialogFolder.handleEvents();
    m_fileDialogSavePlaylist.handleEvents();
    m_fileDialogOpenPlaylist.handleEvents();
    m_fileExporter.handleEvents();
}

void ebox::ProgramManager::processHotkeys()
{
    if(Hotkeys::get()->isProgramHotkeyPressed(ebox::Hotkeys::ProgramHotkey::OpenFolder))
        m_fileDialogFolder.setOpen(true);
    if(Hotkeys::get()->isProgramHotkeyPressed(ebox::Hotkeys::ProgramHotkey::OpenFile))
        m_fileDialogFile.setOpen(true);
    if(Hotkeys::get()->isProgramHotkeyPressed(ebox::Hotkeys::ProgramHotkey::CloseApplication))
        m_window.close();
}

void ebox::ProgramManager::draw()
{
    drawDock();
    m_menu.process();
    m_formManager.draw();
    m_fileDialogFile.draw();
    m_fileDialogFolder.draw();
    m_fileDialogSavePlaylist.draw();
    m_fileDialogOpenPlaylist.draw();
    m_preferences.draw();
    m_about.draw();
    m_fileExporter.draw();
    ImGui::SFML::Render(m_window);
}

void ebox::ProgramManager::drawDock()
{
    bool open = true;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(DOCK_ROOT_ID.c_str(), &open, window_flags);
    ImGui::PopStyleVar();

    ImGui::PopStyleVar(2);

    if (ImGui::DockBuilderGetNode(ImGui::GetID(DOCKSPACE_ID.c_str())) == nullptr)
    {
        createDock();
    }

    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, m_iniFile.getBackgroundColor());
    ImGuiID dockspace_id = ImGui::GetID(DOCKSPACE_ID.c_str());
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
    ImGui::PopStyleColor();
    ImGui::End();
}

void ebox::ProgramManager::createDock()
{
    ImGuiID dockspace_id = ImGui::GetID(DOCKSPACE_ID.c_str());
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout

    //ImGui::DockBuilderAddNode(dockspace_id); //viewport->Size); // Add empty node
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_Dockspace); // Add empty node
    ImGui::DockBuilderSetNodeSize(dockspace_id, viewport->Size);

    ImGuiID dock_main_id = dockspace_id; // This variable will track the document node, however we are not using it here as we aren't docking anything into it.
    ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
    ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.20f, nullptr, &dock_main_id);
    ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, nullptr, &dock_main_id);

    //ImGui::DockBuilderDockWindow(SystemLog::ID.c_str(), dock_id_bottom);
    //ImGui::DockBuilderDockWindow(FormManager::PROPERTY_EDITOR_ID.c_str(), dock_id_right);
    //ImGui::DockBuilderDockWindow(FormManager::PROJECT_EXPLORER_ID.c_str(), dock_id_left);
    //ImGui::DockBuilderDockWindow("Extra", dock_id_prop);

    ImGui::DockBuilderDockWindow(fmt::format("dummy###{0}", FilelistForm::ID).c_str(), dock_id_left);
    ImGui::DockBuilderDockWindow(fmt::format("dummy###{0}", AudioPlayerForm::ID).c_str(), dock_main_id);
    ImGui::DockBuilderDockWindow(fmt::format("dummy###{0}", PlaylistForm::ID).c_str(), dock_id_right);
    ImGui::DockBuilderDockWindow(SystemLog::ID.c_str(), dock_id_bottom);
    ImGui::DockBuilderFinish(dockspace_id);
}

void ebox::ProgramManager::resetDock()
{
    bool open = true;


    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin(DOCK_ROOT_ID.c_str(), &open, window_flags);
    ImGui::PopStyleVar();

    ImGui::PopStyleVar(2);

    createDock();

    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, m_backgroundColor);
    ImGuiID dockspace_id = ImGui::GetID(DOCKSPACE_ID.c_str());
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
    ImGui::PopStyleColor();
    ImGui::End();

    SystemLog::get()->addDebug("Layout has been reset.");
}

void ebox::ProgramManager::createMenu()
{
    m_menuOpenFolder.setImageRef(&m_openFolderImage);
    m_menuOpenFolder.setShortcut("(<Ctrl>+O)");
    m_menuOpenFile.setImageRef(&m_openFileImage);
    m_menuOpenFile.setShortcut("(<Alt>+O)");
    m_menuSavePlaylist.setImageRef(&m_savePlaylistImage);
    m_menuOpenPlaylist.setImageRef(&m_openPlaylistImage);
    m_menuQuit.setImageRef(&m_imgQuit);
    m_menuQuit.setShortcut("(<Ctrl>+Q)");

    m_menuSettingsReset.setImageRef(&m_resetLayoutImage);
    m_menuSettingsPreferences.setImageRef(&m_preferencesImage);

    m_menuFile.addRef(&m_menuOpenFolder);
    m_menuFile.addRef(&m_menuOpenFile);
    m_menuFile.addRef(&m_menuSavePlaylist);
    m_menuFile.addRef(&m_menuOpenPlaylist);
    m_menuFile.addRef(&m_menuQuit);

    m_menuSettings.addRef(&m_menuSettingsReset);
    m_menuSettings.addRef(&m_menuSettingsPreferences);

    m_menuView.addRef(&m_menuViewAudioPlayer);
    m_menuView.addRef(&m_menuViewFiles);
    m_menuView.addRef(&m_menuViewPlaylist);
    m_menuView.addRef(&m_menuViewSystemlog);

    m_menuToolsExport.setImageRef(&m_imgExport);
    m_menuTools.addRef(&m_menuToolsExport);

    m_menuHelpAbout.setImageRef(&m_imgAbout);
    m_menuHelp.addRef(&m_menuHelpAbout);

    m_menu.addRef(&m_menuFile);
    m_menu.addRef(&m_menuSettings);
    m_menu.addRef(&m_menuView);
    m_menu.addRef(&m_menuTools);
    m_menu.addRef(&m_menuHelp);
}

void ebox::ProgramManager::onChosenMenuItem(pmgui::MenuItem *sender)
{
    if(sender->getId() == m_menuOpenFile.getId()) m_fileDialogFile.setOpen(true);
    else if(sender->getId() == m_menuOpenFolder.getId()) m_fileDialogFolder.setOpen(true);
    else if(sender->getId() == m_menuSavePlaylist.getId()) m_fileDialogSavePlaylist.setOpen(true);
    else if(sender->getId() == m_menuOpenPlaylist.getId()) m_fileDialogOpenPlaylist.setOpen(true);
    else if(sender->getId() == m_menuQuit.getId()) m_window.close();
    else if(sender->getId() == m_menuSettingsReset.getId()) resetDock();
    else if(sender->getId() == m_menuSettingsPreferences.getId()) m_preferences.setOpen(true);
    else if(sender->getId() == m_menuViewPlaylist.getId()) m_formManager.toggleOpened(FormType::Playlist);
    else if(sender->getId() == m_menuViewAudioPlayer.getId()) m_formManager.toggleOpened(FormType::AudioPlayer);
    else if(sender->getId() == m_menuViewFiles.getId()) m_formManager.toggleOpened(FormType::Files);
    else if(sender->getId() == m_menuViewSystemlog.getId()) m_formManager.toggleOpened(FormType::SystemLog);
    else if(sender->getId() == m_menuToolsExport.getId()) openExportPopup();
    else if(sender->getId() == m_menuHelpAbout.getId()) m_about.setOpen(true);
}

void ebox::ProgramManager::openExportPopup()
{
    AudioPlayerForm *audioPlayer = m_formManager.getAudioPlayerForm();
    EmuStream * stream = audioPlayer->getCurrentStream();
    if(stream != nullptr)
    {
        m_fileExporter.setExportInfo(fs::path(stream->getFilename()), stream->getTrack(), audioPlayer->getTempo());
        m_fileExporter.transferVoiceStates(stream->getVoices());
        m_fileExporter.setOpen(true);
    }
    else
        SystemLog::get()->addError("No stream data found in player. You must open a track to be able to export it.");
}

void ebox::ProgramManager::onFileChosen(const fs::path& path)//(const std::string &path)
{
	fs::path currentPath = path;//fs::path(path);
    m_formManager.getFilelistForm()->loadFile(currentPath);
    if(!m_firstRun)
    {
		m_iniFile.setLastOpenedFolder(currentPath.parent_path());//.u8string());
        m_iniFile.setLastOpenedFile(currentPath);
        m_iniFile.setLastItemIsFolder(false);
        m_iniFile.write();
    }
}

void ebox::ProgramManager::onFolderChosen(const fs::path& path)//(const std::string &path)
{
	fs::path currentPath = path;//fs::path(path);
    m_formManager.getFilelistForm()->loadAllFilesInFolder(currentPath);
    if(!m_firstRun)
    {
		m_iniFile.setLastOpenedFolder(currentPath); //currentPath.u8string());
        m_iniFile.setLastItemIsFolder(true);
        m_iniFile.write();
    }
}

void ebox::ProgramManager::onSavePlaylist(const fs::path& path)//(const std::string &path)
{
	PlaylistFile file{ path }; //{fs::path(path)};

    json data = m_formManager.getPlaylistForm()->getAsJson();
    file.setName(data["name"].get<std::string>());
    json files = data["files"];
    int i = 0;
    for(auto const &item : files)
    {
        file.add(fs::path(item["path"].get<std::string>()), item["name"].get<std::string>(), item["track_no"].get<int>());
        ++i;
    }
    file.write();
    //TODO: 30.07.2019 - Check why this was ambigiously defined (fmt)
    SystemLog::get()->addSuccess(fmt::format("Wrote playlist with {0} items to path: {1}", i, path.u8string()));
}

void ebox::ProgramManager::onOpenPlaylist(const fs::path& path)//(const std::string &path)
{
	PlaylistFile file{ path }; //{fs::path(path)};
    file.load();
    m_formManager.getPlaylistForm()->createByFile(file);
    //TODO: 30.07.2019 - Check why this was ambigiously defined (fmt)
    SystemLog::get()->addSuccess(fmt::format("Loaded playlist with {0} items from path: {1}", file.getPlaylistData().size(), path.u8string()));
}

void ebox::ProgramManager::registerCallbacks()

{
    m_menuOpenFolder.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuOpenFile.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuSavePlaylist.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuOpenPlaylist.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuQuit.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuSettingsReset.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuSettingsPreferences.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewAudioPlayer.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewFiles.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewPlaylist.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewSystemlog.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuToolsExport.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuHelpAbout.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));

    m_fileDialogFile.registerOnFileChosenCallback(std::bind(&ProgramManager::onFileChosen, this, std::placeholders::_1));
    m_fileDialogFolder.registerOnFileChosenCallback(std::bind(&ProgramManager::onFolderChosen, this, std::placeholders::_1));
    m_fileDialogSavePlaylist.registerOnFileChosenCallback(std::bind(&ProgramManager::onSavePlaylist, this, std::placeholders::_1));
    m_fileDialogOpenPlaylist.registerOnFileChosenCallback(std::bind(&ProgramManager::onOpenPlaylist, this, std::placeholders::_1));

    m_preferences.registerOnChangedCallback(std::bind(&ProgramManager::onChangedPreferences, this, std::placeholders::_1));
}

void ebox::ProgramManager::updateViewMenu()
{
    m_menuViewSystemlog.setIsSelected(m_formManager.isOpened(FormType::SystemLog));
    m_menuViewAudioPlayer.setIsSelected(m_formManager.isOpened(FormType::AudioPlayer));
    m_menuViewPlaylist.setIsSelected(m_formManager.isOpened(FormType::Playlist));
    m_menuViewFiles.setIsSelected(m_formManager.isOpened(FormType::Files));
}

void ebox::ProgramManager::onChangedPreferences(PreferencesPopup *sender)
{
    applyIniFileToProgram();
}

void ebox::ProgramManager::applyIniFileToProgram()
{
    m_fileDialogFile.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_fileDialogFolder.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_fileDialogSavePlaylist.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_fileDialogOpenPlaylist.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_preferences.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_about.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    m_fileExporter.setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
    SystemLog::get()->setScaleFactor(m_iniFile.getFontManager()->getFontSizeFactor());
}
