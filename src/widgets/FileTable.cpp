//
// Created by robin on 20.01.19.
//

#include "FileTable.h"

ebox::FileTable::FileTable(const string &id, const string &label, bool useFileIcons) : DataTable(id, label), m_useFileIcons {useFileIcons}
{
    create();
}

void ebox::FileTable::create()
{
    initializeFilemap();
    initializeImgFilemap();
    addColumn("filename", "Filename");
    addColumn("size", "Size");
    addColumn("type", "Type");
    addColumn("modified", "Modified");
}

void ebox::FileTable::listFilesByDirectory(const fs::path &path,const fs::path &parentDirectory)
{
    if(fs::exists(path) && fs::is_directory(path))
    {
        m_rows.clear();
        m_lastOpenedPath = path;
        m_pathMap.clear();
        m_pathToOpen = "";
        m_parentDirectory = parentDirectory;
        m_selectedRow = std::nullopt;
        m_callPathOpening = false;

        //Add parent directory
        if(fs::exists(parentDirectory) && fs::is_directory(parentDirectory))
        {
            DataRow *row = newRow();

            /*auto timeEntry = fs::last_write_time(parentDirectory);
            time_t cftime = chrono::system_clock::to_time_t(timeEntry);

            std::string timefmt = fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));*/

            row->setValue("filename", "..");
            //auto imgData = getFileIcon("directory");
            //row->setImage("filename", imgData.first, imgData.second);
            auto icon = getImgFileIcon("directory");
            row->setImageRef("filename", icon);

            row->setValue("type", "parent directory");
            row->setValue("modified", ""); //timefmt); //std::asctime(std::localtime(&cftime)));
            m_pathMap[generatePathId(*row)] = parentDirectory;
        }

        for (const auto &entry : fs::directory_iterator(path))
        {
            auto filename = entry.path().filename();
            auto extension = entry.path().extension();

            if (fs::is_directory(entry.status()))
            {
                DataRow *row = newRow();

                #if MSVC
                    fs::file_time_type timeEntry = fs::last_write_time(entry);
                    //time_t cftime = chrono::system_clock::to_time_t(timeEntry);
                    std::string timefmt = "<not supported by MSVC>"; //fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
                #elif APPLE
                auto timeEntry = fs::last_write_time(entry);
                //time_t cftime = chrono::system_clock::to_time_t(timeEntry);
                std::string timefmt = "<not supported by Clang!>";//fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
                #else
                    auto timeEntry = fs::last_write_time(entry);
                    time_t cftime = chrono::system_clock::to_time_t(timeEntry);
                    std::string timefmt = fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
                #endif
                row->setValue("filename", filename.u8string());
                //auto imgData = getFileIcon("directory");
                //row->setImage("filename", imgData.first, imgData.second);
                auto icon = getImgFileIcon("directory");
                row->setImageRef("filename", icon);
                row->setValue("type", "directory");
                row->setValue("modified", timefmt); //std::asctime(std::localtime(&cftime)));
                m_pathMap[generatePathId(*row)] = entry.path();
            }
            else if (fs::is_regular_file(entry.status()))
            {
                if(m_fileFilter == "*.*" || m_fileFilter == extension)
                {
                    auto err = std::error_code{};
                    auto filesize = fs::file_size(entry, err);

#if MSVC
                    fs::file_time_type timeEntry = fs::last_write_time(entry);
                    //time_t cftime = chrono::system_clock::to_time_t(timeEntry);
                    std::string timefmt = "<not supported by MSVC>"; //fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
#elif APPLE
                    auto timeEntry = fs::last_write_time(entry);
                    //time_t cftime = chrono::system_clock::to_time_t(timeEntry);
                    std::string timefmt = "<not supported by Clang!>";//fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
#else
                    auto timeEntry = fs::last_write_time(entry);
                    time_t cftime = chrono::system_clock::to_time_t(timeEntry);
                    std::string timefmt = fmt::format("{0:%Y.%m.%d %H:%M:%S}", *std::localtime(&cftime));
#endif


                    DataRow *row = newRow();
                    row->setValue("filename", filename.string());

                    if(m_useFileIcons)
                    {
                        auto icon = getImgFileIcon(extension.string());
                        row->setImageRef("filename", icon);
                        //auto imgData = getFileIcon(extension.string());
                        //row->setImage("filename", imgData.first, imgData.second);
                    }

                    row->setValue("type", extension.string());
                    row->setValue("size", fmt::format("{0}", filesize));
                    row->setValue("modified", timefmt); //std::asctime(std::localtime(&cftime)));

                    m_pathMap[generatePathId(*row)] = entry.path();
                }
            }
            else
            {
                if(m_fileFilter == "*.*" || m_fileFilter == extension)
                {

                    DataRow *row = newRow();
                    row->setValue("filename", filename.string());

                    if(m_useFileIcons)
                    {
                        auto icon = getImgFileIcon(extension.string());
                        row->setImageRef("filename", icon);
                        //auto imgData = getFileIcon(extension.string());
                        //row->setImage("filename", imgData.first, imgData.second);
                    }
                    row->setValue("type", extension.string());
                    row->setValue("size", "0");
                    row->setValue("modified", "???");

                    m_pathMap[generatePathId(*row)] = entry.path().string();
                }
            }
        }
    }
    sort();
}

