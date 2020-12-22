#ifndef MAINPAGEPROXY_H
#define MAINPAGEPROXY_H
#include"mainwindow.h"

class MainPageProxy
{
private:
    MainWindow* mw;
public:
    MainWindow* getMainWindow() const;
    void show();
    MainPageProxy();
    ~MainPageProxy();
};

#endif // MAINPAGEPROXY_H
