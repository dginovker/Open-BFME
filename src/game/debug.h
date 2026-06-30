#pragma once

class Debug {
public:
    static void PostStaticInit();

private:
    static Debug *PreStaticInit();
};
