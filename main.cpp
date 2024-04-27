#include <iostream>
using namespace std;
#include "user.h"

int main() {
    std::cout << "Tere tulemast virtuaalsesse raamatukokku!\n";
    User currentUser;

    while (true) {
        std::cout << "\nValikud:\n";
        std::cout << "1. Logi sisse\n";
        std::cout << "2. Loo uus kasutaja\n";
        std::cout << "3. Välju\n";

        int choice;
        std::cout << "\nPalun vali tegevus (1-3): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                currentUser.login();
                break;
            case 2:
                currentUser.createUser();
                break;
            case 3:
                cout << "Täname kasutamast virtuaalset raamatukogu. Head aega!\n";
                return 0;
            default:
                cout << "Vigane valik. Palun vali uuesti.\n";
        }
        return 0;
    }


}