#include <QApplication>
#include "view.h"
#include "model.h"
#include "controller.h"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    View view ;
    Model model ;
    Controller controller(&model, &view) ;
    return a.exec();
}
