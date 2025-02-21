// Подключение необходимых заголовочных файлов wxWidgets
#include <wx/wx.h>         // Основной заголовок wxWidgets
#include <wx/dir.h>        // Работа с директориями
#include <wx/filedlg.h>    // Диалоговые окна для выбора файлов/директорий
#include <wx/textctrl.h>   // Текстовые поля
#include <wx/choice.h>     // Элемент выбора (combo box)
#include <wx/button.h>     // Кнопки
#include <wx/stattext.h>   // Статические текстовые элементы (метки)
#include <wx/stdpaths.h>   // Стандартные пути (например, путь к исполняемому файлу)
#include <wx/filename.h>   // Работа с именами файлов и путями
#include <wx/msgdlg.h>     // Диалоговые окна сообщений (например, ошибки, предупреждения)
#include <wx/config.h>     // Работа с конфигурационными файлами или реестром
#include <wx/fileconf.h>   // Заголовок для использования wxFileConfig
#include <wx/filefn.h>     // Функции для работы с файлами (копирование, удаление и т.д.)
#include <wx/textfile.h>   // Работа с текстовыми файлами
#include "tsnsoft.xpm"     // Подключение XPM-изображения для иконки окна

// Константа для имени конфигурационного файла
const wxString CONFIG_FILE_NAME = L"wxProjectCreator.ini";

