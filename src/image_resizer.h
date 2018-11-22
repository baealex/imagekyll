#ifndef IMAGE_RESIZER_H
#define IMAGE_RESIZER_H

#include <QDialog>

namespace Ui {
class image_resizer;
}

class image_resizer : public QDialog
{
    Q_OBJECT

public:
    explicit image_resizer(QWidget *parent = nullptr);
    ~image_resizer();

private:
    Ui::image_resizer *ui;
};

#endif // IMAGE_RESIZER_H
