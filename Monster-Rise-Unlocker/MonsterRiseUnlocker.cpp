#include "MonsterRiseUnlocker.h"
#include <windows.h>
#include "Memory.h"
#include "Opcode.h"
#include "QCheckBox.h"
#include "QMessageBox.h"
MonsterRiseUnlocker::MonsterRiseUnlocker(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    mem = new Memory();
    op = new Opcode(Memory::pid);

    //查找特征码
    //48 8B ?? ?? ?? ?? 0A 45 33 C0 48 8B CE 48 8B B8 ?? 00 00 00 48 8B D7
    UINT64 address[30] = { 0 };
    op->findBaseAddressOffset("48 8B ?? ?? ?? ?? 0A 45 33 C0 48 8B CE 48 8B B8 ?? 00 00 00 48 8B D7", address, 3, 4);
    //QMessageBox::information(this,"",QString::number(address[0], 16), "");
    baseOffset = address[0];

    //绑定信号槽
    QList<QCheckBox*> tcboxs = ui.widget->findChildren<QCheckBox*>();
    foreach(QCheckBox * cbox, tcboxs) 
        connect(cbox, &QCheckBox::stateChanged, this, &MonsterRiseUnlocker::cBoxToggled);


}

void MonsterRiseUnlocker::writeSkillIndex(UINT64 offset,UINT32 index)
{
    UINT64 of1 = mem->R8(mem->getGameModuleBase() + baseOffset);

    UINT64 of2 = mem->R8(of1 + 0xE0);
    UINT64 of3 = mem->R8(of2 + 0x390);
    UINT64 of4 = mem->R8(of3 + 0x40);
    UINT64 of5 = mem->R8(of4 + 0x10);
    mem->W4(of5 + offset, index);
}



void MonsterRiseUnlocker::cBoxToggled()
{

    QCheckBox* c = (QCheckBox*)sender();
    QString name = c->text();

    //获得当前状态
    bool statue = c->isChecked();
   
    //写入
    if (name == "1") {
        if (statue)
            writeSkillIndex(0x20,1);
        else
            writeSkillIndex(0x20, 0);
    }
    else if (name == "2") {
        if (statue)
            writeSkillIndex(0x20 + 0x04 * 1,1);
        else
            writeSkillIndex(0x20 + 0x04 * 1, 0);
    }
    else if (name == "3") {
        if (statue)
            writeSkillIndex(0x20 + 0x04 * 2,1);
        else
            writeSkillIndex(0x20 + 0x04 * 2, 0);
    }
    else if (name == "4") {
        if (statue)
            writeSkillIndex(0x20 + 0x04 * 3,1);
        else
            writeSkillIndex(0x80 + 0x04 * 3, 0);
    }
    else if (name == "5") {
        if (statue)
            writeSkillIndex(0x20 + 0x04 * 4,1);
        else
            writeSkillIndex(0x80 + 0x04 * 4, 0);
    }
    else if (name == "6") {
        if (statue)
            writeSkillIndex(0x20 + 0x04 * 5,1);
        else
            writeSkillIndex(0x80 + 0x04 * 5, 0);
    }
    else if (name == "7") {
        if (statue)
            writeSkillIndex(0x80,1);
        else
            writeSkillIndex(0x80, 0);
    }
    else if (name == "8") {
        if (statue)
            writeSkillIndex(0x80 + 0x04 * 1,1);
        else
            writeSkillIndex(0x80 + 0x04 * 1, 0);
    }
    else if (name == "9") {
        if (statue)
            writeSkillIndex(0x80 + 0x04 * 2,1);
        else
            writeSkillIndex(0x80 + 0x04 * 2, 0);
    }
    else if (name == "10") {
        if (statue)
            writeSkillIndex(0x80 + 0x04 * 3, 1);
        else
            writeSkillIndex(0x80 + 0x04 * 3, 0);
        //QMessageBox::information(this, "", QString::number(statue), "");
    }
    else if (name == "11") {
        if (statue)
            writeSkillIndex(0x80 + 0x04 * 4, 1);
        else
            writeSkillIndex(0x80 + 0x04 * 4, 0);
    }
    else if (name == "12") {
        if (statue)
            writeSkillIndex(0x80 + 0x04 * 5,1);
        else
            writeSkillIndex(0x80 + 0x04 * 5, 0);
    }

}
