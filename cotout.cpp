#include "cutout.h"

#include <QRegularExpression>

CutOut::CutOut(QWidget *parent) : QWidget(parent)
{
    InitObj();
    InitLayout();
    ReLayout();
    InitSlots();
}

void CutOut::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
}

void CutOut::mousePressEvent(QMouseEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        int x=event->pos().x();
        int y=event->pos().y();
        int x_min=_labelOriginImage->x();
        int y_min=_labelOriginImage->y();
        if(x>=x_min&&x<=x_min+260&&y>=y_min&&y<=y_min+260)
        {
            QPixmap pixmap = QPixmap::grabWidget(this, x, y, 1, 1);
            if (!pixmap.isNull())
            {
                QImage image = pixmap.toImage();//将像素图转换为QImage
                if (!image.isNull()) //如果image不为空
                {
                     if (image.valid(0, 0)) //坐标位置有效
                     {
                         QColor color = image.pixel(0, 0);
                         int R = color.red();
                         int G = color.green();
                         int B = color.blue();
                         QString strInfo = QString("%1,%2,%3").arg(R).arg(G).arg(B);
                         _inputRgb->setText(strInfo);
                     }
                }
            }
        }

    }

}
//布局设置
void CutOut::InitLayout()
{
    //右侧功能区
    _btnOpenImage=new QPushButton;
    _btnProcessImage=new QPushButton;
    _btnReplaceImage=new QPushButton;
    _btnSaveImage=new QPushButton;
    _btnExchangeImage=new QPushButton;

    _inputRgb=new QLineEdit;
    _inputReplaceRgb=new QLineEdit;

    //左侧图片栏
    _labelOriginImage=new QLabel;
    _labelReplaceImage=new QLabel;

    //布局
    QHBoxLayout *mainBox=new QHBoxLayout;
    QVBoxLayout *btnBox=new QVBoxLayout;

    mainBox->addWidget(_labelOriginImage);
    mainBox->addWidget(_labelReplaceImage);
    mainBox->addLayout(btnBox);

    btnBox->addStretch(5);
    btnBox->addWidget(_btnOpenImage);
    btnBox->addWidget(_inputRgb);
    btnBox->addWidget(_btnProcessImage);
    btnBox->addWidget(_inputReplaceRgb);
    btnBox->addWidget(_btnReplaceImage);
    btnBox->addWidget(_btnSaveImage);
    btnBox->addStretch(5);
    btnBox->setSpacing(20);


    slider=new QSlider(Qt::Horizontal);
    _labelSliderNum=new QLabel;

    QHBoxLayout *sliderLayout=new QHBoxLayout;
    sliderLayout->addWidget(slider);
    sliderLayout->addSpacing(10);
    sliderLayout->addWidget(_labelSliderNum);
    sliderLayout->addSpacing(15);
    sliderLayout->addWidget(_btnExchangeImage);
    sliderLayout->addSpacing(30);

    QVBoxLayout *mainvBox=new QVBoxLayout;
    mainvBox->addLayout(mainBox);
    mainvBox->addLayout(sliderLayout);
    mainvBox->addSpacing(100);
    this->setLayout(mainvBox);
    this->setFixedSize(806,600);


}

void CutOut::InitObj()
{

}