// Класс ProjectCreator является основным окном приложения и наследуется от wxFrame
class ProjectCreator : public wxFrame {
public:
    // Конструктор окна ProjectCreator
    ProjectCreator()
        : wxFrame(nullptr, wxID_ANY, L"Создание консольного wx-проекта (TSN, v2025.2)", wxDefaultPosition, wxSize(500, 200))
    {
        SetIcon(wxIcon(tsnsoft_xpm));
        Centre();

        // --- Создание основной панели ---
        m_panel = new wxPanel(this, wxID_ANY);
        wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
        m_panel->SetSizer(panelSizer);

        // --- Строка для ввода имени проекта ---
        wxBoxSizer* projectNameSizer = new wxBoxSizer(wxHORIZONTAL);
        projectNameSizer->Add(new wxStaticText(m_panel, wxID_ANY, L"Имя проекта:"), 
                                0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        projectNameCtrl = new wxTextCtrl(m_panel, wxID_ANY);
        projectNameSizer->Add(projectNameCtrl, 1, wxALL | wxEXPAND, 5);
        panelSizer->Add(projectNameSizer, 0, wxEXPAND);

        // --- Строка для выбора типа шаблона ---
        wxBoxSizer* templateSizer = new wxBoxSizer(wxHORIZONTAL);
        templateSizer->Add(new wxStaticText(m_panel, wxID_ANY, L"Тип шаблона:"), 
                             0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        templateChoice = new wxChoice(m_panel, wxID_ANY);
        templateChoice->Append(L"DialogBlocks");
        templateChoice->Append(L"RedPanda-CPP");
        templateChoice->Bind(wxEVT_CHOICE, &ProjectCreator::OnTemplateChoice, this);
        templateSizer->Add(templateChoice, 1, wxALL | wxEXPAND, 5);
        panelSizer->Add(templateSizer, 0, wxEXPAND);

        // --- Строка для ввода пути к wxWidgets (показывается только при выборе "RedPanda-CPP") ---
        wxBoxSizer* wxWidgetsPathSizer = new wxBoxSizer(wxHORIZONTAL);
        wxWidgetsLabel = new wxStaticText(m_panel, wxID_ANY, L"Путь к wxWidgets:");
        wxWidgetsPathSizer->Add(wxWidgetsLabel, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
        wxWidgetsPathCtrl = new wxTextCtrl(m_panel, wxID_ANY);
        wxWidgetsPathSizer->Add(wxWidgetsPathCtrl, 1, wxALL | wxEXPAND, 5);
        panelSizer->Add(wxWidgetsPathSizer, 0, wxEXPAND);

        // --- Кнопка для создания проекта ---
        wxButton* createButton = new wxButton(m_panel, wxID_ANY, L"Сделать проект");
        createButton->Bind(wxEVT_BUTTON, &ProjectCreator::OnCreateProject, this);
        panelSizer->Add(createButton, 0, wxALL | wxALIGN_CENTER, 10);

        // --- Загрузка настроек приложения ---
        LoadSettings();
        wxCommandEvent evt;
        OnTemplateChoice(evt);

        // --- Размещение панели на основном окне (фрейме) ---
        wxBoxSizer* frameSizer = new wxBoxSizer(wxVERTICAL);
        frameSizer->Add(m_panel, 1, wxEXPAND);
        SetSizer(frameSizer);

        // --- Фиксация размера окна ---
        SetMinSize(GetSize());
        SetMaxSize(GetSize());
    }

private:
    // Элементы управления
    wxPanel* m_panel;
    wxTextCtrl* projectNameCtrl;
    wxChoice*   templateChoice;
    wxStaticText* wxWidgetsLabel;
    wxTextCtrl* wxWidgetsPathCtrl;

    // Прототипы функций для копирования директории и замены содержимого файла
    void CopyDirectory(const wxString& source, const wxString& destination);
    void ReplaceInFile(const wxString& filePath, const wxString& projectName, wxString wxWidgetsPath);

    // Обработчик изменения выбора шаблона
    void OnTemplateChoice(wxCommandEvent&)
    {
        if (templateChoice->GetSelection() == 1) {
            wxWidgetsLabel->Show();
            wxWidgetsPathCtrl->Show();
        } else {
            wxWidgetsLabel->Hide();
            wxWidgetsPathCtrl->Hide();
        }
        m_panel->Layout();
    }

    // --- Функция загрузки настроек приложения из файла рядом с exe ---
    void LoadSettings()
    {
        // Получаем директорию исполняемого файла
        wxString exePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
        // Формируем полный путь к файлу настроек, используя константу CONFIG_FILE_NAME
        wxString configPath = exePath + wxFILE_SEP_PATH + CONFIG_FILE_NAME;

        // Создаем wxFileConfig, указывая, что файл настроек хранится локально
        wxFileConfig config("ProjectCreator", wxEmptyString, configPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);

        wxString projectName, wxWidgetsPath;
        int templateIndex;
        if (config.Read(L"ProjectName", &projectName)) {
            projectNameCtrl->SetValue(projectName);
            // Отложенный сброс курсора – вызывается после компоновки
            CallAfter([=]() {
                projectNameCtrl->SetInsertionPoint(0);
                projectNameCtrl->SetSelection(0, 0);
            });
        }
        if (config.Read(L"TemplateType", &templateIndex))
            templateChoice->SetSelection(templateIndex);
        if (config.Read(L"WxWidgetsPath", &wxWidgetsPath)) {
            wxWidgetsPathCtrl->SetValue(wxWidgetsPath);
            CallAfter([=]() {
                wxWidgetsPathCtrl->SetInsertionPoint(0);
                projectNameCtrl->SetSelection(0, 0);
            });
        }
    }

    // --- Функция сохранения настроек приложения в файл рядом с exe ---
    void SaveSettings()
    {
        wxString exePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
        // Формируем полный путь к файлу настроек, используя константу CONFIG_FILE_NAME
        wxString configPath = exePath + wxFILE_SEP_PATH + CONFIG_FILE_NAME;

        wxFileConfig config("ProjectCreator", wxEmptyString, configPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
        config.Write(L"ProjectName", projectNameCtrl->GetValue());
        config.Write(L"TemplateType", templateChoice->GetSelection());
        config.Write(L"WxWidgetsPath", wxWidgetsPathCtrl->GetValue());
        config.Flush();
    }

    // Обработчик события нажатия на кнопку "Сделать проект"
    void OnCreateProject(wxCommandEvent& event)
    {
        wxString projectName = projectNameCtrl->GetValue();
        if (projectName.IsEmpty()) {
            wxMessageBox(L"Введите имя проекта", L"Ошибка", wxOK | wxICON_ERROR);
            return;
        }
        wxString templateType = templateChoice->GetStringSelection();
        wxString basePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
        wxString projectPath = basePath + L"/" + projectName;
        if (!wxFileName::Mkdir(projectPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL)) {
            wxMessageBox(L"Не удалось создать директорию проекта", L"Ошибка", wxOK | wxICON_ERROR);
            return;
        }

        wxString templatePath = basePath + L"/templates/" +
            (templateType == L"DialogBlocks" ? L"dialogblocks_console" : L"redpanda_console");
        wxString commonPath = basePath + L"/templates/common";
        SaveSettings();
        CopyDirectory(templatePath, projectPath);
        CopyDirectory(commonPath, projectPath);

        if (templateType == L"RedPanda-CPP") {
            wxString wxWidgetsPath = wxWidgetsPathCtrl->GetValue();
            wxString devFilePath   = projectPath + L"/redpanda-cpp.dev";
            wxString newDevFilePath = projectPath + L"/" + projectName + L".dev";
            if (wxFileExists(devFilePath)) {
                if (!wxRenameFile(devFilePath, newDevFilePath)) {
                    wxMessageBox(L"Не удалось переименовать dev файл", L"Ошибка", wxOK | wxICON_ERROR);
                    return;
                }
                ReplaceInFile(newDevFilePath, projectName, wxWidgetsPath);
            }
        }
        else if (templateType == L"DialogBlocks") {
            wxString pjdFilePath = projectPath + L"/dialogblocks.pjd";
            wxString newPjdFilePath = projectPath + L"/" + projectName + L".pjd";
            if (wxFileExists(pjdFilePath)) {
                if (!wxRenameFile(pjdFilePath, newPjdFilePath)) {
                    wxMessageBox(L"Не удалось переименовать pjd файл", L"Ошибка", wxOK | wxICON_ERROR);
                    return;
                }
                ReplaceInFile(newPjdFilePath, projectName, wxEmptyString);
            }
        }
        wxMessageBox(L"Проект создан", L"Готово", wxOK | wxICON_INFORMATION);
    }
};

// Функция для копирования директории (рекурсивно копирует файлы и поддиректории)
void ProjectCreator::CopyDirectory(const wxString& source, const wxString& destination)
{
    wxDir dir(source);
    if (!dir.IsOpened()) {
        wxMessageBox(L"Не удалось открыть директорию", L"Ошибка", wxOK | wxICON_ERROR);
        return;
    }

    wxString filename;
    bool cont = dir.GetFirst(&filename);
    while (cont) {
        wxString sourcePath = source + "/" + filename;
        wxString destPath = destination + "/" + filename;
        if (wxDirExists(sourcePath)) {
            wxFileName::Mkdir(destPath, wxS_DIR_DEFAULT, wxPATH_MKDIR_FULL);
            CopyDirectory(sourcePath, destPath);
        }
        else if (wxFileExists(sourcePath)) {
            wxCopyFile(sourcePath, destPath);
        }
        cont = dir.GetNext(&filename);
    }
}

// Функция для замены содержимого файла
void ProjectCreator::ReplaceInFile(const wxString& filePath, const wxString& projectName, wxString wxWidgetsPath)
{
    if (!wxWidgetsPath.IsEmpty()) {
        if (!wxWidgetsPath.EndsWith("/") && !wxWidgetsPath.EndsWith("\\")) {
            wxWidgetsPath.Append("/");
        }
    }

    wxTextFile file;
    if (!file.Open(filePath)) {
        wxMessageBox(L"Не удалось открыть файл для чтения", L"Ошибка", wxOK | wxICON_ERROR);
        return;
    }

    wxString content;
    for (content = file.GetFirstLine(); !file.Eof(); content += file.GetNextLine() + "\n")
        ;
    file.Close();

    content.Replace("RPCPP_wx_Console_Hello", projectName);
    content.Replace("DialogBlocksConsoleApp", projectName);

    if (!wxWidgetsPath.IsEmpty()) {
        content.Replace("D:/Development/RedPanda-CPP/wxWidgets/", wxWidgetsPath);
        content.Replace("D:/Development/RedPanda-CPP/wxWidgets",  wxWidgetsPath);
        content.Replace("D:\\Development\\RedPanda-CPP\\wxWidgets\\", wxWidgetsPath);
        content.Replace("D:\\Development\\RedPanda-CPP\\wxWidgets",  wxWidgetsPath);
    }

    file.Clear();
    file.AddLine(content);
    file.Write();
    file.Close();
}

// Основной класс приложения
class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        ProjectCreator* frame = new ProjectCreator();
        frame->Show();
        return true;
    }
};

wxIMPLEMENT_APP_NO_MAIN(MyApp);

// Точка входа в приложение
int main(int argc, char** argv)
{
    wxEntry(argc, argv); // Запускаем приложение
}
