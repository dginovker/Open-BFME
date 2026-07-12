#pragma once
// Shims for GameLogic dispatch functions (Generals GameLogicDispatch.cpp family).
// Vtable slot positions and callee addresses are facts read from the binary;
// several callee NAMES are provisional (marked TODO) until more of the GUI
// subsystem is ported. Globals resolve via DIR32 relocations (masked), so only
// their types matter here, not their addresses.

enum NameKeyType { NAMEKEY_INVALID = 0 };
typedef unsigned int WindowMsgData;

enum GadgetGameMessage { GBM_SELECTED = 0x4008 };

class GameWindow;

class WindowLayout {
public:
    virtual void winSlot0();
    virtual ~WindowLayout();  // deleting destructor at vtable slot 1
    virtual void winSlot2();
    virtual void winSlot3();
    virtual void winSlot4();
    virtual void winSlot5();
    virtual void winSlot6();
    virtual void winSlot7();
    virtual void destroyWindows();  // slot 8 (+0x20)
};

class GameWindowManager {
public:
    virtual void wmSlot0();
    virtual void wmSlot1();
    virtual void wmSlot2();
    virtual void wmSlot3();
    virtual void wmSlot4();
    virtual void reset();  // slot 5 (+0x14)
    virtual void wmSlot6();
    virtual void wmSlot7();
    virtual void wmSlot8();
    virtual void wmSlot9();
    virtual void wmSlot10();
    virtual void wmSlot11();
    virtual void wmSlot12();
    virtual void wmSlot13();
    virtual void wmSlot14();
    virtual void wmSlot15();
    virtual void wmSlot16();
    virtual void wmSlot17();
    virtual void wmSlot18();
    virtual void wmSlot19();
    virtual void wmSlot20();
    virtual void wmSlot21();
    virtual void wmSlot22();
    virtual void wmSlot23();
    virtual void wmSlot24();
    virtual void wmSlot25();
    virtual void wmSlot26();
    virtual void wmSlot27();
    virtual void wmSlot28();
    virtual void wmSlot29();
    virtual void wmSlot30();
    virtual void wmSlot31();
    virtual void wmSlot32();
    virtual void wmSlot33();
    virtual void wmSlot34();
    virtual void wmSlot35();
    virtual void wmSlot36();
    virtual void wmSlot37();
    virtual void wmSlot38();
    virtual void wmSlot39();
    virtual void wmSlot40();
    virtual void wmSlot41();
    virtual void wmSlot42();
    virtual void wmSlot43();
    virtual void wmSlot44();
    virtual void wmSlot45();
    virtual void wmSlot46();
    virtual void wmSlot47();
    virtual void wmSlot48();
    virtual void wmSlot49();
    virtual void wmSlot50();
    virtual void wmSlot51();
    virtual void wmSlot52();
    virtual int winSendSystemMsg(GameWindow *window, unsigned int msg, WindowMsgData data1, WindowMsgData data2);  // slot 53 (+0xd4)
    virtual void wmSlot54();
    virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);  // slot 55 (+0xdc)
};

// TODO(identity): subsystem at .data 0x012F19E8 whose vtable slot 5 is invoked
// twice by closeWindows; renamed once more of the GUI is ported.
class InGameChatType {
public:
    virtual void icSlot0();
    virtual void icSlot1();
    virtual void icSlot2();
    virtual void icSlot3();
    virtual void icSlot4();
    virtual void reset();  // slot 5 (+0x14)
};

class ControlBar {
public:
    void hidePurchaseScience();
    void hideSpecialPowerShortcut();
};

class NameKeyGenerator {
public:
    NameKeyType nameToKey(const char *name);
};

class GameLogic {
public:
    void closeWindows(void);

    virtual ~GameLogic();

private:
    char m_pad[0x1a0];              // unexplored members up to +0x1a4
    WindowLayout *m_background;     // +0x1a4
    char m_backgroundPending;       // +0x1a8, cleared by closeWindows
};

void HideDiplomacy();
void HideInGameChat();
void ResetInGameChat();
void HideQuitMenu();
void HideSaveLoadMenu();                       // TODO(identity): guarded hide at 0xA416
void ReleaseWindowLayout(WindowLayout *layout);  // TODO(identity): null-path call at 0x49AD0

extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern InGameChatType *TheInGameChat;
extern GameWindow *TheQuitMenuWindow;      // TODO(identity): guard global 0x12F4AD4
extern GameWindow *TheSaveLoadWindow;      // TODO(identity): guard global 0x12F4B40