//样式设置
void CutOut::ReLayout()
{
    _labelOriginImage->setFixedSize(260,260);
    _labelReplaceImage->setFixedSize(260,260);

    _btnOpenImage->setFixedSize(100,40);
    _btnOpenImage->setText("选择图片");
    _btnOpenImage->setStyleSheet("QPushButton {\
                                 background-color: #808069;\
                                 color: white;\
                                 border-style: outset;\
                                 border-width: 2px;\
                                 border-radius: 10px;\
                                 border-color: beige;\
                                 font-size: 12px;\
                                 padding: 6px;\
                             }\
                             QPushButton:hover {\
                                 background-color: #148CD2;\
                             }\
                             QPushButton:pressed {\
                                 background-color: #005CA3;\
                             }");

    _btnProcessImage->setFixedSize(100,40);
    _btnProcessImage->setText("开始抠图");
    _btnProcessImage->setDisabled(true);
    _btnProcessImage->setStyleSheet("QPushButton {\
                                 background-color: 	#808069;\
                                 color: white;\
                                 border-style: outset;\
                                 border-width: 2px;\
                                 border-radius: 10px;\
                                 border-color: beige;\
                                 font-size: 12px;\
                                 padding: 6px;\
                             }\
                             QPushButton:hover {\
                                 background-color: #148CD2;\
                             }\
                             QPushButton:pressed {\
                                 background-color: #005CA3;\
                             }");


    _btnReplaceImage->setFixedSize(100,40);
    _btnReplaceImage->setText("开始替换");
    _btnReplaceImage->setStyleSheet("QPushButton {\
                                 background-color: 	#808069;\
                                 color: white;\
                                 border-style: outset;\
                                 border-width: 2px;\
                                 border-radius: 10px;\
                                 border-color: beige;\
                                 font-size: 12px;\
                                 padding: 6px;\
                             }\
                             QPushButton:hover {\
                                 background-color: #148CD2;\
                             }\
                             QPushButton:pressed {\
                                 background-color: #005CA3;\
                             }");


     _btnSaveImage->setFixedSize(100,40);
     _btnSaveImage->setText("保存图片");
     _btnSaveImage->setStyleSheet("QPushButton {\
                                  background-color: #808069;\
                                  color: white;\
                                  border-style: outset;\
                                  border-width: 2px;\
                                  border-radius: 10px;\
                                  border-color: beige;\
                                  font-size: 12px;\
                                  padding: 6px;\
                              }\
                              QPushButton:hover {\
                                  background-color: #148CD2;\
                              }\
                              QPushButton:pressed {\
                                  background-color: #005CA3;\
                              }");
    _btnExchangeImage->setFixedSize(100,40);
    _btnExchangeImage->setText("继续处理");
    _btnExchangeImage->setDisabled(true);
    _btnExchangeImage->setStyleSheet("QPushButton {\
                                 background-color: #808069;\
                                 color: white;\
                                 border-style: outset;\
                                 border-width: 2px;\
                                 border-radius: 10px;\
                                 border-color: beige;\
                                 font-size: 12px;\
                                 padding: 6px;\
                             }\
                             QPushButton:hover {\
                                 background-color: #148CD2;\
                             }\
                             QPushButton:pressed {\
                                 background-color: #005CA3;\
                             }");
                             //返回登录界面按钮
                                 backBtn=new QPushButton();
                                 backBtn->setParent(this);
                                 backBtn->setText("返回");
                                 backBtn->setFixedSize(100,40);
                                 backBtn->setStyleSheet("QPushButton {\
                                                        background-color: #808069;\
                                 color: white;\
                                 border-style: outset;\
                                 border-width: 2px;\
                                 border-radius: 10px;\
                                 border-color: beige;\
                                 font-size: 12px;\
                                 padding: 6px;\
                                 }\
                                 QPushButton:hover {\
                                     background-color: #148CD2;\
                                 }\
                                 QPushButton:pressed {\
                                     background-color: #005CA3;\
                                 }");
                                 backBtn->move(this->width()-backBtn->width()-20, this->height()-backBtn->height()-20);





    _inputRgb->setPlaceholderText("RGB参数");
    _inputRgb->setFixedSize(200,30);

    _inputReplaceRgb->setPlaceholderText("需替换的RGB参数");
    _inputReplaceRgb->setFixedSize(200,30);

    _labelOriginImage->setText("待处理图片");
    _labelOriginImage->setStyleSheet("QLabel{"
                                     "border: 2px dashed #808080;"
                                     "background-color: #e0e0e0;"
                                     "color: #000000;"
                                     "font-size: 18px;"
                                     "text-align: center;"
                                     "}");
    _labelReplaceImage->setText("处理中图片");
    _labelReplaceImage->setStyleSheet("QLabel{"
                                      "border: 2px dashed #808080;"
                                      "background-color: #e0e0e0;"
                                      "color: #000000;"
                                      "font-size: 18px;"
                                      "text-align: center;"
                                      "}");

    slider->setStyleSheet("QSlider::groove:horizontal {\
                          border: 2px solid gray;\
                          height: 4px; \
                          left: 16px; \
                          right: 16px; \
                      } \
                      QSlider::handle:horizontal {\
                          border: 2px solid gray; \
                          background:white;\
                          border-radius:10px;\
                          width: 20px; \
                          height: 20px; \
                          margin: -10px; \
                      } \
                      QSlider::add-page:horizontal{ \
                          background: rgb(189, 189, 189);\
                      } \
                      QSlider::sub-page:horizontal{ \
                          background: rgb(80, 165, 245);\
                      }");
     slider->setRange(0,300);
     slider->setValue(0);
     slider->setFixedWidth(450);
     _labelSliderNum->setFixedSize(50,25);
     _labelSliderNum->setText("0");
     _labelSliderNum->setAlignment(Qt::AlignCenter);
     _labelSliderNum->setStyleSheet("background-color: lightgray; border: 1px solid gray;"
                                    "padding: 5px; border-radius:5px;");


     this->setStyleSheet(""
                         "QWidget{"
                         "background-color: #80C7E2;"
                         "border: 2px solid #447799"
                         "border-radius: 10px;"
                         "padding: 2px;"
                         "color: 2D3D4D;"
                         "}"
                         "QWidget:hover{"
                         "background-color: #A6D1E8;"
                         "border: 2px solid #6699CC"
                         "}");


}

