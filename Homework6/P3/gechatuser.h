/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#ifndef _GECHATUSER_H_
#define _GECHATUSER_H_
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class GechatUser {
   public:
    // Assume using namespace std;
    GechatUser();
    GechatUser(std::string username);
    GechatUser(const GechatUser &other);
    ~GechatUser();

    const int numFriends() const;
    void setUsername(std::string username);
    const bool haveFriend(
        std::shared_ptr<GechatUser> user) const;  // return true if user is a friend to *this.
    const bool addFriend(std::shared_ptr<GechatUser>
                             user);  // return false only if user is invalid or already a friend.
    const bool singleDelete(
        std::shared_ptr<GechatUser> user);  // return false only if user is invalid or not a friend.
    const bool singleDelete(
        std::string username);  // return false only if username not found in friends.
    const bool doubleDelete(
        std::shared_ptr<GechatUser> user);  // return false only if user is invalid or not a friend.
    const bool doubleDelete(
        std::string username);  // return false only if username not found in friends.

    const bool operator<(const GechatUser &other) const { return name < other.name; }

    friend std::ostream &operator<<(std::ostream &out, const GechatUser &p) {
        out << p.name << " (friends: " << p.numFriends() << ")";
        return out;
    }

    //
    const int find(const std::string &name) const {
        for (int i = 0; i < (int)d.size(); i++)
            if (d[i]->name == name) return i;
        return d.size();
    }

   private:
    std::vector<std::shared_ptr<GechatUser> > d;
    std::string name;
};

#endif