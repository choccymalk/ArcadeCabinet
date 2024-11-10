// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override {
        /*if (event->key() == Qt::Key_P) {
            qDebug() << "Up arrow pressed!";
            // Do something when the 'A' key is pressed
        } else if (event->key() == Qt::Key_Escape) {
            close();
        }*/
        printf("key pressed");
        qDebug() << "key pressed";
        int currentIndex = getCurrentButtonIndex();
        int nextIndex = -1;
        int previousIndex;
        qDebug() << "nextIndex: " << nextIndex;
        qDebug() << "currentIndex: " << currentIndex;

        switch (event->key()) {
        case Qt::Key_P:
            colorButton(false, 1);
            colorButton(false, 2);
            colorButton(false, 3);
            colorButton(false, 4);
            colorButton(false, 5);
            colorButton(false, 6);
            colorButton(false, 7);
            if (currentIndex > 0) {
                nextIndex = currentIndex - 1;
                colorButton(true, nextIndex+1);
                qDebug() << "Moving up to index:" << nextIndex;  // Debug output
            }
            if(currentIndex == 0){
                colorButton(true, 1);
            }
            break;

        case Qt::Key_L:
            colorButton(false, 1);
            colorButton(false, 2);
            colorButton(false, 3);
            colorButton(false, 4);
            colorButton(false, 5);
            colorButton(false, 6);
            colorButton(false, 7);
            if (currentIndex < 6) {
                nextIndex = currentIndex + 1;
                colorButton(true, nextIndex+1);
                qDebug() << "Moving down to index:" << nextIndex;  // Debug output
            }
            if(currentIndex == 6){
                colorButton(true, 7);
            }
            break;

        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (currentButton)
                currentButton->click();
            break;
        }

        if (nextIndex >= 0 && nextIndex < 7) {
            focusNextButton(nextIndex);
        }
    }

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton* currentButton;
    void updateLabel();
    void updatePreviewImage();
    void initializeUI();
    int getCurrentButtonIndex();
    void colorButton(bool enable, int index);
    void focusNextButton(int nextIndex);
    void launchMame(std::string game);
    QString getImagePath(const QString& game);
};
#endif // MAINWINDOW_H
