#pragma once
#include "Rectangle.hpp"
#include <iomanip>
#include <string>
#include <string_view>
#include <conio.h>
#include <unordered_map>
#include <Windows.h>
#include <filesystem>
#include <fstream>

#ifdef max
#undef max
#endif

using Rectd = Rect<double>;
namespace fs = std::filesystem;

// Все переменные
std::unordered_map<std::string, Rectd> vals;

// Выравнивание в выводе
constexpr std::streamsize align = 60;

// Невалидные символы для имен переменных
constexpr std::string_view invalid_name = " 1234567890!@#$%^&*()[]{}/\\|";

// Невалтдные символы для файлов
constexpr std::string_view invalid_file = " \\|/:\"\'*<>?!$.";

/// <summary>
/// Очистка консоли
/// </summary>
void clear_console() {
	system("cls");
}

/// <summary>
/// Функция отображения команд
/// </summary>
size_t check_ask(std::string_view ann, std::vector<std::string_view> command) {
	assert(command.size() <= 9);

	size_t input = 0;
	do {
		std::cout << ann;

		size_t i = 0;

		for (decltype(auto) c : command) {
			std::cout << std::setw(align) << std::left << c << ++i << '\n';
		}

		std::cout << "\n\n";

		input = _getch();
		
		clear_console();

		if (input <= '9' and input >= '1' and input - '1' < command.size()) return input - '0';
		else std::cout << "Неправильный ввод, попробуйте снова\n\n";
		
	} while (true);
}

/// <summary>
/// Отображение всех перменных
/// </summary>
void show_vals() {
	if (vals.empty()) {
		std::cout << "Переменных нет\n";
	}
	else {
		std::cout << std::setw(align) << std::left << "Имя переменной" << "Значение" << "\n\n";

		for (decltype(auto) v : vals) {
			std::cout << std::setw(align) << std::left << v.first << v.second.ToString() << '\n';
		}
	}
	std::cout << '\n';
}

/// <summary>
/// Меню ввода положительного числа
/// </summary>
double get_abs_double(std::string ann) {
	double input = 0;
	do {
		std::cout << ann;

		std::cin >> input;

		clear_console();

		if (!std::cin) {
			if (std::cin.eof()) {
				std::cout << "Fatal error";
				std::exit(0);
			}

			std::cin.clear();

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Неправильный ввод, попробуйте снова.\nВвод должен быть неотрицательным числом с разделителем \'.\'\n\n";
		}
		else if (input < 0) {
			std::cout << "Неправильный ввод, попробуйте снова.\nВвод должен быть неотрицательным числом с разделителем \'.\'\n\n";
		}
		else return input;
	} while (true);
}

/// <summary>
/// Меню ввода числа
/// </summary>
double get_double(std::string_view ann) {
	double input = 0;
	do {
		std::cout << ann;

		std::cin >> input;

		clear_console();

		if (!std::cin) {
			if (std::cin.eof()) {
				std::cout << "Fatal error";
				std::exit(0);
			}

			std::cin.clear();

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Неправильный ввод, попробуйте снова.\nВвод должен быть числом с разделителем \'.\'\n\n";
		}
		else return input;
	} while (true);
}

/// <summary>
/// Меню выбора переменной
/// </summary>
Rectd& choice_rect(std::string_view ann) {
	std::string input;
	
	if (vals.empty()) throw std::runtime_error("Нет переменных");

	do {
		std::cout << ann;

		show_vals();
		
		std::cout << "Введите имя переменной: ";

		std::cin >> input;

		clear_console();

		if (vals.contains(input)) return vals.at(input);
		else std::cout << "Такой переменной нет\n\n";

	} while (true);
}

/// <summary>
/// Меню создания значения переменной
/// </summary>
void create_val_value(std::string name) {
	do {
		switch (check_ask("Имя переменной " + name + "\n\n", {
			"Создать прямоугольник по умолчанию",
			"Создать прямоуольник по точке, высоте и широте",
			"Создать прямоугольник из обьединения двух прямоугольников",
			"Создать прямоугольник из пересечения двух прямоугольников",
			"Назад"
			})) {
		case 1:
			vals.insert({ name, Rectd() });
			return;
		case 2:
			vals.insert({ name, Rectd(get_double("Введите координату X: "), get_double("Введите координату Y: "),
				get_abs_double("Введите ширину: "),get_abs_double("Введите высоту: ")) });
			return;
		case 3:
			if (vals.size() < 2) {
				std::cout << "Слишком мало существующих переменных для обьединения\n\n";
				break;
			}
			else {
				vals.insert({ name, choice_rect("Выберите первый прямоугольник для обьединения: \n").Union(
					choice_rect("Выберите второй прямоугольник для обьединения: \n")) });
				return;
			}
		case 4:
			if (vals.size() < 2) {
				std::cout << "Слишком мало существующих переменных для пересечения\n\n";
				break;
			}
			else {
				vals.insert({ name, choice_rect("Выберите первый прямоугольник для пересечения: \n").Union(
					choice_rect("Выберите второй прямоугольник для пересечения: \n")) });
				return;
			}
		case 5:
			return;
		}
	} while (true);
}

/// <summary>
/// Проверка имени переменной
/// </summary>
bool check_value_name(std::string_view name) {
	return name.find_first_of(invalid_name) == name.npos and !vals.contains(name.data());
}

