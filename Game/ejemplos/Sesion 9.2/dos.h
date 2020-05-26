#ifndef __DOS_H__
#define __DOS_H__

struct Cuenta{

    Cuenta(unsigned time);

    unsigned step();
    unsigned status() const;

private:
    unsigned m_time;
};

#endif