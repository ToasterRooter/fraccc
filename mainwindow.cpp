#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QPainter>
#include <QResizeEvent>

using namespace std;

vector<Segment> next(const vector<Segment>& current)
{
    vector<Segment> result;
    for (const auto& seg : current)
    {
        QPointF A = seg.first, B = seg.second;

        QPointF P1, P2, P3;
        P1.setX(A.x() + (B.x() - A.x()) / 3);
        P1.setY(A.y() + (B.y() - A.y()) / 3);

        P2.setX(A.x() + 2 * (B.x() - A.x()) / 3);
        P2.setY(A.y() + 2 * (B.y() - A.y()) / 3);

        double dx = P2.x() - P1.x();
        double dy = P2.y() - P1.y();

        double L = sqrt(dx * dx + dy * dy);
        double Mx = (P1.x() + P2.x()) / 2;
        double My = (P1.y() + P2.y()) / 2;
        double H = L * sqrt(3) / 2;

        P3.setX(Mx - (dy / L) * H);
        P3.setY(My + (dx / L) * H);

        result.push_back({A, P1});
        result.push_back({P1, P3});
        result.push_back({P3, P2});
        result.push_back({P2, B});
    }
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(8);
    ui->horizontalSlider->setValue(0);

    connect(ui->horizontalSlider, &QSlider::valueChanged,
            this, [this](int) { update(); });

    koch = KochSneg();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    koch = KochSneg();
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 1.5));

    int n = ui->horizontalSlider->value();
    if (n < 0 || n >= static_cast<int>(koch.size())) return;

    for (const auto& seg : koch[n])
    {
        painter.drawLine(seg.first, seg.second);
    }
}

vector<vector<Segment>> MainWindow::KochSneg()
{
    double cx = width() / 2.0;
    double cy = height() / 2.0;

    double R = std::min(width(), height()) / 3.0;

    QPointF A(cx, cy - R);
    QPointF B(cx - R * sqrt(3) / 2, cy + R / 2);
    QPointF C(cx + R * sqrt(3) / 2, cy + R / 2);

    vector<vector<Segment>> result;

    vector<Segment> first;
    first.push_back({A, B});
    first.push_back({B, C});
    first.push_back({C, A});
    result.push_back(first);

    for (int n = 1; n <= 8; n++) {
        result.push_back(next(result[n - 1]));
    }

    return result;
}
