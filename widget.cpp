#include "widget.h"
#include <vector>

//Used to save the blank block position
struct Point{
    int x;
    int y;
    Point(int a,int b){
        x=a;
        y=b;
    }
};

Widget::Widget(){

    /*Initialize the interface*/

    for(int i=0;i<4;i++)
        Layout[i]=new QHBoxLayout;
    MainLayout=new QVBoxLayout;
    ScoreLabel.setText("0");
    QFont b;
    b.setPixelSize(18);
    ScoreLabel.setFont(b);

    Score=0;
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            block[i][j].setText("-");
            block[i][j].setFixedSize(QSize(60,60));
            block[i][j].setAlignment(Qt::AlignCenter);
            num[i][j]=1;
        }

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            Layout[i]->addWidget(&block[i][j]);
    MainLayout->addWidget(&ScoreLabel);
    for(int i=0;i<4;i++)
        MainLayout->addLayout(Layout[i]);
    this->setLayout(MainLayout);

    /*create two number*/

    create();
    create();

    /*display number*/
    paint();
}

Widget::~Widget(){

}

void Widget::create(){
    int type=GetNumber(1,10);//2 or 4
    std::vector<Point> PList;

    /*save the blank block position*/
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(num[i][j]==1)
                PList.push_back(Point(i,j));

    /*Get a random blank block*/
    int randp=GetNumber(0,PList.size());
    Point tempp=PList.at(randp);

    /*set number*/
    if(type!=10)//10% is 4
        num[tempp.x][tempp.y]=2;
    else
        num[tempp.x][tempp.y]=4;
}



void Widget::paint(){

    /*very simple*/
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            block[i][j].setText(QString::number(num[i][j]));
            if(block[i][j].text()=="1")
            {
                block[i][j].setText("-");
                block[i][j].setStyleSheet("background-color:rgb(255,255,255);");
            }
            if(block[i][j].text()=="2")
                block[i][j].setStyleSheet("background-color:rgb(255,200,200)");
            if(block[i][j].text()=="4")
                block[i][j].setStyleSheet("background-color:rgb(255,150,150);");
            if(block[i][j].text()=="8")
                block[i][j].setStyleSheet("background-color:rgb(255,100,100);");
            if(block[i][j].text()=="16")
                block[i][j].setStyleSheet("background-color:rgb(255,50,50);");
            if(block[i][j].text()=="32")
                block[i][j].setStyleSheet("background-color:rgb(255,100,50);");
            if(block[i][j].text()=="64")
                block[i][j].setStyleSheet("background-color:rgb(255,150,50);");
            if(block[i][j].text()=="128")
                block[i][j].setStyleSheet("background-color:rgb(255,200,50);");
            if(block[i][j].text()=="256")
                block[i][j].setStyleSheet("background-color:rgb(255,255,50);");
            if(block[i][j].text()=="512")
                block[i][j].setStyleSheet("background-color:rgb(200,255,50);");
            if(block[i][j].text()=="1024")
                block[i][j].setStyleSheet("background-color:rgb(150,255,50);");
            if(block[i][j].text()=="2048")
                block[i][j].setStyleSheet("background-color:rgb(100,255,50);");
            if(block[i][j].text()=="4096")
                block[i][j].setStyleSheet("background-color:rgb(50,255,50);");
        }
    ScoreLabel.setText("得分："+QString::number(Score));
}


void Widget::up()
{
    int move=0;//whether have been moved

    for(int a=0;a<4;a++)
    {
        for(int i=0;i<4;i++)
            for(int j=i+1;j<4;j++)
            {
                if(num[i][a]==num[j][a]&&num[j][a]!=1)//whether is the same,then add up
                {
                    num[j][a]=1;
                    move=1;
                    num[i][a]*=2;
                    Score+=num[i][a];
                    break;
                }
                if(num[j][a]!=1)
                    break;
            }

    }

    for(int a=0;a<4;a++)//Make the block near the edge
    {
        for(int i=0;i<4;i++)
            if(num[i][a]==1)
                for(int j=i+1;j<4;j++)
                    if(num[j][a]!=1)
                    {
                        num[i][a]=num[j][a];
                        num[j][a]=1;
                        move=1;
                        break;
                    }


    }

    if(move==1)//create a number
        create();
    paint();

    if(check()==0)
        ScoreLabel.setText("你输啦！得分："+QString::number(Score));
}

