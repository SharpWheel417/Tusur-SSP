#include <iostream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>


using namespace std;





string executeCommand(const string& command) {
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return "Ошибка при выполнении команды";
    }

    string output;
    char buffer[255];

    while (fgets(buffer, 255, pipe) != NULL) {
        output += buffer;
    }

    pclose(pipe);
    return output;
}


vector<string> executeInterfaceName(const string& str) {
    istringstream iss(str);
    string line;

    vector<string> list;

    // Пропускаем первые две строки
    getline(iss, line);
    getline(iss, line);

    while (getline(iss, line)) {
        // Разделяем строку на части по пробелам
        istringstream lineIss(line);
        string part;

        // Пропускаем первые три части
        for (int i = 0; i < 3; i++) {
            getline(lineIss, part, ' ');
        }

        // Выводим четвертую часть (Interface Name)
        getline(lineIss, part);
        list.push_back(part);
    }

    return list;
}


void disableNetworkAdapter(const string& adapterName) {
    string command = "netsh interface set interface \"" + adapterName + "\" admin=disable";
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Ошибка при отключении адаптера: " << adapterName << endl;
        cerr << "Ошибка: " << result << endl;
    }
}

int main() {
    string command = "netsh interface show interface"; // пример команды
    string output = executeCommand(command);
    vector<string> interfaceNames = executeInterfaceName(output);
    for (auto &&interface : interfaceNames)
    {
        disableNetworkAdapter(interface);
    }

    cout << output << endl;
    return 0;
}











void enableNetworkAdapter(const string& adapterName) {
    string command = "netsh interface set interface \"" + adapterName + "\" admin=enable";
    int result = system(command.c_str());
    if (result != 0) {
        cerr << "Error enabling adapter: " << adapterName << " (return code: " << result << ")" << endl;
    }
}

// int main() {
//     // Disable adapters
//     disableNetworkAdapter("Беспроводная сеть");
//     disableNetworkAdapter("Wi-Fi");
//     disableNetworkAdapter("Bluetooth Network Connection");

//     cout << "Network adapters have been disabled." << endl;

//     this_thread::sleep_for(chrono::seconds(3));

//     // Enable adapters
//     enableNetworkAdapter("Ethernet");
//     enableNetworkAdapter("Wi-Fi");
//     enableNetworkAdapter("Bluetooth Network Connection");

//     return 0;
// }