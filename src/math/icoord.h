#pragma once

struct ICoord2DBase {
    ICoord2DBase &operator=(const ICoord2DBase &that);

    int x;
    int y;
};

struct ICoord2D : public ICoord2DBase {
    ICoord2D();
    ICoord2D(const ICoord2DBase &that);
    ICoord2D(int x, int y);

    ICoord2D &operator=(const ICoord2D &that);
    ICoord2D &operator=(const ICoord2DBase &that);
    bool operator==(const ICoord2DBase &that) const;
    bool operator!=(const ICoord2DBase &that) const;
};

struct ICoord3D {
    ICoord3D();
    ICoord3D(int x, int y, int z);

    ICoord3D &operator=(const ICoord3D &that);

    int length() const;
    void zero();

    int x;
    int y;
    int z;
};
