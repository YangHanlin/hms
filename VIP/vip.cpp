// vip.cpp

#include "vip.h"
#include "../HMS.h"

#include <string>
#include <vector>
#include <ostream>
#include <iomanip>
#include <algorithm>

using std::string;
using std::vector;
using std::ostream;
using std::setw;
using std::setfill;
using std::left;
using std::right;
using std::sort;

vector<VIP> vips;

VIP::VIP(int _VIPCard, const string &_ID, const string &_Name, const string &_phoneNumber, int _score)
    : VIPCard(_VIPCard), ID(_ID), Name(_Name), phoneNumber(_phoneNumber), score(_score) {}

bool operator<(const VIP &lhs, const VIP &rhs) {
	return lhs.VIPCard < rhs.VIPCard;
}

ostream &operator<<(ostream &os, const VIP &rhs) {
    os << right << setfill('0')
	   << setw(6) << rhs.VIPCard << "  "
	   << left << setfill(' ')
       << setw(18) << rhs.ID << "  "
	   << setw(10) << rhs.Name << "  "
       << setw(11) << rhs.phoneNumber << "  "
       << setw(5) << rhs.score;
    return os;
}

bool initVIPArray() {
    vips.clear();
	string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "vipdata.conf";
	ifstream vipFileIn(currentPath.c_str());
	if (!vipFileIn)
		return false;
	int tmpVIPCard = 0, tmpScore = 0;
    string tmpID, tmpName, tmpPhoneNumber;
    while (vipFileIn >> tmpVIPCard >> tmpID >> tmpName >> tmpPhoneNumber >> tmpScore)
        vips.push_back(VIP(tmpVIPCard, tmpID, tmpName, tmpPhoneNumber, tmpScore));
	bool vipFileInSuccess = !(vipFileIn.fail() && !vipFileIn.eof());
	vipFileIn.close();
	if (vipFileInSuccess)
		sort(vips.begin(), vips.end());
	return vipFileInSuccess;
}

bool updateVIPArray() {
    string currentPath = _pgmptr;
	currentPath = currentPath.substr(0, currentPath.find_last_of('\\') + 1) + "vipdata.conf";
	ofstream vipFileOut(currentPath.c_str());
	if (!vipFileOut)
		return false;
	for (vector<VIP>::size_type i = 0; i < vips.size(); ++i)
		vipFileOut << vips[i] << endl;
	bool vipFileOutSuccess = !vipFileOut.fail();
	vipFileOut.close();
	return vipFileOutSuccess;
}