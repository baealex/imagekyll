#include "paintscene.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent) {
    mPen.setCapStyle(Qt::RoundCap);
}

paintScene::~paintScene() {

}

void paintScene::setColor(int r,int g,int b) {
    QBrush brush(QColor(r,g,b));
    mPen.setBrush(brush);
}

void paintScene::setPenSize(int size) {
    mPen.setWidth(size);
}

void paintScene::setDrawDot(bool temp) {
    DrawDot = temp;
}

void paintScene::setDrawLine(bool temp) {
    DrawLine = temp;
}

void paintScene::setDrawRound(bool temp) {
    DrawRound = temp;
}

void paintScene::setDrawSqure(bool temp) {
    DrawSqure = temp;
}

bool paintScene::getDrawDot() {
    return DrawDot;
}

bool paintScene::getDrawLine() {
    return DrawLine;
}

bool paintScene::getDrawRound() {
    return DrawLine;
}

bool paintScene::getDrawSqure() {
    return DrawLine;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent * event){
    previousPoint = event->scenePos();
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(DrawDot) {
        addLine(previousPoint.x(),
                    previousPoint.y(),
                    event->scenePos().x(),
                    event->scenePos().y(),
                    mPen);
        previousPoint = event->scenePos();
        /*if(Shadow) {
            painter->setPen(QPen( QColor(qRgba(0, 10, 20, 50))));
        }*/
    }
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(DrawLine) {
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                mPen);
    }
    if(DrawSqure) {
        addRect(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x()-previousPoint.x(),
                event->scenePos().y()-previousPoint.y(),
                mPen);
    }
}
