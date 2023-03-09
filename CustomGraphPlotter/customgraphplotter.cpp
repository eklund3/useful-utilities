#include "customgraphplotter.h"
#include "ui_customgraphplotter.h"
#include <QVector>

CustomGraphPlotter::CustomGraphPlotter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CustomGraphPlotter)
{
    ui->setupUi(this);
    ui->customPlot->addGraph();
    m_graphCount = 1;
}

CustomGraphPlotter::~CustomGraphPlotter()
{
    delete ui;
}

const bool CustomGraphPlotter::setData(const std::vector<double> &xdata, const std::vector<double> &ydata, int graphIndex)
{
    if (graphIndex >= ui->customPlot->graphCount()) {
        qDebug() << "invalid index, add new graph (use addGraph())";
        return false;
    }
    ui->customPlot->graph(graphIndex)->setData(QVector<double>::fromStdVector(xdata), QVector<double>::fromStdVector(ydata));

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();

    ui->customPlot->setInteraction(QCP::Interaction::iRangeDrag);
    ui->customPlot->setInteraction(QCP::Interaction::iRangeZoom);
    return true;
}

const bool CustomGraphPlotter::setData(const QVector<double> &xdata, const QVector<double> &ydata, int graphIndex)
{
    if (graphIndex >= ui->customPlot->graphCount()) {
        qDebug() << "invalid index, add new graph (use addGraph())";
        return false;
    }
    ui->customPlot->graph(graphIndex)->setData(xdata, ydata);

    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->rescaleAxes();
    ui->customPlot->replot();

    ui->customPlot->setInteraction(QCP::Interaction::iRangeDrag);
    ui->customPlot->setInteraction(QCP::Interaction::iRangeZoom);
    return true;
}

bool CustomGraphPlotter::setLineWidth(int graphIndex, int width)
{
    QPen pen = ui->customPlot->graph(graphIndex)->pen();
    pen.setWidth(width);
    ui->customPlot->graph(graphIndex)->setPen(pen);
    return true;
}

void CustomGraphPlotter::addGraph()
{
    ui->customPlot->addGraph();
    ui->customPlot->graph(ui->customPlot->graphCount()-1)->setPen(QPen(Qt::black,1));
    m_graphCount++;
}

void CustomGraphPlotter::removeGraph()
{
    if (ui->customPlot->graphCount() == 0) return;
    ui->customPlot->removeGraph(ui->customPlot->graphCount()-1);
    m_graphCount--;
}

const int CustomGraphPlotter::getGraphCount()
{
    return ui->customPlot->graphCount();
}
