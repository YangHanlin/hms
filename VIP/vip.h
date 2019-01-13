// vip.h

#ifndef VIP_H
#define VIP_H

#include <string>
#include <vector>
#include <ostream>

class VIP {
    friend bool updateVIPArray();
    friend int checkDeleteVIP(Form &src);
    friend int checkNewVIP(Form &src);
    friend int filterVIPInfo(Form &src);
    friend struct AdminActions;
    friend struct ServerActions;
    friend void initModifyVIPActionScreen(Form &actionScreen, int vipIndex);
    friend bool operator<(const VIP &lhs, const VIP &rhs);
    friend int customerInfoQuery(Form &src);
    friend std::ostream &operator<<(std::ostream &os, const VIP &rhs);
public:
    VIP(int _VIPCard = 999999,
        const std::string &_ID = "340000200000000000",
        const std::string &_Name = "ÎÞÃûÊÏ",
        const std::string &_phoneNumber = "19999999999",
        int _score = 0);
private:
    int VIPCard;
    std::string ID;
    std::string Name;
    std::string phoneNumber;
    int score;
};

extern std::vector<VIP> vips;

bool initVIPArray();
bool updateVIPArray();
bool operator<(const VIP &lhs, const VIP &rhs);
std::ostream &operator<<(ostream &os, const VIP &rhs);

#endif
