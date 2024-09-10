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

/// @brief �������� � ��������� ��������� ���������
/// @param adapterName �������� ����������
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
        cerr << "������ ���������/���������� ����������: " << adapterName << endl;
        cerr << "������: " << result << endl;
    }
}

void DisableBluetooth() {
    // ��������� Bluetooth ����� PowerShell
    system("powershell -Command \"Get-PnpDevice -FriendlyName Bluetooth | Enable-PnpDevice -Confirm:$false\"");
    cout << "Bluetooth ��������." << endl;

    // ����� 3 �������
    this_thread::sleep_for(chrono::seconds(3));

    // �������� Bluetooth ����� PowerShell
    system("powershell -Command \"Get-Device -Class Bluetooth | Enable-PnpDevice -Confirm:$false\"");
    cout << "Bluetooth �������." << endl;
}



int main() {

    // ��������� Wi-Fi
    controllerNetworkAdapter("������������ ����", 0);
    controllerNetworkAdapter("Ethernet", 0);
    Sleep(3000);
    controllerNetworkAdapter("������������ ����", 1);
    controllerNetworkAdapter("Ethernet", 1);


    DisableBluetooth();

    // cout << output << endl;
    while(1){
    }
    return 0;
}