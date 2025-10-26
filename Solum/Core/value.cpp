#include "pch.h"
#include "value.h"
using namespace std;
using namespace solum;

Value::Value(const vector<int>& initData)
	: SolumObj("Value"), data(initData) {
}

Value::Value(const string& bitstringData)
	: SolumObj("Value") {

	string bitstring = bitstringData;

	if (bitstring.empty()) {
		bitstring = "00000000";
	}
	else if (bitstring.size() % 8) {
		bitstring = string(8 - (bitstring.size() % 8), bitstringData[0]) + bitstring;
	}

	for (int i = 0; i < bitstring.size() / 8; ++i) {
		unsigned char byte = 0;
		for (int j = 0; j < 8; ++j) {
			byte <<= 1;
			if (bitstring[i * 8 + j] == '1') {
				byte |= 1;
			}
		}
		data.push_back(static_cast<int>(byte));
	}
}

vector<int> Value::getData() const {
	return data;
}

string Value::toBitstring() const {
	string bitstring;
	for (int byte : data) {
		for (int i = 7; i >= 0; --i) {
			bitstring += ((byte >> i) & 1) ? '1' : '0';
		}
	}
	return bitstring;
}

string Value::asStyledString() const {
	string styledString;
	styledString += toBitstring();
	styledString += " (0x";
	for (int byte : data) {
		char buffer[3];
		sprintf_s(buffer, "%02X", byte & 0xFF);
		styledString += buffer;
	}
	styledString += ")";
	return styledString;
}