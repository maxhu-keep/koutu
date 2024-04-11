#ifndef CUTOUT_H
#define CUTOUT_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QImage>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QPoint>
#include <QMouseEvent>
#include <QRgb>
#include <QDebug>
#include <QFont>

class CutOut : public QWidget
{
    Q_OBJECT
public:
    explicit CutOut(QWidget *parent = nullptr);

signals:

public slots:

private:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent*event) override;

    void InitLayout();

    void InitObj();

    void ReLayout();

    void InitSlots();

    void processImages();

    bool isTransparent(const QColor &color);

    bool isBackground(const QColor &color);

private:
    QPixmap originImage;
    QPixmap processedImage;

    QPushButton * _btnOpenImage;
    QLineEdit * _inputRgb;
    QPushButton * _btnProcessImage;
    QLineEdit * _inputReplaceRgb;
    QPushButton * _btnReplaceImage;
    QPushButton * _btnSaveImage;
    QPushButton * _btnExchangeImage;
    QPushButton *backBtn;

    QLabel * _labelOriginImage;
    QLabel * _labelReplaceImage;
    QSlider *slider;
    QLabel *_labelSliderNum;

    QColor backgroundColor;
    QColor replaceColor;

    bool hasResult=false;
    int colorDifferenceThreshold=1;//像素点相似范围
    bool isCut=false;//判断当前要做的是抠图还是替换
    bool isReplace=false;//判断当前要做的是抠图还是替换
};

#endif // CUTOUT_H
