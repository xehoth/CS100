#include "gechatuser.h"
#include "customset.h"

int main() {
    std::shared_ptr<GechatUser> gzw(new GechatUser("GeziWang"));
    std::shared_ptr<GechatUser> gf(new GechatUser("Girlfriend"));
    gf->addFriend(gzw);
    gzw->addFriend(gf);
    gf->singleDelete(gzw);

    CustomSet<GechatUser> sad_story;
    sad_story.add(*gzw);
    sad_story.add(*gf);
    sad_story.printSet();
    // prints "{GeziWang (friends: 0), Girlfriend (friends: 0)}\n"
}