void ebox::FileTable::initializeFilemap()
{
    m_fileMap[".as"] = {fm::gui::filetypes::_ACTIONSCRIPT_PNG, fm::gui::filetypes::_ACTIONSCRIPT_PNG_SIZE};
    m_fileMap[".avi"] = {fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_fileMap[".c"] = {fm::gui::filetypes::_C_PNG, fm::gui::filetypes::_C_PNG_SIZE};
    m_fileMap[".cpp"] = {fm::gui::filetypes::_CPP_PNG, fm::gui::filetypes::_CPP_PNG_SIZE};
    m_fileMap[".csv"] = {fm::gui::filetypes::_CSV_PNG, fm::gui::filetypes::_CSV_PNG_SIZE};
    m_fileMap[".flv"] = {fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_fileMap[".gif"] = {fm::gui::filetypes::_IMAGE_PNG, fm::gui::filetypes::_IMAGE_PNG_SIZE};
    m_fileMap[".h"] = {fm::gui::filetypes::_HH_PNG, fm::gui::filetypes::_HH_PNG_SIZE};
    m_fileMap[".hpp"] = {fm::gui::filetypes::_HH_PNG, fm::gui::filetypes::_HH_PNG_SIZE};
    m_fileMap[".html"] = {fm::gui::filetypes::_HTML_PNG, fm::gui::filetypes::_HTML_PNG_SIZE};
    m_fileMap[".js"] = {fm::gui::filetypes::_JS_PNG, fm::gui::filetypes::_JS_PNG_SIZE};
    m_fileMap[".json"] = {fm::gui::filetypes::_JSON_PNG, fm::gui::filetypes::_JSON_PNG_SIZE};
    m_fileMap[".jpg"] = {fm::gui::filetypes::_IMAGE_PNG, fm::gui::filetypes::_IMAGE_PNG_SIZE};
    m_fileMap[".lua"] = {fm::gui::filetypes::_LUA_PNG, fm::gui::filetypes::_LUA_PNG_SIZE};
    m_fileMap[".log"] = {fm::gui::filetypes::_LOG_PNG, fm::gui::filetypes::_LOG_PNG_SIZE};
    m_fileMap[".mov"] = {fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_fileMap[".mp3"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".mp4"] = {fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_fileMap[".mpeg"] = {fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_fileMap[".ogg"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".pdf"] = {fm::gui::filetypes::_PDF_PNG, fm::gui::filetypes::_PDF_PNG_SIZE};
    m_fileMap[".ebox"] = {fm::gui::misc::_APPLICATION_PNG, fm::gui::misc::_APPLICATION_PNG_SIZE};
    m_fileMap[".png"] = {fm::gui::filetypes::_IMAGE_PNG, fm::gui::filetypes::_IMAGE_PNG_SIZE};
    m_fileMap[".sh"] = {fm::gui::filetypes::_SHELL_PNG, fm::gui::filetypes::_SHELL_PNG_SIZE};
    m_fileMap[".txt"] = {fm::gui::filetypes::_TEXT_PNG, fm::gui::filetypes::_TEXT_PNG_SIZE};
    m_fileMap[".wav"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".wmv"] = {fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_fileMap[".xml"] = {fm::gui::filetypes::_XML_PNG, fm::gui::filetypes::_XML_PNG_SIZE};
    m_fileMap[".ay"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".gbs"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".gym"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".hes"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".kss"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".nsf"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".nsfe"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".sap"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".spc"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_fileMap[".vgm"] = {fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    //Non
    m_fileMap["default"] = {fm::gui::filetypes::_BLANK_PNG, fm::gui::filetypes::_BLANK_PNG_SIZE};
    m_fileMap["directory"] = {fm::gui::folders::blue::_FOLDER_CLOSED_PNG, fm::gui::folders::blue::_FOLDER_CLOSED_PNG_SIZE};
}

void ebox::FileTable::initializeImgFilemap()
{
    m_imgFileMap[".as"] = {".as", fm::gui::filetypes::_ACTIONSCRIPT_PNG, fm::gui::filetypes::_ACTIONSCRIPT_PNG_SIZE};
    m_imgFileMap[".avi"] = {".avi", fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_imgFileMap[".c"] = {".c", fm::gui::filetypes::_C_PNG, fm::gui::filetypes::_C_PNG_SIZE};
    m_imgFileMap[".cpp"] = {".cpp", fm::gui::filetypes::_CPP_PNG, fm::gui::filetypes::_CPP_PNG_SIZE};
    m_imgFileMap[".csv"] = {".csv", fm::gui::filetypes::_CSV_PNG, fm::gui::filetypes::_CSV_PNG_SIZE};
    m_imgFileMap[".flv"] = {".flv", fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_imgFileMap[".gif"] = {".gif", fm::gui::filetypes::_IMAGE_PNG, fm::gui::filetypes::_IMAGE_PNG_SIZE};
    m_imgFileMap[".h"] = {".h", fm::gui::filetypes::_HH_PNG, fm::gui::filetypes::_HH_PNG_SIZE};
    m_imgFileMap[".hpp"] = {".hpp", fm::gui::filetypes::_HH_PNG, fm::gui::filetypes::_HH_PNG_SIZE};
    m_imgFileMap[".html"] = {".html", fm::gui::filetypes::_HTML_PNG, fm::gui::filetypes::_HTML_PNG_SIZE};
    m_imgFileMap[".js"] = {".js", fm::gui::filetypes::_JS_PNG, fm::gui::filetypes::_JS_PNG_SIZE};
    m_imgFileMap[".json"] = {".json", fm::gui::filetypes::_JSON_PNG, fm::gui::filetypes::_JSON_PNG_SIZE};
    m_imgFileMap[".jpg"] = {".jpg", fm::gui::filetypes::_IMAGE_PNG, fm::gui::filetypes::_IMAGE_PNG_SIZE};
    m_imgFileMap[".lua"] = {".lua", fm::gui::filetypes::_LUA_PNG, fm::gui::filetypes::_LUA_PNG_SIZE};
    m_imgFileMap[".log"] = {".log", fm::gui::filetypes::_LOG_PNG, fm::gui::filetypes::_LOG_PNG_SIZE};
    m_imgFileMap[".mov"] = {".mov", fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_imgFileMap[".mp3"] = {".mp3", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".mp4"] = {".mp4", fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_imgFileMap[".mpeg"] = {".mpeg", fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_imgFileMap[".ogg"] = {".ogg", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".pdf"] = {".pdf", fm::gui::filetypes::_PDF_PNG, fm::gui::filetypes::_PDF_PNG_SIZE};
    m_imgFileMap[".ebox"] = {".ebox", fm::gui::misc::_APPLICATION_PNG, fm::gui::misc::_APPLICATION_PNG_SIZE};
    m_imgFileMap[".png"] = {".png", fm::gui::filetypes::_IMAGE_PNG, fm::gui::filetypes::_IMAGE_PNG_SIZE};
    m_imgFileMap[".sh"] = {".sh", fm::gui::filetypes::_SHELL_PNG, fm::gui::filetypes::_SHELL_PNG_SIZE};
    m_imgFileMap[".txt"] = {".txt", fm::gui::filetypes::_TEXT_PNG, fm::gui::filetypes::_TEXT_PNG_SIZE};
    m_imgFileMap[".wav"] = {".wav", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".wmv"] = {".wmv", fm::gui::filetypes::_VIDEO_PNG, fm::gui::filetypes::_VIDEO_PNG_SIZE};
    m_imgFileMap[".xml"] = {".xml", fm::gui::filetypes::_XML_PNG, fm::gui::filetypes::_XML_PNG_SIZE};
    m_imgFileMap[".ay"] = {".ay", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".gbs"] = {".gbs", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".gym"] = {".gym", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".hes"] = {".hes", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".kss"] = {".kss", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".nsf"] = {".nsf", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".nsfe"] = {".nsfe", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".sap"] = {".sap", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".spc"] = {".spc", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".vgm"] = {".vgm", fm::gui::filetypes::_AUDIO_PNG, fm::gui::filetypes::_AUDIO_PNG_SIZE};
    m_imgFileMap[".epl"] = {".epl", fm::gui::actions::_QUICKLIST_PNG, fm::gui::actions::_QUICKLIST_PNG_SIZE};
    //Non
    m_imgFileMap["default"] = {"default", fm::gui::filetypes::_BLANK_PNG, fm::gui::filetypes::_BLANK_PNG_SIZE};
    m_imgFileMap["directory"] = {"directory", fm::gui::folders::blue::_FOLDER_CLOSED_PNG, fm::gui::folders::blue::_FOLDER_CLOSED_PNG_SIZE};
}

pair<const unsigned char *, size_t> ebox::FileTable::getFileIcon(const string &key)
{
    if(m_fileMap.count(key) > 0)
        return m_fileMap[key];
    else
        return m_fileMap["default"];
}

ebox::Image *ebox::FileTable::getImgFileIcon(const string &key)
{
    if(m_imgFileMap.count(key) > 0)
        return &m_imgFileMap[key];
    else
        return nullptr;
}


void ebox::FileTable::onHeaderColumnClicked(const string &id)
{
    if(id == "filename" || id == "type")
    {
        sort(id, m_sortDesc);
        m_sortDesc = !m_sortDesc;
    }
    else if(id == "size")
    {
        sortAsInt(id, m_sortDesc);
        m_sortDesc = !m_sortDesc;
    }
    else if(id == "modified")
    {
        sort(id, m_sortDesc);
        m_sortDesc = !m_sortDesc;
    }

    m_previousSortAction = {id, !m_sortDesc};
}

void ebox::FileTable::sort(const string &columnName, bool sortDesc)
{
    std::sort(m_rows.begin(), m_rows.end(), [&columnName, &sortDesc](DataRow const &a, DataRow const &b) -> bool
    {
        //Sort directories for themselves. Always appears on top
        if(a["type"] == "parent directory")
            return true;
        else if(b["type"] == "parent directory")
            return false;
        else if(a["type"] == "directory" && b["type"] != "directory")
            return true; //a < b
        else if(b["type"] == "directory" && a["type"] != "directory")
            return false; // a > b

        return lexicographical_compare(
                begin(a[columnName]), end(a[columnName]),
                begin(b[columnName]), end(b[columnName]),
                [&sortDesc](const char& char1, const char& char2) {
                    return (sortDesc) ? (tolower(char1) > tolower(char2)) : (tolower(char1) < tolower(char2));
                }
        );
    });
}

void ebox::FileTable::sortAsInt(const string &columnName, bool sortDesc)
{
    std::sort(m_rows.begin(), m_rows.end(), [&columnName, &sortDesc](DataRow const &a, DataRow const &b) -> bool
    {
        //Sort directories for themselves. Always appears on top
        if(a["type"] == "parent directory")
            return true;
        else if(b["type"] == "parent directory")
            return false;
        else if(a["type"] == "directory" && b["type"] != "directory")
            return true; //a < b
        else if(b["type"] == "directory" && a["type"] != "directory")
            return false; // a > b

        int num_a = (a[columnName].size() == 0) ? 0 : stoi(a[columnName]);
        int num_b = (b[columnName].size() == 0) ? 0 : stoi(b[columnName]);

        return (sortDesc) ? (num_a > num_b) : (num_a < num_b);
    });
}

/*!
 * Will perform default or previous sort action
 */
void ebox::FileTable::sort()
{
    sort(m_previousSortAction.first, m_previousSortAction.second);
}

void ebox::FileTable::onRowDoubleClicked(DataRow *row)
{
    size_t size = m_pathMap.size();
    std::string path = m_pathMap[generatePathId(*row)].string();
    if(m_pathMap.count(generatePathId(*row)) > 0)
    {
        m_pathToOpen = m_pathMap[generatePathId(*row)];
        m_callPathOpening = true;
    }
    //Be careful to edit values of selectables on the way. It somewhat makes them unclickable after a while.
    //if(row->isDoubleClicked())
    //    row->setValue("type", "Double boy");
}

const fs::path &ebox::FileTable::getPathToOpen() const
{
    std::string str = m_pathToOpen.string();
    return m_pathToOpen;
}

const std::string ebox::FileTable::generatePathId(const DataRow &row) const
{
    return fmt::format("{0}_{1}", row["filename"], row["type"]);
}

bool ebox::FileTable::canCallPathOpening() const
{
    return m_callPathOpening;
}

void ebox::FileTable::resetPathOpeningCall()
{
    m_callPathOpening = false;
}

const fs::path &ebox::FileTable::getLastOpenedPath() const
{
    return m_lastOpenedPath;
}

void ebox::FileTable::onRowMarked(DataRow *row)
{
    fs::path path = m_pathMap[generatePathId(*row)];
    m_selectedFile = (fs::is_regular_file(path)) ? path.filename().string() : "";
    m_callRowChangeEvent = true;
}

bool ebox::FileTable::canCallRowChangeEvent() const
{
    return m_callRowChangeEvent;
}

void ebox::FileTable::resetRowChangeCall()
{
    m_callRowChangeEvent = false;
}

const string &ebox::FileTable::getSelectedFile() const
{
    return m_selectedFile;
}

void ebox::FileTable::setFileFilter(const std::string &filter)
{
    m_fileFilter = filter;
    listFilesByDirectory(m_lastOpenedPath, m_parentDirectory);
}

const string &ebox::FileTable::getFileFilter() const
{
    return m_fileFilter;
}

bool ebox::FileTable::useFileIcons() const
{
    return m_useFileIcons;
}

void ebox::FileTable::setUseFileIcons(bool useFileIcons)
{
    m_useFileIcons = useFileIcons;
}