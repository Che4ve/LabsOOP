// М80-204Б-22 Чесноков В.Д. | Вариант 5
#include <iostream>
#include "include/timecalc.h"

int main() {
    int hour, minute;
    std::string period;
    char colon; // Для разделителя времени ':'
    std::cout << "Enter time in a 12-hour format: ";
    fflush(stdout);
    // Чтение пользовательского ввода
    if (!(std::cin >> hour >> colon >> minute >> period) || colon != ':') {
        // Некорректный формат строки
        std::cerr << "Invalid input" << std::endl;
    }

    // Преобразование и вывод результатов
    std::cout << convertTo24HourFormat(hour, minute, period) << std::endl; // Выведет "0830"

    return 0;
}