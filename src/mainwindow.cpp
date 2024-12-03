#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_degree, SIGNAL(clicked()), this,
          SLOT(input_function()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_abs, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(input_digit()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_divide, SIGNAL(clicked()), this,
          SLOT(input_function()));
  connect(ui->pushButton_multiply, SIGNAL(clicked()), this,
          SLOT(input_function()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input_function()));
  connect(ui->pushButton_brackets_open, SIGNAL(clicked()), this,
          SLOT(input_function()));
  connect(ui->pushButton_brackets_close, SIGNAL(clicked()), this,
          SLOT(input_function()));
  connect(ui->pushButton_argument, SIGNAL(clicked()), this,
          SLOT(input_function()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this,
          SLOT(on_pushButton_AC_clicked()));
  connect(ui->pushButton_X, SIGNAL(clicked()), this,
          SLOT(on_pushButton_X_clicked()));
  connect(ui->pushButton_Xmin, SIGNAL(clicked()), this,
          SLOT(on_pushButton_Xmin_clicked()));
  connect(ui->pushButton_Xmax, SIGNAL(clicked()), this,
          SLOT(on_pushButton_Xmax_clicked()));
  connect(ui->pushButton_Ymin, SIGNAL(clicked()), this,
          SLOT(on_pushButton_Ymin_clicked()));
  connect(ui->pushButton_Ymax, SIGNAL(clicked()), this,
          SLOT(on_pushButton_Ymax_clicked()));
  connect(ui->pushButton_graf, SIGNAL(clicked()), this,
          SLOT(on_pushButton_Ymax_clicked()));

  ui->pushButton_AC->setCheckable(true);
  ui->pushButton_X->setCheckable(true);
  ui->pushButton_Xmin->setCheckable(true);
  ui->pushButton_Xmax->setCheckable(true);
  ui->pushButton_Ymin->setCheckable(true);
  ui->pushButton_Ymax->setCheckable(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::input_digit() {
  if (ui->pushButton_AC->isChecked()) {
    ui->result_show->setText("");
    ui->pushButton_AC->setChecked(false);
  }

  QPushButton *button = (QPushButton *)sender();
  QString new_label;

  if (ui->pushButton_X->isChecked()) {
    new_label = (ui->argument_show->text() + button->text());
    ui->argument_show->setText(new_label);
  } else if (ui->pushButton_Xmin->isChecked()) {
    new_label = (ui->Xmin_show->text() + button->text());
    ui->Xmin_show->setText(new_label);
  } else if (ui->pushButton_Xmax->isChecked()) {
    new_label = (ui->Xmax_show->text() + button->text());
    ui->Xmax_show->setText(new_label);
  } else if (ui->pushButton_Ymax->isChecked()) {
    new_label = (ui->Ymax_show->text() + button->text());
    ui->Ymax_show->setText(new_label);
  } else if (ui->pushButton_Ymin->isChecked()) {
    new_label = (ui->Ymin_show->text() + button->text());
    ui->Ymin_show->setText(new_label);
  } else {
    new_label = (ui->result_show->text() + button->text());
    ui->result_show->setText(new_label);
  }
}

void MainWindow::input_function() {
  if (ui->pushButton_AC->isChecked()) {
    ui->result_show->setText("");
    ui->pushButton_AC->setChecked(false);
  }

  QPushButton *button = (QPushButton *)sender();
  QString new_label;

  if (!(ui->pushButton_X->isChecked()) && !(ui->pushButton_Xmin->isChecked()) &&
      !(ui->pushButton_Xmax->isChecked()) &&
      !(ui->pushButton_Ymin->isChecked()) &&
      !(ui->pushButton_Ymax->isChecked())) {
    new_label = (ui->result_show->text() + button->text());
    ui->result_show->setText(new_label);
  }
}

void MainWindow::on_pushButton_equals_clicked() {
  int error = 0;
  QString str_label = (ui->result_show->text());

  QString arg_label = (ui->argument_show->text());
  double x = arg_label.toDouble();

  char expression[1000];
  strcpy(expression, str_label.toLocal8Bit().constData());

  double y = base_calculation(expression, x, &error);

  char result_str[100];

  switch (error) {
    case 1:
      strcpy(result_str, "Ошибка ввода!");
      break;
    case 2:
      strcpy(result_str, "Деление на ноль!");
      break;
    case 3:
      strcpy(result_str, "Логарифм недопустимого числа!");
      break;
    case 4:
      strcpy(result_str, "Корень недопустимого числа!");
      break;
    default:
      sprintf(result_str, "%.7f", y);
      break;
  }
  ui->result_show->setText(result_str);
}

void MainWindow::on_pushButton_AC_clicked() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  ui->result_show->setText("0");
  ui->pushButton_X->setChecked(false);
  ui->pushButton_Xmin->setChecked(false);
  ui->pushButton_Xmax->setChecked(false);
  ui->pushButton_Ymin->setChecked(false);
  ui->pushButton_Ymax->setChecked(false);
}

void MainWindow::on_pushButton_X_clicked() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  ui->argument_show->setText("");
  ui->pushButton_Xmax->setChecked(false);
  ui->pushButton_Xmin->setChecked(false);
  ui->pushButton_Ymax->setChecked(false);
  ui->pushButton_Ymin->setChecked(false);
}

void MainWindow::on_pushButton_Xmin_clicked() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  ui->Xmin_show->setText("");
  ui->pushButton_X->setChecked(false);
  ui->pushButton_Xmax->setChecked(false);
  ui->pushButton_Ymin->setChecked(false);
  ui->pushButton_Ymax->setChecked(false);
}

