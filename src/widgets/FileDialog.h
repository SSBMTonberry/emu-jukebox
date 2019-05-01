//
// Created by robin on 20.01.19.
//

#ifndef EMU_JUKEBOX_FILEDIALOG_H
#define EMU_JUKEBOX_FILEDIALOG_H

#include "../../EmuJukeboxConfig.h"

#if MSVC
#include <filesystem>
    namespace fs = std::filesystem;
#elif MINGW
#if __MINGW64_VERSION_MAJOR > 6
#include <filesystem>
namespace fs = std::filesystem;
#else
#include <experimental/filesystem>
        namespace fs = std::experimental::filesystem;
#endif
#elif APPLE
#include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
#if __GNUC__ < 8 //GCC major version less than 8
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
        namespace fs = std::filesystem;
#endif
#endif

#include "../gui/forms/Popup.h"
#include "../gui/controls/ImageButton.h"
#include "FileTable.h"
#include "../../content/files_mapper.h"
#include <map>
#include "../gui/forms/MessagePopup.h"
#include "../gui/controls/Combobox.h"
#include <SFML/Window/VideoMode.hpp>

using namespace std;
using namespace ebox;
namespace fm = files_mapper;

namespace ebox
{
    typedef std::function<void(fs::path)> func_path; //OnFileChosen, for instance
    typedef std::function<void(void)> func_void; //OnCancel(), for instance

    enum class DialogType : unsigned
    {
            OpenDirectory = 0,
            SaveDirectory = 1,
            OpenFile = 2,
            SaveFile = 3
    };

    enum class FileTypeMode : unsigned
    {
            None = 0,
            EmuFiles = 1,
            Sprites = 2,
            Folder = 3,
            EmuPlaylists = 4,
            SoundFiles = 5
    };

    class FileDialog : public ebox::Popup
    {
        public:
            static const int MAX_FILE_PATH_LENGTH = 512;

            FileDialog(const DialogType &dialogType, std::string id, std::string title, std::string imguiId = "");

            FileDialog(const DialogType &dialogType, const sf::Vector2<int> &position, const sf::Vector2<int> &size,
                       std::string id, std::string title, std::string imguiId = "");

            void assignEnvironmentMap(unordered_map<string, string> *env);
            void assignDefaults();

            //bool draw() override;
            void handleEvents() override;

            void setFileTypes(const ebox::FileTypeMode &mode);
            void setFilename(const std::string &filename);
            void setUseFileIcons(bool useFileIcons);

            void registerOnFileChosenCallback(const func_path &cb);
            void registerOnCancelCallback(const func_void &cb);

            const fs::path &getPath() const;
            const fs::path &getChosenFile() const;
            bool useFileIcons();

            void setPath(const fs::path &path);

            void setScaleFactor(float scaleFactor) override;

        protected:
            void update();
            void initializePopups();
            void handleFileChosen();

            bool customDraw() override;

            //void getHomeEnvironmentVariable();
            std::string getOkBtnText() const;

            unordered_map<string, string> *m_environmentMap = nullptr;

            FileTable m_fileTable {"filetable", "Filetable!"};

            ebox::Group m_upperGroup {"upper_group", "upper_group"};
            ebox::Group m_midGroup {"middle_group", "middle_group"};
            ebox::Group m_bottomGroup {"bottom_group", "bottom_group"};

            ebox::Child m_upperLeftChild {"upper_left_child", "upper_left_child"}; //Must be reinitialized
            ebox::Child m_upperMiddleChild {"upper_middle_child", "upper_middle_child"};
            ebox::Child m_upperRightChild {"upper_right_child", "upper_right_child"};
            ebox::Child m_midRightChild {"mid_right_child", "mid_right_child"};
            ebox::Child m_bottomchildleft {"bottom_child_left", "bottom_child_left"};
            ebox::Child m_bottomchildmid {"bottom_child_mid", "bottom_child_mid"};
            ebox::Child m_bottomchildright {"bottom_child_right", "bottom_child_right"};

            ebox::Label m_upperLabel {"upper_label", "", "Path: "};
            ebox::Textbox m_filepathtext {"filepathtext", "filepath", 0};//MAX_FILE_PATH_LENGTH};
            ebox::ImageButton m_refreshbtn {"refresh_img", files_mapper::gui::actions::_REFRESH_PNG, files_mapper::gui::actions::_REFRESH_PNG_SIZE};
            ebox::Label m_filenameLabel {"file_name_lbl", "", "File name: "};
            ebox::Label m_filetypeLabel {"file_type_lbl", "", "File type: "};
            ebox::Textbox m_filenametext {"file_name_text", "File name text", 0};//50};
            ebox::Combobox m_fileTypeCombo {"file_type_combo", "File type combo"}; //dropdown
            ebox::Button m_okBtn {"ok_btn", "Unset", {10, 10}};
            ebox::Button m_cancelBtn {"cancel_btn", "Cancel", {10, 10}};

            void onMessageResponse(const Button *btn, const MessagePopupResponse &response);
            void onOpen() override;

            void initialize(const std::optional<sf::Vector2<int>> &position = std::nullopt, const std::optional<sf::Vector2<int>> &size = std::nullopt);
            void createLayout();
            std::string getEnv(const std::string_view &id);

            DialogType m_dialogType = DialogType::SaveFile;
            fs::path m_path;
            fs::path m_chosenFile;

            MessagePopup m_msgPopup {"msg_popup_file_exists", "File already exists!", MessagePopupType::YesNo, "1"}; //Since the file dialog has the ###0, this one must have another (using: ###1)
            MessagePopup m_msgPopupNoFileChosen {"msg_popup_no_file_chosen", "No file chosen!", MessagePopupType::Ok, "2"};
            MessagePopup m_msgPopupFileDoesNotExist {"msg_popup_file_does_not_exist", "File does not exist!", MessagePopupType::Ok, "3"};

            vector<func_path> m_callbackOnFileChosen;
            vector<func_void> m_callbackOnClose;

            unordered_map<std::string, std::string> m_filetypeFilter; //first: the text displayed in dropdown of file type, second: the file extension
    };
}


#endif //EMU_JUKEBOX_FILEDIALOG_H
