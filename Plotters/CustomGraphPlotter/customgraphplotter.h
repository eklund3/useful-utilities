#ifndef CUSTOMGRAPHPLOTTER_H
#define CUSTOMGRAPHPLOTTER_H

#include <QDialog>

namespace Ui {
class CustomGraphPlotter;
}

class CustomGraphPlotter : public QDialog
{
    Q_OBJECT

public:
    explicit CustomGraphPlotter(QWidget *parent = nullptr);
    ~CustomGraphPlotter();

    const bool setData(const std::vector<double> &xdata, const std::vector<double> &ydata, int graphIndex);
    const bool setData(const QVector<double> &xdata, const QVector<double> &ydata, int graphIndex);
    bool setLineWidth(int graphIndex, int width);
    void addGraph();
    void removeGraph();

    const int getGraphCount();

private:
    //const std::vector<double> xdata;
    //const std::vector<double> ydata;
    int m_graphCount;

    Ui::CustomGraphPlotter *ui;

};

#endif // CUSTOMGRAPHPLOTTER_H
