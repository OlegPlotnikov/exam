#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

class Employee {
private:
  std::string name;
  int id;
  double salary;

public:
  Employee(std::string n, int i, double s) : name(n), id(i), salary(s) {}

  std::string getName() const { return name; }
  int getId() const { return id; }
  double getSalary() const { return salary; }

  void setSalary(double newSalary) { salary = newSalary; }
};

bool isValidEmployeeData(const std::string &name, int id, double salary) {
  if (name.empty())
    return false;
  if (id <= 0)
    return false;
  if (salary < 0)
    return false;
  return true;
}

void saveToFile(const Employee employees[], int size,
                const std::string &filename) {
  std::ofstream outFile(filename);
  if (!outFile.is_open()) {
    std::cerr << "Не удалось открыть файл для записи: " << filename
              << std::endl;
    return;
  }

  for (int i = 0; i < size; ++i) {
    outFile << employees[i].getId() << " " << employees[i].getName() << " "
            << employees[i].getSalary() << "\n";
  }
  outFile.close();
  std::cout << "Данные успешно сохранены в файл " << filename << std::endl;
}

int main() {
  SetConsoleOutputCP(65001);
  SetConsoleCP(65001);

  std::vector<Employee> employees;
  employees.reserve(5);

  std::cout << "Введите данные для 3 сотрудников." << std::endl;

  for (int i = 0; i < 3; ++i) {
    std::string name;
    int id;
    double salary;

    std::cout << "\nСотрудник №" << (i + 1) << std::endl;

    std::cout << "Введите имя: ";
    std::cin >> std::ws;
    std::getline(std::cin, name);

    std::cout << "Введите ID: ";
    if (!(std::cin >> id)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ошибка ввода ID. Повторите ввод." << std::endl;
      --i;
      continue;
    }

    std::cout << "Введите зарплату: ";
    if (!(std::cin >> salary)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ошибка ввода зарплаты. Повторите ввод." << std::endl;
      --i;
      continue;
    }

    if (isValidEmployeeData(name, id, salary)) {
      employees.emplace_back(name, id, salary);
    } else {
      std::cout << "Некорректные данные! (Имя не пустое, ID > 0, Зарплата >= "
                   "0). Повторите ввод."
                << std::endl;
      --i;
    }
  }

  std::cout << "\nСписок всех сотрудников:" << std::endl;
  for (const auto &emp : employees) {
    std::cout << "ID: " << emp.getId() << ", Name: " << emp.getName()
              << ", Salary: " << emp.getSalary() << std::endl;
  }

  saveToFile(employees.data(), employees.size(), "employees.txt");

  return 0;
}
