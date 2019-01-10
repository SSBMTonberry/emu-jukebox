//
// Created by robin on 18.12.17.
//

#include "GuiManager.h"
#include "Themes/Theme.h"
#include "../../PixelmoundStudio/files/files.h"


ebox::GuiManager::GuiManager()
{

}

ebox::GuiManager::GuiManager(sf::RenderWindow *window, ebox::EventManager *eventManager)
{
    initialize(window, eventManager);
}

void ebox::GuiManager::initialize(sf::RenderWindow *window, ebox::EventManager *eventManager)
{
    ImGui::CreateContext(); //IMGUI 1.60
    m_window = window;
    m_style = &ImGui::GetStyle();
    m_io = &ImGui::GetIO();
    m_eventManager = eventManager;

    ImGui::SFML::Init(*m_window);

    //m_io->ConfigResizeWindowsFromEdges = true;

    //Enable Ctrl+TAB (New in ImGui 1.63)
    m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //Enable docking (New in ImGui 1.66 WIP) - Downloaded 14.10.2018
    m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
}

bool ebox::GuiManager::run(bool callWindowDisplay)
{
    update();
    draw(callWindowDisplay);
    return true;
}

void ebox::GuiManager::update()
{
    m_eventManager->update();
    for(sf::Event &event : m_eventManager->getAllEvents())
    {
        ImGui::SFML::ProcessEvent(event);
        if (event.type == sf::Event::Closed)
        {
            m_window->close();
        }
    }
    ImGui::SFML::Update(*m_window, m_deltaClock.restart());

    //for(auto const & form : m_forms)
    //    form->update();
}

void ebox::GuiManager::draw(bool callWindowDisplay)
{
    for(auto const & form: m_forms)
        form->draw();
    for(auto const & form: m_formRefs)
        form->draw();
    for(auto const &callback : m_callbackOnCustomDraw)
        callback();

    if(m_showImguiDemoWindow)
        ImGui::ShowDemoWindow();

    ImGui::SFML::Render(*m_window);

    if(callWindowDisplay)
        m_window->display();

}

