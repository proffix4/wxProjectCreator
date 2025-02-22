#include <wx/wx.h>
#include <locale>
#include <codecvt>
#include <iostream>


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "ru_RU.UTF-8"); // Установить русскую локаль для Linux
    wxLocale m_locale; // Создать объект локали для wxWidgets
    m_locale.Init(wxLANGUAGE_RUSSIAN, wxLOCALE_DONT_LOAD_DEFAULT); // Установить локаль для wxWidgets

#ifdef __WXMSW__ // Определение для Windows
    _setmode(_fileno(stdout), _O_U16TEXT); // Установить Юникод для вывода в консоли Windows
    _setmode(_fileno(stdin), _O_U16TEXT); // Установить Юникод для ввода в консоли Windows
    _setmode(_fileno(stderr), _O_U16TEXT); // Установить Юникод для вывода ошибок в консоли Windows
#endif

    wxPuts(L"Замечательно! Das ist großartig! Wonderful! 精彩的！ رائع!\n");
    wxPrintf(L"Введите имя: ");
    
    std::wstring fio; // Создать строковую переменную
    std::wcin >> fio; // Считать строку
    
    wxPuts(L"Привет, " + fio + L"!"); // Вывести строку
    wxPuts(L"Размер строки: " + std::to_wstring(fio.length())); // Вывести размер строки

    for (std::wstring::size_type i = 0; i < fio.length(); i++) {
        wxPuts(L"[" + std::to_wstring(i) + L"]: " + std::wstring(1, fio[i]) + 
               L" (code: " + std::to_wstring(int(fio[i])) + L")");
    }

#ifdef __WXMSW__ // Определение для Windows
    system("pause"); // Приостановить выполнение программы
#else // Определение для Linux
    system("read -p \"Нажмите Enter для продолжения...\" var"); // Приостановить выполнение программы
#endif

    return 0;
}
