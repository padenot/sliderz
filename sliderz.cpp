#include "sliderz.h"
#include "ui_sliderz.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include <QSlider>
#include <QLabel>
#include <functional>
#include <iostream>
#include <QLayout>
#include <QDir>
#include <cmath>
#include <iomanip>

Sliderz::Sliderz(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::Sliderz)
{
  ui->setupUi(this);

  readJSON();
}

void print(int index, int scale, int value)
{
    std::setprecision(log10(scale));
    std::cout << index << ":" << (float)value/scale << std::endl;
}

void Sliderz::readJSON()
{
  QString val;
  QFile file;
  file.setFileName("sliderz.json");
  if (!file.exists()) {
    QLabel* label = new QLabel(QString("No sliderz.json in ") + QDir::currentPath());
    ui->verticalLayout->addWidget(label);
    return;
  }
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  val = file.readAll();
  file.close();
  QJsonParseError error;
  QJsonDocument d = QJsonDocument::fromJson(val.toUtf8(), &error);
  if (error.error != QJsonParseError::ParseError::NoError) {
    QString str = QString("JSON parse error: ") + error.errorString() + QString(" at offset ") + QString::number(error.offset);
    QLabel* label = new QLabel(str);
    ui->verticalLayout->addWidget(label);
    return;
  }
  if (d.object().keys().size() != 1) {
    QString str = QString("JSON parse error: expected only one top level key with title, found %d.").arg(d.object().keys().size());
    QLabel* label = new QLabel(str);
    ui->verticalLayout->addWidget(label);
    return;
  }
  QString app_name = d.object().keys()[0];

  QCoreApplication::setApplicationName(app_name);
  setWindowTitle( QCoreApplication::applicationName() );

  QJsonArray top = d[app_name].toArray();

  int i = 0;
  for (auto slider_text : top) {
    if (!slider_text.isObject()) {
      QString str = QString("JSON parse error: expected an array with objects, array element %d is not an object.").arg(i);
      QLabel* label = new QLabel(str);
      ui->verticalLayout->addWidget(label);
      return;
    }
    QJsonObject slider_desc = slider_text.toObject();
    QSlider* slider = new QSlider(Qt::Orientation::Horizontal);
    QString name = slider_desc["name"].toString();
    QLabel* label = new QLabel(name);
    QHBoxLayout* l = new QHBoxLayout();
    double default_value = slider_desc["default"].toDouble();
    double min = slider_desc["min"].toDouble();
    double max = slider_desc["max"].toDouble();
    double step = slider_desc["step"].toDouble();
    QString unit = slider_desc["unit"].toString();
    int scale = 1;

    if (!(default_value == (int)default_value &&
          min == (int)min &&
          max == (int)max &&
          step == (int)step)) {
      scale = 1.0 / (step - (int)step);
    }

    QLabel* min_label = new QLabel(QString::number(min));
    QLabel* max_label = new QLabel(QString::number(max));
    QLabel* val_label = new QLabel(QString::number(default_value));

    connect(slider, &QSlider::valueChanged, val_label, [val_label, unit, scale](int value) {
        val_label->setText(QString::number((double)value / scale) + unit);
    });

    l->addWidget(min_label, 0);
    l->addWidget(slider, 10);
    l->addWidget(max_label, 0);
    l->addSpacing(3);
    l->addWidget(val_label, 0, Qt::AlignRight);

    slider->setRange(min * scale, max * scale);
    slider->setTickInterval(step * scale);
    connect(slider,  &QSlider::valueChanged, std::bind(print, i, scale, std::placeholders::_1));
    slider->setValue(default_value);
    ui->verticalLayout->addWidget(label);
    ui->verticalLayout->addLayout(l);
    i++;
  }
}

  Sliderz::~Sliderz()
  {
    delete ui;
  }

