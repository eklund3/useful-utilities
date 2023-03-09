#include <QVector>

namespace math {
namespace filters {
double getAvrgInInterval(const QVector<double> &src, int from, int to)
{
    return std::accumulate(src.begin()+from, src.begin()+to, 0)/(double)(to-from);
}
double getMedianInInterval(const QVector<double> &src, int from, int to)
{
    std::vector<double> vec(src.begin()+from, src.begin()+to);
    std::sort(vec.begin()+from, vec.begin()+to);
    return vec[round(from+to)/2];
}

void medianFiltr(QVector<double> &src, QVector<double> &dst, int window)
{
    if (window == 0) return;
    if (window < 3) {
        window = 3;
        qDebug() << "averageFiltr(): Invalid median filter window";
    }
    if (window % 2 == 0) window++;
    QVector<double> src_buf = src;
    dst.clear();
    int start = floor((float)window/2.0);
    int end = src_buf.size() - start;
    double median = getMedianInInterval(src_buf, 0, start-1);
    for(int i = 0; i < start-1; i++) {
        dst.push_back(median); //заполняем то, для чего не можем посчитать медиану
    }
    for(int i = start; i < end; i++) {
        median = getMedianInInterval(src_buf,i-start, i+start);
        dst.push_back(median);
    }
    median = getMedianInInterval(src_buf, end, src_buf.size());
    for(int i = end; i < src_buf.size(); i++) {
        dst.push_back(median); //заполняем то, для чего не можем посчитать медиану
    }
}

void averageFiltr(QVector<double> &src, QVector<double> &dst, int window)
{
    if (window == 0) return;
    if (window < 3) {
        window = 3;
        qDebug() << "averageFiltr(): Invalid average filter window";
    }
    if (window % 2 == 0) window++;
    QVector<double> src_buf = src;
    dst.clear();
    int start = floor((float)window/2.0);
    int end = src_buf.size() - start;
    double avrg = getAvrgInInterval(src_buf, 0, start-1);
    for(int i = 0; i < start-1; i++) {
        dst.push_back(avrg); //заполняем то, для чего не можем посчитать среднее
    }
    for(int i = start; i < end; i++) {
        avrg = getAvrgInInterval(src_buf,i-start, i+start);
        dst.push_back(avrg);
    }
    avrg = getAvrgInInterval(src_buf, end, src_buf.size());
    for(int i = end; i < src_buf.size(); i++) {
        dst.push_back(avrg); //заполняем то, для чего не можем посчитать среднее
    }
}
} //namespace filters
} // namespace math

