#pragma once
// WindowLayout (GameClient/WindowLayout.h in Generals). BFME made the layout
// methods virtual; the declaration order below reproduces the vtable read from
// the binary at 0x10f7514 (runInit, dtor, runUpdate, runShutdown, hide,
// bringForward, addWindow, removeWindow, destroyWindows). Generals' inline
// run* accessors stayed inline (their bodies land in COMDAT space at 0x4706xx,
// away from the WindowLayout.obj region at 0x497axx).

class GameWindow;
class WindowLayout;

// GameWindow layout-chain accessors (Generals GameWindow.h). Addresses come
// from reverse/symbols.csv, derived from the binary's call sites.
class GameWindow {
public:
    GameWindow *winGetNextInLayout(void);
    GameWindow *winGetPrevInLayout(void);
    int winSetNextInLayout(GameWindow *next);
    int winSetPrevInLayout(GameWindow *prev);
    int winSetLayout(WindowLayout *layout);
    int winHide(int hide);
    int winBringToTop(void);
};

// Partial GameWindowManager: only the slot used here is meaningful.
class GameWindowManager {
public:
    virtual void wmSlot0();
    virtual void wmSlot1();
    virtual void wmSlot2();
    virtual void wmSlot3();
    virtual void wmSlot4();
    virtual void wmSlot5();
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
    virtual int winDestroy(GameWindow *window);  // slot 30 (+0x78)
};

extern GameWindowManager *TheWindowManager;

// Stands in for BFME's AsciiString member (StringBase<char> family). The
// out-of-line set/dtor resolve to the matched StringBase<char> functions via
// reverse/symbols.csv until AsciiString/StringBase headers unify.
class LayoutFilename {
public:
    LayoutFilename() : m_data(0) {}
    void set(const char *str, int len);
    ~LayoutFilename();

private:
    void *m_data;
};

typedef void (*WindowLayoutFunc)(void *layout, void *userData);

class WindowLayout {
public:
    WindowLayout(void);

    virtual void runInit(void *userData) { if (m_init) m_init(this, userData); }            // slot 0
    virtual ~WindowLayout();                                                                 // slot 1
    virtual void runUpdate(void *userData) { if (m_update) m_update(this, userData); }       // slot 2
    virtual void runShutdown(void *userData) { if (m_shutdown) m_shutdown(this, userData); } // slot 3
    virtual void hide(int hide);                                                             // slot 4
    virtual void bringForward(void);                                                         // slot 5
    virtual void addWindow(GameWindow *window);                                              // slot 6
    virtual void removeWindow(GameWindow *window);                                           // slot 7
    virtual void destroyWindows(void);                                                       // slot 8

    GameWindow *getFirstWindow(void) { return m_windowList; }

private:
    GameWindow *findWindow(GameWindow *window);

    LayoutFilename m_filenameString;  // +0x04
    GameWindow *m_windowList;         // +0x08
    GameWindow *m_windowTail;         // +0x0c
    int m_windowCount;                // +0x10
    char m_hidden;                    // +0x14
    WindowLayoutFunc m_init;          // +0x18
    WindowLayoutFunc m_update;        // +0x1c
    WindowLayoutFunc m_shutdown;      // +0x20
};
