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
    if(event->buttons() == Qt::LeftButton)
    {
        isLeft = true;
        runEdit = true;
        if(DrawDotR) {
            DrawDot = true;
        }
        previousPoint = event->scenePos();
    }
}

void paintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(DrawDot && isLeft) {
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                mPen);
        previousPoint = event->scenePos();
    }
    else if(DrawLine && isLeft) {
        removeItem(linePreview);
        linePreview->setLine(previousPoint.x(),
                             previousPoint.y(),
                             event->scenePos().x(),
                             event->scenePos().y());
        linePreview->setPen(mPen);
        addItem(linePreview);
    }
    else if(DrawSqure && isLeft) {
        removeItem(rectPreview);
        rectPreview->setRect(previousPoint.x(),
                             previousPoint.y(),
                             event->scenePos().x()-previousPoint.x(),
                             event->scenePos().y()-previousPoint.y());
        rectPreview->setPen(mPen);
        addItem(rectPreview);
    }
    else if(DrawRound && isLeft) {
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
    if(DrawDot && isLeft) {
        DrawDot = false;
        Drawing = true;
        isLeft = false;
        ObjectCount++;
    }
    else if(DrawLine && isLeft) {
        addLine(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x(),
                event->scenePos().y(),
                mPen);
        Drawing = true;
        isLeft = false;
        ObjectCount++;
    }
    else if(DrawSqure && isLeft) {
        addRect(previousPoint.x(),
                previousPoint.y(),
                event->scenePos().x()-previousPoint.x(),
                event->scenePos().y()-previousPoint.y(),
                mPen);
        Drawing = true;
        isLeft = false;
        ObjectCount++;
    }
    else if(DrawRound && isLeft) {
        addEllipse(previousPoint.x(),
                   previousPoint.y(),
                   event->scenePos().x()-previousPoint.x(),
                   event->scenePos().y()-previousPoint.y(),
                   mPen);
        Drawing = true;
        isLeft = false;
        ObjectCount++;
    }
}
