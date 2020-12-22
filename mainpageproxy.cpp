#include "mainpageproxy.h"

MainPageProxy::MainPageProxy()
{

}
MainPageProxy::~MainPageProxy()
{
    delete mw;
}

MainWindow* MainPageProxy::getMainWindow() const{
    return mw;
}

void MainPageProxy::show(){
    mw=new MainWindow();
    mw->show();
}
