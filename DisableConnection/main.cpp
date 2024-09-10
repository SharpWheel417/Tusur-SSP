#include <iostream>
#include <cstdlib>
#include <cstring>
#include <chrono>
#include <thread>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <SetupAPI.h>
#include <cfgmgr32.h>
#include <devguid.h> // GUID_DEVCLASS_BLUETOOTH

#pragma comment(lib, "Setupapi.lib")


// Sleep
#include "windows.h"
#include <setupapi.h>
#pragma comment(lib, "setupapi.lib")

using namespace std;

/// @brief Включает и выключает введенный интерфейс
/// @param adapterName Название интерфейса
/// @param enable 1 - enable, 0 - disable
void controllerNetworkAdapter(const string& adapterName, bool enable) {
    string command;
    int result;

    if (enable){
        command = "netsh interface set interface \"" + adapterName + "\" enable";
    } else{
    command = "netsh interface set interface \"" + adapterName + "\" disable";
    }
    result = system(command.c_str());
    if (result != 0) {
        cerr << "Ошибка включения/выключения интерфейса: " << adapterName << endl;
        cerr << "Ошибка: " << result << endl;
    }
}

void DisableBluetooth() {
    // Отключить Bluetooth через PowerShell
    system("powershell -Command \"Get-PnpDevice -FriendlyName Bluetooth | Enable-PnpDevice -Confirm:$false\"");
    cout << "Bluetooth отключен." << endl;

    // Ждать 3 секунды
    this_thread::sleep_for(chrono::seconds(3));

    // Включить Bluetooth через PowerShell
    system("powershell -Command \"Get-Device -Class Bluetooth | Enable-PnpDevice -Confirm:$false\"");
    cout << "Bluetooth включен." << endl;
}



int main() {

    // выключаем Wi-Fi
    controllerNetworkAdapter("Беспроводная сеть", 0);
    controllerNetworkAdapter("Ethernet", 0);
    Sleep(3000);
    controllerNetworkAdapter("Беспроводная сеть", 1);
    controllerNetworkAdapter("Ethernet", 1);


    DisableBluetooth();

    // cout << output << endl;
    while(1){
    }
    return 0;
}