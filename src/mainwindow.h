#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "creditcalc.h"
#include "qcustomplot.h"

extern "C" {
#include "smartcalc.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double x_min, x_max, y_min, y_max, h, X, Y, X0, Y0;

  QVector<double> x, y;

  CreditCalc window;

 private slots:
  void input_digit();
  void input_function();
  void on_pushButton_AC_clicked();
  void on_pushButton_equals_clicked();
  void on_pushButton_X_clicked();
  void on_pushButton_Xmin_clicked();
  void on_pushButton_Xmax_clicked();
  void on_pushButton_Ymin_clicked();
  void on_pushButton_Ymax_clicked();
  void on_pushButton_graf_clicked();
  void on_pushButton_credit_clicked();
};

#endif  // MAINWINDOW_H
