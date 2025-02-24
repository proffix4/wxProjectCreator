#include <wx/wx.h> // Подключаем wxWidgets

class MyApp : public wxApp // Создаём класс для нашего приложения
{
public:
	// Переопределяем инициализацию
	virtual bool OnInit() {
		// Установить русскую локаль
		setlocale(LC_ALL, "ru_RU.UTF-8");
		wxLocale m_locale;
		m_locale.Init(wxLANGUAGE_RUSSIAN, wxLOCALE_DONT_LOAD_DEFAULT);

#ifdef __WXMSW__ // Определение для Windows
		_setmode(_fileno(stdout), _O_U16TEXT); // Установить Юникод для вывода в консоли Windows
		_setmode(_fileno(stdin), _O_U16TEXT); // Установить Юникод для ввода в консоли Windows
		_setmode(_fileno(stderr), _O_U16TEXT); // Установить Юникод для вывода ошибок в консоли Windows
#endif


		// ВАШ КОД ---------------------------------------------

		wxDateTime now = wxDateTime::Now(); // Получаем текущую дату и время
		wxPuts(wxT("Текущая дата и время: ") + now.Format(wxT("%Y-%m-%d %H:%M:%S")));
		wxPuts(L"Замечательно! Das ist großartig! Wonderful! 精彩的！ رائع!\n");
		wxPrintf(L"Введите имя: ");
		std::wstring fio; // Создать строковую переменную
		std::wcin >> fio; // Считать строку
		wxPuts(L"Привет, " + fio + L"!"); // Вывести строку

		// -----------------------------------------------------


#ifdef __WXMSW__ // Условная компиляция для Windows
		system("pause"); // Пауза для консоли Window
#else // Условная компиляция для Linux
		system("read -p \"Нажмите Enter для продолжения...\" var"); // Пауза для консоли Linux
#endif
		return false; // Завершаем приложение после выполнения
	}
};

wxIMPLEMENT_APP_NO_MAIN(MyApp); // Используем макрос для создания точки входа в приложение

// Точка входа в приложение
int main(int argc, char** argv)
{
	wxEntry(argc, argv); // Запускаем приложение
}
