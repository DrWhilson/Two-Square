#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QChar>

const int Order = 5;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::search_symbol_array(char matrix[], int matrix_len, QChar search_symbol) {
    for (int i = 0; i < matrix_len; i++)
        if (matrix[i] == search_symbol) return i;
    return -1;
}

QChar** MainWindow::createMatrix(QString keyword, QChar** matrix) {
    //Массив с алфавитом для заполнени матрицы
    char alphabet[Order * Order] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','R','S','T','U','V','W','X','Y','Z' };

    //Проверка длинны ключа
    if (keyword.size() > Order * Order) {
        keyword = "KEYWORD";
    }

    //Заполнение матрицы
    int couter = 0;
    for (int i = 0; i < Order; i++) {
        for (int j = 0; j < Order; j++) {
            //Заполнение ключём
            if (couter < keyword.size()) {
                alphabet[MainWindow::search_symbol_array(alphabet, Order * Order, keyword[couter])] = '-';
                matrix[i][j] = keyword[couter];
            }
            //Заполнение остатка символами алфавита
            else {
                int special_couter = 0;
                char buff = alphabet[special_couter];
                while (alphabet[special_couter] == '-') {
                    special_couter++;
                    buff = alphabet[special_couter];
                }
                matrix[i][j] = buff;
                alphabet[special_couter] = '-';
                special_couter = 0;
            }
            couter++;
        }
    }
    return matrix;
}

QString MainWindow::crypt_function(QString word, QString keyword1, QString keyword2) {

    //создание 2х матриц
    QChar** first_matrix = new QChar* [Order];
    for (int i = 0; i < Order; i++)
        first_matrix[i] = new QChar[Order];

    QChar** second_matrix = new QChar* [Order];
    for (int i = 0; i < Order; i++)
        second_matrix[i] = new QChar[Order];

    //наполнение матриц символами
    first_matrix = MainWindow::createMatrix(keyword1, first_matrix);

    second_matrix = MainWindow::createMatrix(keyword2, second_matrix);

    //Обработка строки
    for (int i = 0; i < word.size(); i += 2) {
        //Стандартные коардинаты
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
        //Поиск коардинат первой буквы биграммы
        while (first_matrix[x1][y1] != word[i]) {
            if (x1 < Order - 1) {
                x1++;
            }
            else {
                x1 = 0;
                y1++;
            }
        }
        //Поиск коардинат второй буквы биграммы
        if (i + 1 < word.size()) {
                    while (second_matrix[x2][y2] != word[i + 1]) {
                        if (x2 < Order - 1) {
                            x2++;
                        }
                        else {
                            x2 = 0;
                            y2++;
                        }
                    }
                }
                word[i] = first_matrix[x1][y2];
        if (i + 1 < word.size()) {
            word[i + 1] = second_matrix[x2][y1];
        }
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
    }

    //Удаление матриц
    for (int i = 0; i < Order; i++)
        delete[] first_matrix[i];
    delete[] first_matrix;

    for (int i = 0; i < Order; i++)
        delete[] second_matrix[i];
    delete[] second_matrix;

    return word;
}

QString MainWindow::set_upper(QString word, int word_len) {
    for (int i = 0; i < word_len; i++) {
        word[i] = word[i].toUpper();
    }
    return word;
}


void MainWindow::on_Enc_Button_clicked()
{
    QString in_text = "hello";
    QString out_text = " ";

    QString keyword1 = "keyword";
    QString keyword2 = "exampl";
    in_text = ui->In_text->text();
    keyword1 = ui->keyword1->text();
    keyword2 = ui->keyword2->text();

    in_text = MainWindow::set_upper(in_text, in_text.size());
    keyword1 = MainWindow::set_upper(keyword1, keyword1.size());
    keyword2 = MainWindow::set_upper(keyword2, keyword2.size());

    out_text = MainWindow::crypt_function(in_text, keyword1, keyword2);

    ui->Out_Text->setText(out_text);
}


void MainWindow::on_Dec_Button_clicked()
{

}

