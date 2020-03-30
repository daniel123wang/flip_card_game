#ifndef GRADECHOICE_H
#define GRADECHOICE_H

#include <QMainWindow>
#include "game.h"
#include <QPushButton>

namespace Ui {
class GradeChoice;
}

class GradeChoice : public QMainWindow
{
    Q_OBJECT

public:
    explicit GradeChoice(QWidget *parent = nullptr, int glev=0);
    void resizeEvent(QResizeEvent *evt);
    ~GradeChoice();
private slots:
    void lettergrade();
    void pnp();
    void handleBack();




private:
    Ui::GradeChoice *ui;
    Game* new_game = nullptr;
    QPushButton* letter;
    QPushButton* passnpass;
    QPushButton* back;
    int levelcount;

};
#endif // GRADECHOICE_H
