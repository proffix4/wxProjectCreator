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
#include <wx/timer.h>      // Таймер для анимации текста в статусной строке
#include "tsnsoft.xpm"     // Подключение XPM-изображения для иконки и картинки
#include "wxwidgets.xpm"   // Подключение XPM-изображения для иконки и картинки
#include "dialogblocks.xpm"
#include "rpcpp.xpm"
#include "visualstudio.xpm"

// Константа для имени конфигурационного файла
const wxString CONFIG_FILE_NAME = L"wxProjectCreator.ini";

// Класс ProjectCreator является основным окном приложения и наследуется от wxFrame
class ProjectCreator : public wxFrame {
public:
    // Конструктор окна ProjectCreator
    ProjectCreator()
        : wxFrame(nullptr, wxID_ANY, L"Создатель нового проекта с wxWidgets (ver.5)", wxDefaultPosition, wxSize(500, 325)),
          timer(this) // Инициализация таймера
    {
        SetIcon(wxIcon(tsnsoft_xpm)); // Установка иконки окна
        SetMinSize(GetSize()); // Фиксация размера окна
        SetMaxSize(GetSize()); // Фиксация размера окна
        SetWindowStyle(wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX); // Убрать кнопку "распахнуть на весь экран"

        Centre(); // Центрирование окна на экране

        // --- Создание статусной строки ---
        CreateStatusBar(); // Создание статусной строки
        originalText = L"✬    Талипов С.Н.    ✬    г. Павлодар, 2025 г.    ✬ https://github.com/tsnsoft    ";
        scrollingText = originalText; // Копируем текст для анимации
        SetStatusText(scrollingText); // Устанавливаем текст в статусную строку

        // Запуск таймера с интервалом 150 мс
        Bind(wxEVT_TIMER, &ProjectCreator::OnTimer, this); // Привязка события таймера к функции
        timer.Start(150); // Запуск таймера

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
        templateChoice->Append(L"DialogBlocks");    // индекс 0
        templateChoice->Append(L"RedPanda-CPP");    // индекс 1
        templateChoice->Append(L"Visual Studio");   // индекс 2

        templateChoice->Bind(wxEVT_CHOICE, &ProjectCreator::OnTemplateChoice, this);
        templateSizer->Add(templateChoice, 1, wxALL | wxEXPAND, 5);
        panelSizer->Add(templateSizer, 0, wxEXPAND);

        // --- Чекбокс для выбора визуальной программы ---
        visualCheckBox = new wxCheckBox(m_panel, wxID_ANY, L"Визуальная программа");
        panelSizer->Add(visualCheckBox, 0, wxALL | wxALIGN_LEFT, 5);

        // --- Строка для ввода пути к wxWidgets ---
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

        // --- Отображение картинки (из файла tsnsoft.xpm) под кнопкой ---
        wxStaticBitmap* imageBitmap = new wxStaticBitmap(m_panel, wxID_ANY, wxBitmap(wxwidgets_xpm));
        panelSizer->Add(imageBitmap, 0, wxALL | wxALIGN_CENTER, 10);

        // *** ДОБАВЛЕНО: Сохраняем указатель на imageBitmap в m_imageBitmap, чтобы менять картинку ***
        m_imageBitmap = imageBitmap;

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
    wxPanel* m_panel;                  // Основная панель
    wxTextCtrl* projectNameCtrl;       // Элемент для ввода имени проекта
    wxChoice* templateChoice;          // Элемент для выбора типа шаблона
    wxStaticText* wxWidgetsLabel;      // Метка для пути к wxWidgets
    wxTextCtrl* wxWidgetsPathCtrl;     // Элемент для ввода пути к wxWidgets
    wxCheckBox* visualCheckBox;        // Элемент для выбора визуальной программы
    wxTimer timer;                     // Таймер для бегущей строки
    wxString originalText;             // Оригинальный текст
    wxString scrollingText;            // Текущий текст для анимации

    // Храним указатель на картинку, чтобы менять её при смене шаблона
    wxStaticBitmap* m_imageBitmap = nullptr;

    // Прототипы функций для копирования директории и замены содержимого файла
    void CopyDirectory(const wxString& source, const wxString& destination);
    void ReplaceInFile(const wxString& filePath, const wxString& projectName, wxString wxWidgetsPath);

    // Функция обработки таймера для бегущей строки
    void OnTimer(wxTimerEvent&) {
        if (!scrollingText.IsEmpty()) {
            scrollingText = scrollingText.Mid(1) + scrollingText[0];
            SetStatusText(scrollingText);
        }
    }

    // Обработчик изменения выбора шаблона
    void OnTemplateChoice(wxCommandEvent&)
    {
        int sel = templateChoice->GetSelection();
        if (sel == 1 || sel == 2) {
            wxWidgetsLabel->Show();
            wxWidgetsPathCtrl->Show();
        }
        else {
            wxWidgetsLabel->Hide();
            wxWidgetsPathCtrl->Hide();
        }

        // Меняем картинку в зависимости от выбора пользователя
        if (m_imageBitmap) {
            if (sel == 0) {
                // DialogBlocks
                m_imageBitmap->SetBitmap(wxBitmap(dialogblocks_xpm));
            }
            else if (sel == 1) {
                // RedPanda-CPP
                m_imageBitmap->SetBitmap(wxBitmap(rpcpp_xpm));
            }
            else if (sel == 2) {
                // Visual Studio
                m_imageBitmap->SetBitmap(wxBitmap(visualstudio_xpm));
            }
        }

        m_panel->Layout();
    }

    // --- Функция загрузки настроек приложения из файла рядом с exe ---
    void LoadSettings()
    {
        wxString exePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
        wxString configPath = exePath + wxFILE_SEP_PATH + CONFIG_FILE_NAME;
        wxFileConfig config("ProjectCreator", wxEmptyString, configPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);

        wxString projectName, wxWidgetsPath;
        int templateIndex;
        if (config.Read(L"ProjectName", &projectName)) {
            projectNameCtrl->SetValue(projectName);
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
        long visualProgram = 0;
        if (config.Read(L"VisualProgram", &visualProgram))
            visualCheckBox->SetValue(visualProgram == 1);
    }

    // --- Функция сохранения настроек приложения в файл рядом с exe ---
    void SaveSettings()
    {
        wxString exePath = wxFileName(wxStandardPaths::Get().GetExecutablePath()).GetPath();
        wxString configPath = exePath + wxFILE_SEP_PATH + CONFIG_FILE_NAME;
        wxFileConfig config("ProjectCreator", wxEmptyString, configPath, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
        config.Write(L"ProjectName", projectNameCtrl->GetValue());
        config.Write(L"TemplateType", templateChoice->GetSelection());
        config.Write(L"WxWidgetsPath", wxWidgetsPathCtrl->GetValue());
        config.Write(L"VisualProgram", visualCheckBox->GetValue() ? 1 : 0);
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

        wxString templatePath;
        if (templateType == L"DialogBlocks") {
            if (visualCheckBox->GetValue())
                templatePath = basePath + L"/templates/dialogblocks_visual";
            else
                templatePath = basePath + L"/templates/dialogblocks_console";
        }
        else if (templateType == L"RedPanda-CPP") {
            if (visualCheckBox->GetValue())
                templatePath = basePath + L"/templates/redpanda_visual";
            else
                templatePath = basePath + L"/templates/redpanda_console";
        }
        else if (templateType == L"Visual Studio") {
            if (visualCheckBox->GetValue())
                templatePath = basePath + L"/templates/vs_visual";
            else
                templatePath = basePath + L"/templates/vs_console";
        }

        wxString commonPath = basePath + L"/templates/common";
        SaveSettings();

        CopyDirectory(templatePath, projectPath);
        CopyDirectory(commonPath, projectPath);

        wxString wxWidgetsPath = wxWidgetsPathCtrl->GetValue();

        if (templateType == L"RedPanda-CPP") {
            wxString devFilePath = projectPath + L"/redpanda-cpp.dev";
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
        else if (templateType == L"Visual Studio") {
            wxString slnFilePath = projectPath + L"/vs2022.sln";
            wxString newSlnFilePath = projectPath + L"/" + projectName + L".sln";
            if (wxFileExists(slnFilePath)) {
                if (!wxRenameFile(slnFilePath, newSlnFilePath)) {
                    wxMessageBox(L"Не удалось переименовать sln файл", L"Ошибка", wxOK | wxICON_ERROR);
                    return;
                }
                ReplaceInFile(newSlnFilePath, projectName, wxWidgetsPath);
            }

            wxString vcxFilePath = projectPath + L"/vs2022.vcxproj";
            wxString newVcxFilePath = projectPath + L"/" + projectName + L".vcxproj";
            if (wxFileExists(vcxFilePath)) {
                if (!wxRenameFile(vcxFilePath, newVcxFilePath)) {
                    wxMessageBox(L"Не удалось переименовать vcxproj файл", L"Ошибка", wxOK | wxICON_ERROR);
                    return;
                }
                ReplaceInFile(newVcxFilePath, projectName, wxWidgetsPath);
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
        if (!wxWidgetsPath.EndsWith("/") && !wxWidgetsPath.EndsWith("\\"))
            wxWidgetsPath.Append("/");
    }

    wxTextFile file;
    if (!file.Open(filePath)) {
        wxMessageBox(L"Не удалось открыть файл для чтения", L"Ошибка", wxOK | wxICON_ERROR);
        return;
    }

    wxString content;
    for (content = file.GetFirstLine(); !file.Eof(); content += file.GetNextLine() + "\n") { }
    file.Close();

    content.Replace("RPCPP_wx_App", projectName);
    content.Replace("DialogBlocks_wx_App", projectName);
    content.Replace("vs2022", projectName);

    if (!wxWidgetsPath.IsEmpty()) {
        content.Replace("D:/Development/RedPanda-CPP/wxWidgets/",   wxWidgetsPath);
        content.Replace("D:\\Development\\RedPanda-CPP\\wxWidgets\\", wxWidgetsPath);
        content.Replace("D:\\Development\\RedPanda-CPP\\wxWidgets/",  wxWidgetsPath);
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