void CutOut::InitSlots()
{
    //抠图
    connect(_btnProcessImage,&QPushButton::clicked,[=](){
        if(_inputRgb->text().trimmed()!="")
        {
            isCut=true;
            isReplace=false;
            processImages();
            hasResult=true;
            _btnExchangeImage->setDisabled(false);

        }
        else
        {
            QMessageBox::information(this,"提示","请先填写需要抠掉的RGB参数");
        }
    });

    //替换
    connect(_btnReplaceImage,&QPushButton::clicked,[=](){
        if(_inputReplaceRgb->text().trimmed()!="")
        {

            isCut=false;
            isReplace=true;
            processImages();
            hasResult=true;
            _btnExchangeImage->setDisabled(false);
        }
        else
        {
            QMessageBox::information(this,"提示","请先填写需要替换的RGB参数");
        }
    });

    //上传图片
    connect(_btnOpenImage,&QPushButton::clicked,[=](){
        hasResult=false;
        _labelReplaceImage->setPixmap(QPixmap());
        QString filePath=QFileDialog::getOpenFileName(this,"选择图片","","图像文件(*.jpg *.png *.jpeg *.bmp)");
        if(!filePath.isEmpty())
        {
            //读取选定文件
            QPixmap pixmap(filePath);
            //图片缩放处理
            _labelOriginImage->setPixmap(pixmap.scaled(260,260,Qt::KeepAspectRatio,Qt::SmoothTransformation));//保持图片不失真缩放

        }
        _btnProcessImage->setDisabled(false);
        _btnReplaceImage->setDisabled(false);
    });

    //保存图片

    connect(_btnSaveImage,&QPushButton::clicked,[=](){
        if(hasResult)
        {
            QString resultPath=QFileDialog::getSaveFileName(this,"保存图片","","(*.png)");
            if(!resultPath.isEmpty())
            {
                processedImage.save(resultPath);
            }
        }
        else
        {
            QMessageBox::information(this,"保存文件","请先进行图片处理!");

        }
    });

    //继续处理

    connect(_btnExchangeImage,&QPushButton::clicked,[=](){
        _labelOriginImage->setPixmap(processedImage.scaled(260,260,Qt::KeepAspectRatio,Qt::SmoothTransformation));
        _labelReplaceImage->setPixmap(QPixmap());
    });

    //滑动条拖动
    connect(slider,&QSlider::valueChanged,this,[=](){
        colorDifferenceThreshold=slider->value();
        _labelSliderNum->setText(QString::number(colorDifferenceThreshold));

    });

    //滑动条释放
    connect(slider,&QSlider::sliderReleased,this,[=](){
        if(_inputRgb->text().trimmed()!="")
        {
            processImages();
            hasResult=true;
            _btnExchangeImage->setDisabled(false);

        }
        else
        {
            QMessageBox::information(this,"提示","请先填写需要抠掉的RGB参数");
        }
    });
}

