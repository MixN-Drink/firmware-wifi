#include <WIFI.h>

WIFI::WIFI(Logger *_logger) {
	logger = _logger;
	memset(ssid, 0, SSID_LENGTH);
	memset(password, 0, PASSWORD_LENGTH);
	localIP = IPAddress(AP_IP);
	gateway = IPAddress(192,168,0,1);
	subnet = IPAddress(255,255,255,0);
}
void WIFI::begin(void) {
	uint8_t retries = 0;

	// Setup
	logger->Writeln(F(""));
	logger->Writeln(F("Setting mode WIFI_STA"));
	WiFi.mode(WIFI_STA);
	logger->Write(F("Setting device name to "));
	logger->Writeln(DEVICE_NAME);
	WiFi.hostname(DEVICE_NAME);

	// Get stored credentials
	loadCredentials();

	const char *rSsid = getSSID();
	const char *rPassword = getPassword();

	// Connect
	logger->Write(F("Connecting to "));
	logger->Writeln(rSsid);
	WiFi.config(localIP, gateway, subnet);
	WiFi.begin(rSsid, rPassword);
	while(WiFi.waitForConnectResult() != WL_CONNECTED && retries < MAX_RETRIES) {
		retries++;
		logger->Write(F("Retrying connection ("));
		logger->Write(retries);
		logger->Writeln(F(")..."));

		WiFi.begin(rSsid, rPassword);
		delay(WIFI_RETRY_DELAY);
	}
	// If not connected then create AP
	if (!WiFi.isConnected()) {
		logger->Writeln(F("Failed to connect! Creating AP..."));
		IPAddress apip(192,168,0,100);
		IPAddress apgw(0,0,0,0);
		IPAddress apsn(255,255,255,0);
		
		/*bool configApplied = WiFi.softAPConfig(apip, apgw, apsn);
		if(!configApplied){
			logger->Writeln(F("Failed to config AP! Rebooting..."));
			while(1);
		}*/
		bool apCreated = WiFi.softAP(AP_SSID, AP_PASS);
		if(!apCreated){
			logger->Writeln(F("Failed to create AP! Rebooting..."));
			while(1);
		}
		logger->Writeln(F("Created!"));
		logger->Write(F("IP: "));
		logger->Writeln(WiFi.softAPIP().toString().c_str());
	} else {
		logger->Writeln(F("Connected!"));
		logger->Write(F("IP: "));
		logger->Writeln(WiFi.localIP().toString().c_str());
	}	
}

void WIFI::setSSID(const char *_ssid){
	strcpy(ssid, _ssid);
}

void WIFI::setPassword(const char *_password){
	strcpy(password, _password);
}

const char* WIFI::getSSID(){
	return ssid;
}
const char* WIFI::getPassword(){
	return password;
}

void WIFI::storeCredentials(){
	EEPROM.begin(SSID_LENGTH+PASSWORD_LENGTH);
	EEPROM.put(SSID_ADDRESS_OFFSET, ssid);
	EEPROM.put(PASSWORD_ADDRESS_OFFSET, password);
	EEPROM.end();
}
void WIFI::loadCredentials(){
	EEPROM.begin(SSID_LENGTH+PASSWORD_LENGTH);
	EEPROM.get(SSID_ADDRESS_OFFSET, ssid);
	EEPROM.get(PASSWORD_ADDRESS_OFFSET, password);
	EEPROM.end();
}