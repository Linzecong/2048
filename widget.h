#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTime>
#include <QKeyEvent>
#include <stdlib.h>
#include <time.h>

class Widget : public QWidget{

public:
    QLabel block[4][4];//Used to display number
    int num[4][4];//Used to save number

    QHBoxLayout* Layout[4];//Qt's things
    QVBoxLayout* MainLayout;//Qt's things

    QLabel ScoreLabel;//Used to display score
    int Score;//Used to save score

public:
    Widget();
    ~Widget();

    //get a random number
    int GetNumber(int a, int b){
        srand(time(0));
        int num=0;
        num=a+rand()%b;
        return num;
    }

    void create();//create a number(2 or 4)

    void up();//when move up
    void down();
    void left();
    void right();

    int check();//check whether the game is over

    void paint();//display num[][]
protected:
    void keyPressEvent(QKeyEvent *e);//keyboard interface


};