void MainWindow::on_pushButton_Xmax_clicked() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  ui->Xmax_show->setText("");
  ui->pushButton_X->setChecked(false);
  ui->pushButton_Xmin->setChecked(false);
  ui->pushButton_Ymin->setChecked(false);
  ui->pushButton_Ymax->setChecked(false);
}

void MainWindow::on_pushButton_Ymin_clicked() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  ui->Ymin_show->setText("");
  ui->pushButton_X->setChecked(false);
  ui->pushButton_Xmax->setChecked(false);
  ui->pushButton_Xmin->setChecked(false);
  ui->pushButton_Ymax->setChecked(false);
}

void MainWindow::on_pushButton_Ymax_clicked() {
  QPushButton *button = (QPushButton *)sender();
  button->setChecked(true);
  ui->Ymax_show->setText("");
  ui->pushButton_X->setChecked(false);
  ui->pushButton_Xmax->setChecked(false);
  ui->pushButton_Xmin->setChecked(false);
  ui->pushButton_Ymin->setChecked(false);
}

void MainWindow::on_pushButton_graf_clicked() {
  ui->widget->clearGraphs();
  x.clear();
  y.clear();

  h = 0.01;
  int N = 0;

  QString Xmin_label = (ui->Xmin_show->text());
  x_min = Xmin_label.toDouble();

  QString Xmax_label = (ui->Xmax_show->text());
  x_max = Xmax_label.toDouble() + h;

  QString Ymin_label = (ui->Ymin_show->text());
  y_min = Ymin_label.toDouble();

  QString Ymax_label = (ui->Ymax_show->text());
  y_max = Ymax_label.toDouble();

  int error = 0;
  QString str_label = (ui->result_show->text());
  char expression[255];
  strcpy(expression, str_label.toLocal8Bit().constData());

  ui->widget->xAxis->setRange(x_min - h, x_max + h);
  ui->widget->yAxis->setRange(y_min - h, y_max + h);

  for (X = x_min; X <= x_max; X += h) {
    Y = base_calculation(expression, X, &error);
    if (error > 0) {
      if (N > 0) {
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x, y);
        ui->widget->replot();
      }
      x.clear();
      y.clear();
      N = 0;
    } else {
      y.push_back(Y);
      x.push_back(X);
      N++;
    }
  }

  if (N > 0) {
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
  }
}

void MainWindow::on_pushButton_credit_clicked() { window.show(); }
