#ifndef SLIDERZ_H
#define SLIDERZ_H

#include <QMainWindow>
#include <QSlider>

QT_BEGIN_NAMESPACE
namespace Ui { class Sliderz; }
QT_END_NAMESPACE

class Sliderz : public QMainWindow
{
    Q_OBJECT

public:
    Sliderz(QWidget *parent = nullptr);
    ~Sliderz();

private:
    void readJSON();
    Ui::Sliderz *ui;
};
#endif // SLIDERZ_H
