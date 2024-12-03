#include "creditcalc.h"

#include <iostream>

#include "ui_creditcalc.h"

CreditCalc::CreditCalc(QWidget *parent)
    : QWidget(parent), ui(new Ui::CreditCalc) {
  ui->setupUi(this);

  ui->summa->setValidator(new QIntValidator(1, 1e9));
  ui->term->setValidator(new QIntValidator(1, 99));
  ui->percent->setValidator(new QDoubleValidator(1, 99, 1));
  ui->term->setPlaceholderText("от 1 до 99");
  ui->summa->setPlaceholderText("от 1 до 100000000");
  ui->percent->setPlaceholderText("от 1 до 99");
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_calculate_clicked() {
  QString N_str = ui->term->text();
  QString S_str = ui->summa->text();
  QString P_str = ui->percent->text().replace(',', '.');
  double P = P_str.toDouble();
  int N = N_str.toInt();
  double S = S_str.toDouble();

  if (P > 0 && S > 0 && N > 0) {
    QString period_str = ui->period->currentText();

    char result_str[100];

    if (period_str == "лет") {
      N *= 12;
    }

    P = P * 0.01 / 12;

    double monthly_pay = 0, total_pay = 0, overpayment = 0;

    if (ui->annuity->isChecked()) {
      monthly_pay = S * (P + P / (pow((1 + P), N) - 1));
      monthly_pay = round(monthly_pay * 100) / 100;
      total_pay = round(monthly_pay * N * 100) / 100;
      overpayment = total_pay - S;

      sprintf(result_str, "%.2f", monthly_pay);
      ui->payment_first->setText(result_str);
      ui->payment_last->setText(result_str);

      sprintf(result_str, "%.2f", overpayment);
      ui->overpayment_show->setText(result_str);

      sprintf(result_str, "%.2f", total_pay);
      ui->total_payment_show->setText(result_str);

      ui->payment_decrease->setText("0");

    } else if (ui->differentiat->isChecked()) {
      double principal_debt = S / N, percent_sum = 0, S_init = S;
      double first_pay = round((principal_debt + S * P) * 100) / 100;

      for (int i = 0; i < N; i++) {
        percent_sum = S * P;
        monthly_pay = round((principal_debt + percent_sum) * 100) / 100;
        if (i == 0) {
          sprintf(result_str, "%.2f", monthly_pay);
          ui->payment_first->setText(result_str);
        }
        overpayment = round((overpayment + percent_sum) * 100) / 100;
        S = S - principal_debt;

        double delta = (first_pay - monthly_pay) / (N - 1);
        sprintf(result_str, "%.2f", delta);
        ui->payment_decrease->setText(result_str);
      }

      sprintf(result_str, "%.2f", monthly_pay);
      ui->payment_last->setText(result_str);

      total_pay = S_init + overpayment;
      sprintf(result_str, "%.2f", total_pay);
      ui->total_payment_show->setText(result_str);

      sprintf(result_str, "%.2f", overpayment);
      ui->overpayment_show->setText(result_str);
    }
  } else {
    QMessageBox::warning(this, "Внимание !", "Заполните все поля!");
  }
}

void CreditCalc::on_pushButton_new_calculate_clicked() {
  ui->payment_first->setText("");
  ui->payment_last->setText("");
  ui->overpayment_show->setText("");
  ui->total_payment_show->setText("");

  ui->summa->setText("");
  ui->percent->setText("");
  ui->term->setText("");
}