void ebox::GuiManager::addTestForm()
{
    unique_ptr<ebox::Form> form = GuiFactory::CreateForm({0, 0}, {400, 600}, "form1", "Testalini", "0");
    form->setFormFlags(ebox::FormFlags::NoResize | FormFlags::NoTitleBar);

    unique_ptr<ebox::TreeNode> tree1 = GuiFactory::CreateTreeNode("tree1", "My first shit!", ebox::TreeNode::NodeType::CollapsingHeader);
    unique_ptr<ebox::TreeNode> tree2 = GuiFactory::CreateTreeNode("tree2", "Treellooo!", ebox::TreeNode::NodeType::CollapsingHeader);
    unique_ptr<ebox::TreeNode> tree3 = GuiFactory::CreateTreeNode("tree3", "Crapman", ebox::TreeNode::NodeType::CollapsingHeader);
    unique_ptr<ebox::TreeNode> tree4 = GuiFactory::CreateTreeNode("tree_of_shit", "Bajsmais", ebox::TreeNode::NodeType::CollapsingHeader);
    unique_ptr<ebox::TreeNode> tree5 = GuiFactory::CreateTreeNode("table_of_ass", "Taburu", ebox::TreeNode::NodeType::CollapsingHeader);
    unique_ptr<ebox::TreeNode> tree6 = GuiFactory::CreateTreeNode("group_and_child", "Group And Child", ebox::TreeNode::NodeType::CollapsingHeader);
    unique_ptr<ebox::TreeNode> tree7 = GuiFactory::CreateTreeNode("datatablerone", "DataTaburu", ebox::TreeNode::NodeType::CollapsingHeader);

    unique_ptr<ebox::Textbox> textbox = GuiFactory::CreateTextbox("smiesh", "BROLO", 25);
    textbox->createBasicTooltip("Skrellåååååå!");
    textbox->setHasLabel(false);
    //textbox->addTextboxFlag(TextboxFlags::ReadOnly);

    textbox->setColor(sf::Color::Red, sf::Color::Black, sf::Color::Cyan, sf::Color::Blue);
    tree1->add(move(textbox));
    tree1->add(move(GuiFactory::CreateTextbox("besh", "SWAGGINS", 5)));
    unique_ptr<ebox::Label> label = GuiFactory::CreateLabel("label", "SHABBY NABBY", "GRASH!?");
    label->setColor(sf::Color::Red);
    tree1->add(move(label));
    unique_ptr<ebox::Button> button = GuiFactory::CreateButton("butz", "KNAPPERIER", {120, 30});
    unique_ptr<ebox::Button> button2 = GuiFactory::CreateButton("butz2", "KNAPPERIER", {120, 30});
    button->setColor(sf::Color::Red, sf::Color::Cyan, sf::Color::Blue);
    button2->setColor(sf::Color::Cyan, sf::Color::Red, sf::Color::Blue);
    button2->setOnSameLine(true);
    tree1->add(move(button));
    tree1->add(move(button2));
    unique_ptr<ebox::ImageButton> imgButton = GuiFactory::CreateImageButton("imgbutt");
    imgButton->setColor(sf::Color::Yellow, sf::Color::Green, sf::Color::Cyan);

    tree1->add(move(imgButton));

    unique_ptr<ebox::InputInt> inputInt = std::make_unique<ebox::InputInt>("input_int", "InputInt", 0, 100, 1, 10);
    tree1->add(move(inputInt));

    unique_ptr<ebox::Combobox> comboboy = GuiFactory::CreateCombobox("comboboy", "james");
    comboboy->addValueRange({"Shitfuck", "McCrabs", "Assbleed McGonoree", "Jæimz", "Blæim"});
    comboboy->removeValue("Jæimz");
    comboboy->setColor(sf::Color::Red, sf::Color::Blue);
    tree1->add(move(comboboy));

    unique_ptr<ebox::RadioSection> radiosec = GuiFactory::CreateRadioSection("bucket", "radiosecie");
    radiosec->addRadioData(0, "james?");
    radiosec->addRadioData(1, "Hobbs");
    radiosec->addRadioData(2, "Knobbs");
    radiosec->addRadioData(3, "Kamelåså?");
    radiosec->addRadioData(4, "Jimmy Fucker");
    radiosec->addRadioData(5, "Kjell");
    radiosec->addRadioData(6, "Grøt");
    radiosec->addRadioData(7, "Pelle");
    radiosec->addRadioData(8, "Tralle");
    radiosec->setHorizontal(4);
    tree2->add(move(radiosec));
    //form->add(move(radiosec));

    unique_ptr<ebox::Checkbox> checkbox = GuiFactory::CreateCheckbox("checkie", "chack", true);
    tree2->add(move(checkbox));
    //form->add(move(checkbox));

    unique_ptr<ebox::CheckboxSection> checks = GuiFactory::CreateCheckboxSection("checkies", "yay");
    checks->addCheckbox(0, "john", true);
    checks->addCheckbox(1, "bon", false);
    checks->addCheckbox(2, "tron", false);
    checks->addCheckbox(3, "hohn", true);
    checks->addCheckbox(4, "ron", true);
    checks->setVertical();

    tree2->add(move(checks));
    //form->add(move(checks));

    unique_ptr<ebox::Listbox> listbox = GuiFactory::CreateListbox("listieboooy", "Listis", false);
    listbox->addValues({{0, "Johnnyboooy"}, {1, "Jim Cartie"}, {2, "Bon bon John"}, {3, "Shitfuck McDiglets"}});
    tree2->add(move(listbox));
    //form->add(move(listbox));

    unique_ptr<ebox::Selectable> slect = GuiFactory::CreateSelectable("slect", "MÆIT!?", {150, 75});
    tree2->add(move(slect));
    //form->add(move(slect));

    unique_ptr<ebox::SliderInt> sliderint = GuiFactory::CreateSliderInt("slida", "slidie", -50, 100, ebox::SliderInt::SliderIntType::H_One);
    unique_ptr<ebox::SliderInt> sliderint2 = GuiFactory::CreateSliderInt("slida2", "slidie2", -50, 100, ebox::SliderInt::SliderIntType::H_Four);
    sliderint2->setValues({1,2,3,4,5,6}); // 5 and 6 should be ignored
    tree3->add(move(sliderint));
    tree3->add(move(sliderint2));

    unique_ptr<ebox::SliderFloat> sliderfloat = GuiFactory::CreateSliderFloat("slidafloat", "slidie3", 0.f, 500.f, 4, ebox::SliderFloat::SliderFloatType::H_Two);
    unique_ptr<ebox::SliderFloat> sliderfloat2 = GuiFactory::CreateSliderFloat("slidafloat2", "slidie4", 5.f, 10.f, 2, ebox::SliderFloat::SliderFloatType::H_Three);

    tree3->add(move(sliderfloat));
    tree3->add(move(sliderfloat2));

    unique_ptr<ebox::SliderInt> vsliderint = GuiFactory::CreateSliderInt("vslida", "##vertint", 0, 8, ebox::SliderInt::SliderIntType::Vertical, {10, 200});
    vsliderint->setHideNumber(true);

    unique_ptr<ebox::SliderFloat> vsliderfloat = GuiFactory::CreateSliderFloat("vslidafloat", "##vertfloat", 0.f, 5.f, 4, ebox::SliderFloat::SliderFloatType::Vertical, {15, 200});
    vsliderfloat->setOnSameLine(true);
    vsliderfloat->setHideNumber(true);

    unique_ptr<ebox::Image> img = GuiFactory::CreateImage("imgboy");
    img->create(ebox::logo::_ebox_LOGO_PNG, ebox::logo::_ebox_LOGO_PNG_SIZE);
    img->setOnSameLine(true);
    unique_ptr<ebox::Image> img2 = GuiFactory::CreateImage("imgboy2");
    img2->create(ebox::logo::_ebox_LOGO_PNG, ebox::logo::_ebox_LOGO_PNG_SIZE);
    img2->setOnSameLine(true);

    unique_ptr<ebox::ColorPicker> picker1 = GuiFactory::CreateColorPicker("pickerillo1", "picks", ColorPicker::ColorPickerType::ColorEdit3, sf::Color::Red);
    unique_ptr<ebox::ColorPicker> picker2 = GuiFactory::CreateColorPicker("pickerillo2", "pyck", ColorPicker::ColorPickerType::ColorEdit4, sf::Color::Green);

    tree3->add(move(vsliderint));
    tree3->add(move(vsliderfloat));
    tree3->add(move(img));
    tree3->add(move(img2));

    tree4->add(move(picker1));
    tree4->add(move(picker2));

    unique_ptr<ebox::DragInt> dragInt = GuiFactory::CreateDragInt("draggis", "DRA MEG!", 2, 45, 2.5f, DragInt::DragIntSize::Four);
    unique_ptr<ebox::DragFloat> dragFloat = GuiFactory::CreateDragFloat("draggis2", "DRA MEG MER!", 4.f, 250.f, 3, 5.f, DragFloat::DragFloatSize::Three);
    tree4->add(move(dragInt));
    tree4->add(move(dragFloat));

    unique_ptr<ebox::ColorButton> colorbtn = GuiFactory::CreateColorButton("colorbtn1", "Fargefaen", {255, 0, 0, 255});
    unique_ptr<ebox::ColorButton> colorbtn2 = GuiFactory::CreateColorButton("colorbtn2", "Drittfargen", {0, 0, 255, 255});
    unique_ptr<ebox::ColorButton> colorbtn3 = GuiFactory::CreateColorButton("colorbtn3", "BÆSJ!", {0, 0, 0, 255});
    colorbtn2->setOnSameLine(true);
    colorbtn3->setOnSameLine(true);

    tree4->add(move(colorbtn));
    tree4->add(move(colorbtn2));
    tree4->add(move(colorbtn3));

    unique_ptr<ebox::Column> col1 = GuiFactory::CreateColumn("col1", "This column maaate");
    col1->add(GuiFactory::CreateLabel("label_basic", "JAMES!?", "YES, JAMES."));
    col1->add(GuiFactory::CreateTextbox("text_basic", "JAMES!?", 25));

    unique_ptr<ebox::Column> col2 = GuiFactory::CreateColumn("col2", "Other column");
    col2->add(GuiFactory::CreateLabel("label_basic2", "Cream", "Seem"));
    col2->add(GuiFactory::CreateTextbox("text_basic2", "John", 20));

    unique_ptr<ebox::Column> col3 = GuiFactory::CreateColumn("col3", "Even better column");
    col3->add(GuiFactory::CreateLabel("label_basic3", "", "Just showin' the label mate"));

    unique_ptr<ebox::Column> col4 = GuiFactory::CreateColumn("col4", "The bestest");
    col4->add(GuiFactory::CreateButton("el_buttonos", "Knappir", {300, 50}));

    unique_ptr<ebox::Column> col5 = GuiFactory::CreateColumn("col5", "Klonnerier");
    col5->add(GuiFactory::CreateLabel("mkaylab", "Kringles", "Rendeem"));
    col5->add(GuiFactory::CreateTextbox("mkaytext", "Bresk", 40));

    unique_ptr<ebox::Column> col6 = GuiFactory::CreateColumn("col6", "That is collieboy");
    col6->add(GuiFactory::CreateLabel("jamescol", "Brysk", "Jeem"));
    col6->add(GuiFactory::CreateTextbox("jamestext", "Shittalini", 20));

    unique_ptr<ebox::Table> table = GuiFactory::CreateTable("tabbie", "Tableboy");
    unique_ptr<ebox::Row> row = GuiFactory::CreateRow("rowie", "Dat row mate");
    unique_ptr<ebox::Row> row2 = GuiFactory::CreateRow("rowie2", "Another Row to grow");
    unique_ptr<ebox::Row> row3 = GuiFactory::CreateRow("rowie3", "Holy crapfuck");
    row->add(move(col1));
    row->add(move(col2));
    row->add(move(col3));
    row2->add(move(col4));
    row3->add(move(col5));
    row3->add(move(col6));

    table->add(move(row));
    table->add(move(row2));
    table->add(move(row3));

    tree5->add(move(table));

    uptr_child child = GuiFactory::CreateChild("left_child", "kid", {150, 0});
    uptr_listbox listbox2 = GuiFactory::CreateListbox("listkid", "Listarino", false, 30);
    listbox2->addValues({{0, "Johohooo"}, {1, "Brannskader"}, {2, "Drasse"}, {3, "Shit in ass"}, {4, "Boyalini"}});
    listbox2->setHasLabel(false);
    child->add(move(listbox2));

    uptr_group group = GuiFactory::CreateGroup("right_group", "groupalini");
    uptr_child child2 = GuiFactory::CreateChild("right_child", "kid2", {0, -50});
    group->setOnSameLine(true);
    
    unique_ptr<ebox::Listbox> listbox3 = GuiFactory::CreateListbox("listkid2", "Klisterlister", false, 30);
    listbox3->addValues({{0, "Gressløk"}, {1, "Grøt"}, {2, "Fløte"}, {3, "Karsk"}, {4, "Danskebåten"},
                         {5, "Granløk"}, {6, "Kjeppfelle"}, {7, "Dritefest"}, {8, "Knappenål"},
                         {9, "Hummer og kanari"}});
    listbox3->setHasLabel(false);

    uptr_progressbar progresso = GuiFactory::CreateProgressbar("progresso", 0, 100, "james: {0}/{1}", {-1, -1}, 50);
    child2->add(move(listbox3));

    group->add(move(child2));
    group->add(move(progresso));

    tree6->add(move(child));
    tree6->add(move(group));

    uptr_datatable datatable = GuiFactory::CreateDataTable("datatableboy", "El tabello");
    datatable->addColumn("img", "ImgCustom", DataColumnType::Image, 0);
    datatable->addColumn("live", "Live and loaded");
    datatable->addColumn("cargo", "Cargolini", DataColumnType::Textbox, 0);
    datatable->addColumn("lynsj", "Lynsje");
    datatable->addColumn("crønsj", "Crønsj");

    DataRow *newrow1 = datatable->newRow();
    newrow1->setImage("img", files::folders::blue::_FOLDER_OPENED_PNG, files::folders::blue::_FOLDER_OPENED_PNG_SIZE);
    newrow1->setValue("live", "Kreeeem");
    newrow1->setValue("cargo", "Kjør biiil");
    newrow1->setValue("lynsj", "Svosh!");
    newrow1->setValue("crønsj", "Limesvette");

    DataRow *newrow2 = datatable->newRow();
    newrow2->setValues({"James", "Brames", "Chames", "www.shitfuckmcnuggets.com", "Should be ass"});

    //std::string lolle = (*newrow2)["live"];

    DataRow *newrow3 = datatable->newRow();
    newrow3->setValuesWithKey({{"live", "Saftfyrste"}, {"lynsj", "Gretten bæsj"}});
    tree7->add(move(datatable));

    form->add(move(tree1));
    form->add(move(tree2));
    form->add(move(tree3));
    form->add(move(tree4));
    form->add(move(tree5));
    form->add(move(tree6));
    form->add(move(tree7));

    //Menu items
    unique_ptr<ebox::MenuBar> mainboy = GuiFactory::CreateMenuBar("mainboy", true);
    unique_ptr<ebox::MenuItemCollection> file = GuiFactory::CreateMenuItemCollection("subbie1", "File");
    unique_ptr<ebox::MenuItem> fileItem1 = GuiFactory::CreateMenuItem("menuitem1", "Galder");
    unique_ptr<ebox::MenuItem> fileItem2 = GuiFactory::CreateMenuItem("menuitem2", "Rabalder");
    file->add(move(fileItem1));
    file->add(move(fileItem2));

    unique_ptr<ebox::MenuItemCollection> edit = GuiFactory::CreateMenuItemCollection("subbie2", "Edit");
    unique_ptr<ebox::MenuItemCollection> edit2 = GuiFactory::CreateMenuItemCollection("subbie3", "Edit even moooore");
    unique_ptr<ebox::MenuItem> fileItem3 = GuiFactory::CreateMenuItem("menuitem3", "TANK FRANK");
    unique_ptr<ebox::MenuItem> fileItem4 = GuiFactory::CreateMenuItem("menuitem4", "<==JÆIMS HERE!?");
    edit->add(move(fileItem3));
    edit2->add(move(fileItem4));
    edit->add(move(edit2));

    unique_ptr<ebox::MenuItem> lastItem = GuiFactory::CreateMenuItem("getout", "GET OUT!");

    mainboy->add(move(file));
    mainboy->add(move(edit));
    form->add(move(mainboy));

    addForm(move(form));

    /*unique_ptr<ebox::Popup> popup = GuiFactory::CreatePopup("popup_test_id", "PopupModal 1.60", "922");
    unique_ptr<ebox::Combobox> comborillo = GuiFactory::CreateCombobox("combo_test_id", "Combotest");
    //comborillo->setHasLabel(false); //Removed not to make confusion
    comborillo->addValue("Robin's shitty code");
    comborillo->addValue("does not work :(");
    popup->add(move(comborillo));
    popup->setOpen(true);

    addForm(move(popup));*/

    addForm(make_unique<ebox::TextEditorForm>("text_editor", "Code a random", "1"));
    m_showImguiDemoWindow = true;
}

