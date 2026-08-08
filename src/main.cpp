#include <Geode/Geode.hpp>
#include <Geode/modify/AppDelegate.hpp>

using namespace geode::prelude;

class $modify(InstantShutdownAppDelegate, AppDelegate) {
    // make it run very early
    static void onModify(auto& self) {
        self.setHookPriorityPre("AppDelegate::trySaveGame", Priority::VeryEarlyPre);
    }

    void trySaveGame(bool force) {
        // hide the window immediately
        ShowWindow(WindowFromDC(wglGetCurrentDC()), 0);

        // cut the audio
        auto fmod = FMODAudioEngine::get();
        fmod->stopAllMusic(true);
        fmod->stopAllEffects();

        // now try to save your save file in the background
        AppDelegate::trySaveGame(force);
    }
};