void CutOut::processImages()
{
    QString rgbNum=_inputRgb->text();//被替换的rgb颜色

    //使用正则表达式获取rgb参数
    QRegularExpression regex("(\\d+),(\\d+),(\\d+)");

    //进行匹配
    QRegularExpressionMatch match=regex.match(rgbNum);

    if(match.hasMatch()){
        //提取参数
        int red=match.captured(1).toInt();
        int green=match.captured(2).toInt();
        int blue=match.captured(3).toInt();
        //定义背景颜色
        backgroundColor.setRgb(red,green,blue);
    }
    //要替换的颜色
    QString replaceNum=_inputReplaceRgb->text();

    //使用正则表达式获取rgb参数
    QRegularExpression regexReplace("(\\d+),(\\d+),(\\d+)");

    //进行匹配
    QRegularExpressionMatch matchReplace=regexReplace.match(replaceNum);

    if(matchReplace.hasMatch()){
        //提取参数
        int red=matchReplace.captured(1).toInt();
        int green=matchReplace.captured(2).toInt();
        int blue=matchReplace.captured(3).toInt();
        //定义背景颜色
        replaceColor.setRgb(red,green,blue);
    }

    QImage img=_labelOriginImage->pixmap()->toImage();
    int width=img.width();
    int height=img.height();

    QImage resultImg(width,height,QImage::Format_ARGB32);//创建一个拥有alpha通道的图片对象
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            QColor pixelColor =QColor(img.pixel(x,y));//获取当前像素点颜色值
            if(isTransparent(pixelColor))
            {
                //如果是透明像素，保持透明就行
                resultImg.setPixel(x,y,qRgba(0,0,0,0));

            }
            else if(isBackground(pixelColor))
            {
                if(isCut&&!isReplace)
                {
                    //如果当前像素点颜色与背景色匹配或接近，设置alpha通道为0，完全透明
                    resultImg.setPixel(x,y,qRgba(pixelColor.red(),pixelColor.green(),pixelColor.blue(),0));
                }
                else if(!isCut&&isReplace)
                {
                     //如果当前像素点颜色与背景色匹配或接近，替换为当前颜色
                    resultImg.setPixel(x,y,qRgba(replaceColor.red(),replaceColor.green(),replaceColor.blue(),255));
                }
            }
            else
            {
                //保留当前颜色
                resultImg.setPixel(x,y,qRgba(pixelColor.red(),pixelColor.green(),pixelColor.blue(),255));
            }
        }
    }

    processedImage=QPixmap::fromImage(resultImg);
    _labelReplaceImage->setPixmap(processedImage);

}

bool CutOut::isTransparent(const QColor &color)
{
    return color.alpha()==0;
}

bool CutOut::isBackground(const QColor &color)
{
    //计算色差
    int colorDifference=std::abs(color.red()-backgroundColor.red())+std::abs(color.green()-backgroundColor.green())
            +std::abs(color.blue()-backgroundColor.blue());
    return colorDifference<colorDifferenceThreshold;
}

