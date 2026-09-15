#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointF>
#include <vector>
#include <utility>

using Segment = std::pair<QPointF, QPointF>;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<Segment>> koch;

    std::vector<std::vector<Segment>> KochSneg();
};

#endif // MAINWINDOW_H