/// <summary>
/// Меню создания имени переменной
/// </summary>
void create_val_name() {
	do {
		std::cout << "Введите уникальное имя переменной\nСуществующие переменные:\n";
		show_vals();

		std::string name;
		std::cin >> name;
		
		clear_console();

		if (check_value_name(name)) {
			create_val_value(std::move(name));
			return;
		}
		else {
			std::cout << "Неправильный ввод, попробуйте снова\nИмя переменной не должно существовать и не должно иметь символы: "
				<< invalid_name << "\n\n";
		}

	} while (true);
}

/// <summary>
/// Меню манипуляций с переменной
/// </summary>
void manipulate_value() {
	if (vals.empty()) {
		std::cout << "Для начала создайте переменные\n\n";
		return;
	}

	Rectd& r = choice_rect("");
	do {
		switch (check_ask("Выбранный прямоугольник: " + r.ToString() + "\n\n", {
			"Показать площадь",
			"Показать периметр",
			"Задать новую точку Х",
			"Задать новую точку Y",
			"Задать новую высоту",
			"Задать новую ширину",
			"Назад"}))
		{
		case 1:
			std::cout << "Площадь: " << r.Area() << '\n';
			break;
		case 2:
			std::cout << "Периметр: " << r.Perimeter() << '\n';
			break;
		case 3:
			r.origin.x = get_double("Введите новую точку Х: ");
			break;
		case 4:
			r.origin.y = get_double("Введите новую точку Y: ");
			break;
		case 5:
			r.height = get_abs_double("Введите новую высоту: ");
			break;
		case 6:
			r.width = get_abs_double("Введите новую ширину: ");
			break;
		case 7:
			return;
		}
	} while (true);
}

/// <summary>
/// Создание файла
/// </summary>
fs::path create_file() {
	std::string input;
	do {
		std::cout << "Введите имя файла: ";

		std::cin >> input;

		if (input.find_first_of(invalid_file) == input.npos) return input;
		else std::cout << "Некорректное имя файла, попробуйте снова\n\n";
	} while (true);
}

/// <summary>
/// Считывание с файла
/// </summary>
void read_file() {
	std::string input;
	std::cout << "Внимание! При коллизии имен, существующие перменные будут перезаписаны\n";
	std::cout << "Введите имя файла: ";

	std::cin >> input;

	if (!fs::exists(input)) {
		std::cout << "Файл не найден, попробуйте снова\n\n";
		return;
	}
	
	fs::path fn = input;

	std::ifstream fin(fn);

	if (!fin.is_open()) {
		std::cout << "Не удалось открыть файл " << fn << "\n\n";
		return;
	}

	std::string n;
	double x = 0, y = 0, w = 0, h = 0;
	while (!fin.eof() and fin.good()) {
		fin >> n >> x >> y >> w >> h;
		if (vals.contains(n)) vals.at(n) = Rectd(x, y, w, h);
		else vals.insert({ n, Rectd(x,y,w,h) });
	}

	std::cout << "Переменные загружены\n\n";
}

/// <summary>
/// Запись в файл
/// </summary>
void write_file() {
	if (vals.empty()) {
		std::cout << "Нет переменных для сохранения\n\n";
		return;
	}

	fs::path fn = create_file();

	std::ofstream fout(fn, std::ios::app);

	if (!fout.is_open()) {
		std::cout << "Не удалось открыть файл " << fn << "\n\n";
		return;
	}

	for (decltype(auto) v : vals) {
		decltype(auto) r = v.second;
		fout << std::setw(align) << std::left << v.first 
			<< r.origin.x << ' ' << r.origin.y << ' ' << r.width << ' ' << r.height << '\n';
	}

	fout.close();

	std::cout << "Успешно сохранено в файл: " << fn << "\n\n";
}

void delete_val() {
	if (vals.empty()) {
		std::cout << "Нет переменных для удаления\n\n";
		return;
	}
	std::string input;
	do {
		std::cout << "Выберете переменную для удаления\n\n";

		show_vals();

		std::cout << "Введите имя переменной: ";

		std::cin >> input;

		clear_console();

		if (vals.contains(input)) {
			vals.erase(input);
			std::cout << "Переменная удалена\n\n";
			return;
		}
		else std::cout << "Такой переменной нет\n\n";

	} while (true);
}
/// <summary>
/// Главное меню
/// </summary>
void main_menu() {
	setlocale(LC_ALL, "RU-ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	clear_console();
	while (true) {
		try {
			switch (check_ask("", { 
				"Показать существующие переменные",
				"Создать новую переменную", 
				"Удалить переменую",
				"Изменить переменную",
				"Загрузить переменные из файла",
				"Выгрузить переменные в файл",
				"Закончить"})) {
			case 1:
				show_vals();
				break;
			case 2:
				create_val_name();
				break;
			case 3:
				delete_val();
				break;
			case 4:
				manipulate_value();
				break;
			case 5:
				read_file();
				break;
			case 6:
				write_file();
				break;
			case 7:
				return;
			}
		}
		catch (const std::runtime_error& e) {
			std::cout << "Ошибка: " << e.what() << "\n\n";
		}
		catch (...) {
			std::cout << "Ошибка\n\n";
		}
	}
}