void ebox::GuiManager::addForm(unique_ptr<ebox::Form> form)
{
    m_forms.push_back(move(form));
}

void ebox::GuiManager::addFormReference(ebox::Form *form)
{
    m_formRefs.push_back(form);
}

/*ebox::Form *ebox::GuiManager::getForm(const string &id)
{
    for(const auto & item : m_forms)
    {
        if(item->getId().compare(id) == 0)
        {
            return item.get();
        }
    }

    return nullptr;
}*/

void ebox::GuiManager::setTheme(const ebox::GuiManager::GuiTheme &theme)
{
    switch (theme)
    {
        case GuiTheme::Classic:
            ImGui::StyleColorsClassic();
            break;

        case GuiTheme::Dark:
            ImGui::StyleColorsDark();
            break;

        case GuiTheme::Light:
            ImGui::StyleColorsLight();
            break;

        case GuiTheme::Custom:
            ImGui::ShowStyleEditor();
    }
}

void ebox::GuiManager::setTheme(Theme &theme)
{
    theme.assign();
}

/*!
 * Settings for the gui style.
 *
 * @param setting
 * @param x First parameter. In cases where the setting just needs one value, this is the one that is used.
 * @param y Second parameter, only used for settings that uses two values
 */
void ebox::GuiManager::setSetting(const ebox::GuiSetting &setting, const float &x, const float &y)
{

    switch (setting)
    {
        case GuiSetting::Alpha:
            m_style->Alpha = x;

        case GuiSetting::WindowPadding:
            m_style->WindowPadding = ImVec2(x, y);
            break;

        case GuiSetting::PopupRounding:
            m_style->PopupRounding = x;
            break;

        case GuiSetting::FramePadding:
            m_style->FramePadding = ImVec2(x, y);
            break;

        case GuiSetting::ItemSpacing:
            m_style->ItemSpacing = ImVec2(x, y);
            break;

        case GuiSetting::ItemInnerSpacing:
            m_style->ItemInnerSpacing = ImVec2(x, y);
            break;

        case GuiSetting::TouchExtraPadding:
            m_style->TouchExtraPadding = ImVec2(x, y);
            break;

        case GuiSetting::IndentSpacing:
            m_style->IndentSpacing = x;
            break;

        case GuiSetting::ScrollbarSize:
            m_style->ScrollbarSize = x;
            break;

        case GuiSetting::GrabMinSize:
            m_style->GrabMinSize = x;
            break;

        case GuiSetting::WindowBorderSize:
            m_style->WindowBorderSize = x;
            break;

        case GuiSetting::ChildBorderSize:
            m_style->ChildBorderSize = x;
            break;

        case GuiSetting::PopupBorderSize:
            m_style->PopupBorderSize = x;
            break;

        case GuiSetting::FrameBorderSize:
            m_style->FrameBorderSize = x;
            break;

        case GuiSetting::WindowRounding:
            m_style->WindowRounding = x;
            break;

        case GuiSetting::ChildRounding:
            m_style->ChildRounding = x;
            break;

        case GuiSetting::FrameRounding:
            m_style->FrameRounding = x;
            break;

        case GuiSetting::ScrollbarRounding:
            m_style->ScrollbarRounding = x;
            break;

        case GuiSetting::GrabRounding:
            m_style->GrabRounding = x;
            break;

        case GuiSetting::WindowTitleAlign:
            m_style->WindowTitleAlign = ImVec2(x, y);
            break;

        case GuiSetting::ButtonTextAlign:
            m_style->ButtonTextAlign = ImVec2(x, y);
            break;

        case GuiSetting::TabRounding:
            m_style->TabRounding = x;
    }
}

void ebox::GuiManager::handleEvents()
{
    for(auto const & form: m_forms)
        form->handleEvents();
    for(auto const & form: m_formRefs)
        form->handleEvents();
}

bool ebox::GuiManager::isShowImguiDemoWindow() const
{
    return m_showImguiDemoWindow;
}

void ebox::GuiManager::setShowImguiDemoWindow(bool showImguiDemoWindow)
{
    m_showImguiDemoWindow = showImguiDemoWindow;
}

void ebox::GuiManager::registerOnCustomDrawCallback(const ebox::GuiManager::func_customdraw &cb)
{
    m_callbackOnCustomDraw.emplace_back(cb);
}




