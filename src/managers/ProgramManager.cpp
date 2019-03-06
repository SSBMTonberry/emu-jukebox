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

    m_events.initialize(&m_window);
    m_formManager.initialize(&m_window, &m_events);
    m_formManager.showImguiDemoWindow(false);
    createMenu();
    registerCallbacks();
    m_fileDialogFile.assignEnvironmentMap(&m_environmentMap);
    m_fileDialogFile.assignDefaults();
    m_fileDialogFile.setUseFileIcons(true);
    
    m_fileDialogFolder.assignEnvironmentMap(&m_environmentMap);
    m_fileDialogFolder.assignDefaults();
    m_fileDialogFolder.setFileTypes(FileTypeMode::Folder);
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
    sf::Clock deltaClock;
    while (m_window.isOpen())
    {
        m_window.clear(m_backgroundColor);
        update();
        draw();
        handleActions();

        //if(ImGui::IsKeyPressed(sf::Keyboard::Key::Escape))
        //    m_window.close();

        m_window.display();
    }
}

void ebox::ProgramManager::update()
{
    m_clipboard.update();
    m_events.update();
    m_formManager.update();
    updateViewMenu();
}

void ebox::ProgramManager::handleActions()
{
    m_formManager.handleEvents();
    m_fileDialogFile.handleEvents();
    m_fileDialogFolder.handleEvents();
}

void ebox::ProgramManager::processHotkeys()
{

}

void ebox::ProgramManager::draw()
{
    drawDock();
    m_menu.process();
    m_formManager.draw();
    m_fileDialogFile.draw();
    m_fileDialogFolder.draw();
    ImGui::SFML::Render(m_window);
}

void ProgramManager::drawDock()
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

    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {35, 65, 90, 255});
    ImGuiID dockspace_id = ImGui::GetID(DOCKSPACE_ID.c_str());
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
    ImGui::PopStyleColor();
    ImGui::End();
}

void ProgramManager::createDock()
{
    ImGuiID dockspace_id = ImGui::GetID(DOCKSPACE_ID.c_str());
    ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
    ImGui::DockBuilderAddNode(dockspace_id); //viewport->Size); // Add empty node

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

void ProgramManager::resetDock()
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

    ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {35, 65, 90, 255});
    ImGuiID dockspace_id = ImGui::GetID(DOCKSPACE_ID.c_str());
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), 0);
    ImGui::PopStyleColor();
    ImGui::End();

    SystemLog::get()->addDebug("Layout has been reset.");
}

void ProgramManager::createMenu()
{
    m_menuOpenFolder.setImageRef(&m_openFolderImage);
    m_menuOpenFile.setImageRef(&m_openFileImage);
    m_menuLayoutReset.setImageRef(&m_resetLayoutImage);
    m_menuQuit.setImageRef(&m_imgQuit);

    m_menuFile.addRef(&m_menuOpenFolder);
    m_menuFile.addRef(&m_menuOpenFile);
    m_menuFile.addRef(&m_menuQuit);

    m_menuLayout.addRef(&m_menuLayoutReset);

    m_menuView.addRef(&m_menuViewAudioPlayer);
    m_menuView.addRef(&m_menuViewFiles);
    m_menuView.addRef(&m_menuViewPlaylist);
    m_menuView.addRef(&m_menuViewSystemlog);

    m_menu.addRef(&m_menuFile);
    m_menu.addRef(&m_menuLayout);
    m_menu.addRef(&m_menuView);
}

void ProgramManager::onChosenMenuItem(MenuItem *sender)
{
    if(sender->getId() == m_menuOpenFile.getId()) m_fileDialogFile.setOpen(true);
    else if(sender->getId() == m_menuOpenFolder.getId()) m_fileDialogFolder.setOpen(true);
    else if(sender->getId() == m_menuQuit.getId()) m_window.close();
    else if(sender->getId() == m_menuLayoutReset.getId()) resetDock();
    else if(sender->getId() == m_menuViewPlaylist.getId()) m_formManager.toggleOpened(FormType::Playlist);
    else if(sender->getId() == m_menuViewAudioPlayer.getId()) m_formManager.toggleOpened(FormType::AudioPlayer);
    else if(sender->getId() == m_menuViewFiles.getId()) m_formManager.toggleOpened(FormType::Files);
    else if(sender->getId() == m_menuViewSystemlog.getId()) m_formManager.toggleOpened(FormType::SystemLog);
}

void ProgramManager::onFileChosen(const std::string &path)
{
    fs::path currentPath = fs::path(path);
    m_formManager.getFilelistForm()->loadFile(currentPath);
}

void ProgramManager::onFolderChosen(const std::string &path)
{
    fs::path currentPath = fs::path(path);
    m_formManager.getFilelistForm()->loadAllFilesInFolder(currentPath);
}

void ProgramManager::registerCallbacks()

{
    m_menuOpenFolder.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuOpenFile.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuQuit.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuLayoutReset.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewAudioPlayer.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewFiles.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewPlaylist.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));
    m_menuViewSystemlog.registerOnChosenCallback(std::bind(&ProgramManager::onChosenMenuItem, this, std::placeholders::_1));

    m_fileDialogFile.registerOnFileChosenCallback(std::bind(&ProgramManager::onFileChosen, this, std::placeholders::_1));
    m_fileDialogFolder.registerOnFileChosenCallback(std::bind(&ProgramManager::onFolderChosen, this, std::placeholders::_1));
}

void ProgramManager::updateViewMenu()
{
    m_menuViewSystemlog.setIsSelected(m_formManager.isOpened(FormType::SystemLog));
    m_menuViewAudioPlayer.setIsSelected(m_formManager.isOpened(FormType::AudioPlayer));
    m_menuViewPlaylist.setIsSelected(m_formManager.isOpened(FormType::Playlist));
    m_menuViewFiles.setIsSelected(m_formManager.isOpened(FormType::Files));
}