void Widget::down()//the same as up()
{
    int move=0;
    for(int a=0;a<4;a++)
    {
        for(int i=3;i>0;i--)
            for(int j=i-1;j>=0;j--)
            {
                if(num[i][a]==num[j][a]&&num[i][a]!=1)
                {
                    num[j][a]=1;
                    move=1;
                    num[i][a]*=2;
                    Score+=num[i][a];
                    break;
                }
                if(num[j][a]!=1)
                    break;
            }

    }


    for(int a=0;a<4;a++)
    {
        for(int i=3;i>0;i--)
            if(num[i][a]==1)
            {
                for(int j=i-1;j>=0;j--)
                    if(num[j][a]!=1)
                    {
                        num[i][a]=num[j][a];
                        num[j][a]=1;
                        move=1;
                        break;
                    }

            }

    }
    if(move==1)
        create();
    paint();
    if(check()==0)
        ScoreLabel.setText("你输啦！得分："+QString::number(Score));
}

void Widget::left()//the same as up()
{
    int move=0;
    for(int a=0;a<4;a++)
    {
        for(int i=0;i<4;i++)
            for(int j=i+1;j<4;j++)
            {
                if(num[a][i]==num[a][j]&&num[a][j]!=1)
                {
                    num[a][j]=1;
                    move=1;
                    num[a][i]*=2;
                    Score+=num[a][i];
                    break;
                }
                if(num[a][j]!=1)
                    break;
            }

    }


    for(int a=0;a<4;a++)
    {
        for(int i=0;i<4;i++)
            if(num[a][i]==1)
                for(int j=i+1;j<4;j++)
                    if(num[a][j]!=1)
                    {
                        num[a][i]=num[a][j];
                        num[a][j]=1;
                        move=1;
                        break;
                    }


    }
    if(move==1)
        create();
    paint();
    if(check()==0)
        ScoreLabel.setText("你输啦！得分："+QString::number(Score));
}

void Widget::right()//the same as up()
{
    int move=0;
    for(int a=0;a<4;a++)
    {
        for(int i=3;i>0;i--)
            for(int j=i-1;j>=0;j--)
            {
                if(num[a][i]==num[a][j]&&num[a][i]!=1)
                {
                    num[a][j]=1;
                    move=1;
                    num[a][i]*=2;
                    Score+=num[a][i];
                    break;
                }
                if(num[a][j]!=1)
                    break;
            }

    }


    for(int a=0;a<4;a++)
    {
        for(int i=3;i>0;i--)
            if(num[a][i]==1)
            {
                for(int j=i-1;j>=0;j--)
                    if(num[a][j]!=1)
                    {
                        num[a][i]=num[a][j];
                        num[a][j]=1;
                        move=1;
                        break;
                    }

            }

    }
    if(move==1)
        create();
    paint();
    if(check()==0)
        ScoreLabel.setText("你输啦！得分："+QString::number(Score));
}

void Widget::keyPressEvent(QKeyEvent *e)
{

    int key = e->key();
    if (Qt::Key_S == key)
        down();
    if (Qt::Key_W == key)
        up();
    if (Qt::Key_A == key)
        left();
    if (Qt::Key_D == key)
        right();

}

int Widget::check()
{
    int temp=0;
    /*whether have the same block */
    for(int i=1;i<3;i++)
        for(int j=1;j<3;j++)
            if((num[i][j]==num[i][j-1])||(num[i][j]==num[i][j+1])||(num[i-1][j]==num[i][j])||(num[i+1][j]==num[i][j])||(num[i][j]==1))
                temp=1;

    for(int i=0;i<3;i++)
        if(num[0][i]==num[0][i+1]||num[i][0]==num[i+1][0])
            temp=1;

    for(int i=3;i>0;i--)
        if(num[3][i]==num[3][i-1]||num[i][3]==num[i-1][3])
            temp=1;

    /*whether have blank block*/
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            if(num[i][j]==1)
                temp=1;


    return temp;
}

