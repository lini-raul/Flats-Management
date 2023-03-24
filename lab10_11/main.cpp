//#include "lab10_11.h"
#include <QtWidgets/QApplication>

#include "teste.h"
#include "g_user_interface.h"


int main(int argc, char *argv[])
{
    Teste test;
    test.test_all();
    
    QApplication a(argc, argv);
    
    RepoLocatariFile repo{ "locatari.txt" };
    LocatarValidator valid;
    SrvLocatari srv{ repo,valid };

    GUserInterface gui{ srv };
  
    gui.show();
    


    return a.exec();
    
}
