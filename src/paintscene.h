#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <QVector2D>

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    ~paintScene();

    void setShadow(bool x);
    void setColor(int r,int g,int b);
    void setPenSize(int size);
    void setDrawDot(bool temp);
    void setDrawLine(bool temp);
    void setDrawSqure(bool temp);
    void setDrawRound(bool temp);

    bool getDrawDot();
    bool getDrawLine();
    bool getDrawSqure();
    bool getDrawRound();

    bool runEdit = false;

private:
    QPen mPen;
    int PenSize;
    QPointF previousPoint;
    bool DrawDot;
    bool DrawLine;
    bool DrawSqure;
    bool DrawRound;

private:
    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAINTSCENE_H
