#include <iostream>
#include "Menu.h"
/**
 * Точка входа программы.
 * @return код завершения программы
 */
int main()  {
    try  {
        Menu();
    }  catch(std::exception&)  {
        std::cout << "Something went wrong, try again!\n";
    }

}