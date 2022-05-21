#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int search_symbol_array(char matrix[], int matrix_len, QChar search_symbol);
    QChar** createMatrix(QString keyword, QChar** matrix);
    QString crypt_function(QString word, QString keyword1, QString keyword2);
    QString set_upper(QString word, int word_len);

private slots:
    void on_Enc_Button_clicked();

    void on_Dec_Button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
