#include "paintscene.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent) {
    mPen.setCapStyle(Qt::RoundCap);
}

paintScene::~paintScene() {

}

void paintScene::setColor(int r,int g,int b) {
    QBrush brush(QColor(r,g,b));
    mPen.setBrush(brush);
    linePreview = new QGraphicsLineItem();
    rectPreview = new QGraphicsRectItem();
    ellipesPreview = new QGraphicsEllipseItem();
}

void paintScene::setPenSize(int size) {
    mPen.setWidth(size);
}

void paintScene::setDrawDot(bool temp) {
    DrawDot = temp;
    DrawDotR = temp;
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
    runEdit = true;
    if(DrawDotR) {
        DrawDot = true;
    }
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
    }
    if(DrawLine) {
        removeItem(linePreview);
        linePreview->setLine(previousPoint.x(),
                             previousPoint.y(),
                             event->scenePos().x(),
                             event->scenePos().y());
        linePreview->setPen(mPen);
        addItem(linePreview);
    }
    if(DrawSqure) {
        removeItem(rectPreview);
        rectPreview->setRect(previousPoint.x(),
                             previousPoint.y(),
                             event->scenePos().x()-previousPoint.x(),
                             event->scenePos().y()-previousPoint.y());
        rectPreview->setPen(mPen);
        addItem(rectPreview);
    }
    if(DrawRound) {
        removeItem(ellipesPreview);
        ellipesPreview->setRect(previousPoint.x(),
                                previousPoint.y(),
                                event->scenePos().x()-previousPoint.x(),
                                event->scenePos().y()-previousPoint.y());
        ellipesPreview->setPen(mPen);
        addItem(ellipesPreview);
    }
    update(0,0,width(),height());
}

void paintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(DrawDot) {
        DrawDot = false;
    }
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
    if(DrawRound) {
        addEllipse(previousPoint.x(),
                   previousPoint.y(),
                   event->scenePos().x()-previousPoint.x(),
                   event->scenePos().y()-previousPoint.y(),
                   mPen);
    }
}
