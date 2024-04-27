#include <iostream>
using namespace std;
#include "user.h"

int main() {

    cout << "Tere tulemast virtuaalsesse raamatukokku!\n";
    User currentUser;

    while (true) {

        cout << "\nValikud:\n";

        cout << "1. Logi sisse\n";

        cout << "2. Loo uus kasutaja\n";

        cout << "3. Välju\n";

        int choice;

        cout << "\nPalun vali tegevus (1-3): ";

        cin >> choice;

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