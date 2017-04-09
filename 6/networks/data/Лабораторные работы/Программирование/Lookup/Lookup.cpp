#include <iostream>
#include <winsock2.h>
#include <string>

using namespace std;

int main() {
	
	WSADATA data;

	
	if (WSAStartup(MAKEWORD(2, 2), &data) == 0) {
	
		//Task 1

		cout << "Task1 : search information about host by hostname and host ip:  " << endl;
		
		const int length = 255;
		char name[length];

		if (gethostname(name, length) == 0)
			cout << endl
				 << "Localhost name: " << name << endl << endl;
		else
			cout << "Can't get localhost name" << endl << endl;
		
		string address;
		cout << "Enter host name/address: ";
		cin >> address;	

		HOSTENT* host;
		
		ULONG addr = inet_addr(address.c_str());

		if (addr != INADDR_NONE) {					

			host = gethostbyaddr((char*)&addr, sizeof(ULONG), AF_INET);
		}
		else {
			host = gethostbyname(address.c_str());
		}

		if (host != NULL) {
			cout << "Host name: " << host->h_name << endl;
			int i = 0;
			while (host->h_aliases[i] != NULL) {
				cout << "Alias name: " << host->h_aliases[i] << endl;
				i++;
			}

			i = 0;

			while (host->h_addr_list[i] != NULL) {
				cout << inet_ntoa(*(in_addr*)host->h_addr_list[i])<<endl;
				i++;
			}
		}
		else {
			cerr << "No information about host" << endl;
		}


		cout << endl << "_________________________________________________________" << endl << endl;



	}

		WSACleanup();			

	return 0;
}

