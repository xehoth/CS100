/**
 * Copyright (c) 2019, HongtuXu
 * All rights reserved.
 *
 * @author HongtuXu
 * @date 2019-11-17
 */
#include "gechatuser.h"

GechatUser::GechatUser() = default;

GechatUser::GechatUser(std::string username) : name(username) {}

GechatUser::GechatUser(const GechatUser &other) : d(other.d), name(other.name) {}

GechatUser::~GechatUser() {}

const int GechatUser::numFriends() const { return d.size(); }

void GechatUser::setUsername(std::string username) { name = username; }

const bool GechatUser::haveFriend(std::shared_ptr<GechatUser> user) const {
    if (!user) return false;
    return d.begin() + find(user->name) != d.end();
}

const bool GechatUser::addFriend(std::shared_ptr<GechatUser> user) {
    if (!user) return false;
    if (haveFriend(user)) return false;
    d.push_back(user);
    //
    // user->addFriend(std::make_shared<GechatUser>(*this));
    return true;
}

const bool GechatUser::singleDelete(std::shared_ptr<GechatUser> user) {
    if (!user) return false;
    int p = find(user->name);
    if (d.begin() + p == d.end()) return false;
    d.erase(d.begin() + p);
    return true;
}

const bool GechatUser::singleDelete(std::string username) {
    int p = find(username);
    if (d.begin() + p == d.end()) return false;
    d.erase(d.begin() + p);
    return true;
}

const bool GechatUser::doubleDelete(std::shared_ptr<GechatUser> user) {
    if (!user) return false;
    int p = find(user->name);
    if (d.begin() + p == d.end()) return false;
    user->singleDelete(name);
    d.erase(d.begin() + p);
    return true;
}

const bool GechatUser::doubleDelete(std::string username) {
    int p = find(username);
    if (d.begin() + p == d.end()) return false;
    (*(d.begin() + p))->singleDelete(name);
    d.erase(d.begin() + p);
    return true;
}