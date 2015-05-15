#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setupWidget();
    void setupWindows();

private:
    QVBoxLayout *_windowLayout;
    QWidget *_windowWidget;
    int _clientWidth;
    int _clientHeight;
};

#endif // MAINWINDOW_H
