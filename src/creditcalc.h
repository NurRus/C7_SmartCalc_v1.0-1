#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QIntValidator>
#include <QMessageBox>
#include <QWidget>
#include <cmath>

extern "C" {
#include "smartcalc.h"
}

namespace Ui {
class CreditCalc;
}

class CreditCalc : public QWidget {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_pushButton_calculate_clicked();

  void on_pushButton_new_calculate_clicked();

 private:
  Ui::CreditCalc *ui;
};

#endif  // CREDITCALC_H
