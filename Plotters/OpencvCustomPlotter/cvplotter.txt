struct GraphSettings
{
    bool autoscale;
    int width, height;
    double minx, maxx, miny, maxy;
};

cv::Mat MainWindow::drawPlot(const std::vector<QPointF> &data, GraphSettings &settings)
{
    int xAxisOffset = 20;
    int yAxisOffset = 20;
    cv::Mat plot(settings.height+yAxisOffset, settings.width+xAxisOffset, CV_8UC3, cv::Scalar(255, 255, 255));
    auto compx = [](const QPointF &a, const QPointF &b) {return a.x() < b.x();};
    auto compy = [](const QPointF &a, const QPointF &b) {return a.y() < b.y();};
    if (settings.autoscale) {
        settings.minx = std::min_element(data.begin(), data.end(), compx)->x() - 50;
        settings.miny = std::min_element(data.begin(), data.end(), compy)->y() - 50;
        settings.maxx = std::max_element(data.begin(), data.end(), compx)->x() + 50;
        settings.maxy = std::max_element(data.begin(), data.end(), compx)->y() + 50;
    }

    double mmStepx = (settings.maxx - settings.minx) / (double)settings.width;
    double mmStepy = (settings.maxy - settings.miny) / (double)settings.height;

    cv::Point pixCoord;
    for (int i = 0; i < data.size(); i++) {
        pixCoord.x = ((data[i].x() - settings.minx) / mmStepx)+xAxisOffset/2;
        pixCoord.y = (settings.height - ((data[i].y() - settings.miny) / mmStepy))+yAxisOffset/2;
        cv::circle(plot, pixCoord, 1, cv::Scalar(0,0,0));
    }
    //draw horizontal grid:
    int hgridCount = 10;
    int hstep = settings.height/hgridCount;
    for (int i = 1; i < hgridCount; i++) {
        cv::line(plot, cv::Point(xAxisOffset/2, i*hstep), cv::Point(settings.width, i*hstep), cv::Scalar(200,200,200));
        cv::putText(plot, cv::format("%.1f", settings.miny + ((double)i*(double)hstep)*mmStepy), cv::Point(0, (settings.height - i*hstep)-5),cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);
    }
    //draw vertical grid:
    int vgridCount = 10;
    int vstep = settings.width/vgridCount;
    for (int i = 1; i < vgridCount; i++) {
        cv::line(plot, cv::Point(i*vstep, yAxisOffset/2), cv::Point(i*vstep, settings.height), cv::Scalar(200,200,200));
        cv::putText(plot, cv::format("%.1f", settings.minx + ((double)i*(double)vstep)*mmStepx), cv::Point(i*vstep, yAxisOffset),cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,0), 1);
    }
    return plot;
}
