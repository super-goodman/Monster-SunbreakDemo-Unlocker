#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MonsterRiseUnlocker.h"
#include <windows.h>
class Memory;
class Opcode;
class MonsterRiseUnlocker : public QMainWindow
{
    Q_OBJECT

public:
    MonsterRiseUnlocker(QWidget *parent = Q_NULLPTR);

    void writeSkillIndex(UINT64 offset,UINT32 index);

private:
    Ui::MonsterRiseUnlockerClass ui;
    void cBoxToggled();
    Memory* mem;
    Opcode* op;
    UINT64 baseOffset;
};
