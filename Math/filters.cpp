#include <QVector>

namespace math {
namespace filters {
double getAvrgInInterval(const QVector<double> &src, int from, int to)
{
    if (from - to == 0) return src[from];
    return std::accumulate(src.begin()+from, src.begin()+to+1, 0.0) / (double)(to-from+1);
}
double getMedianInInterval(const QVector<double> &src, int from, int to)
{
    if (from - to == 0) return src[from];
    std::vector<double> vec(src.begin()+from, src.begin()+to+1);
    std::sort(vec.begin(), vec.begin() + vec.size());
    return vec[(to-from)/2];
}

void medianFiltr(QVector<double> &src, QVector<double> &dst, int window)
{
    if (window == 0) return;
    if (window < 3) {
        window = 3;
        qDebug() << "medianFiltr(): Invalid median filter window";
    }
    if (window % 2 == 0) window++;
    QVector<double> src_buf = src;
    dst.clear();
    int start = floor((float)window/2.0);
    int end = src_buf.size() - start;
    double median = getMedianInInterval(src_buf, 0, start-1);
    for(int i = 0; i < start; i++) {
        dst.push_back(src_buf[i]); //заполняем то, для чего не можем посчитать медиану
    }
    for(int i = start; i < end; i++) {
        median = getMedianInInterval(src_buf,i-start, i+start);
        dst.push_back(median);
    }
    median = getMedianInInterval(src_buf, end, src_buf.size()-1);
    for(int i = end; i < src_buf.size(); i++) {
        dst.push_back(src_buf[i]); //заполняем то, для чего не можем посчитать медиану
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
    for(int i = 0; i < start; i++) {
        dst.push_back(src_buf[i]); //заполняем то, для чего не можем посчитать среднее
    }
    for(int i = start; i < end; i++) {
        avrg = getAvrgInInterval(src_buf,i-start, i+start);
        dst.push_back(avrg);
    }
    avrg = getAvrgInInterval(src_buf, end, src_buf.size()-1);
    for(int i = end; i < src_buf.size(); i++) {
        dst.push_back(src_buf[i]); //заполняем то, для чего не можем посчитать среднее
    }
}
} //namespace filters
} // namespace math

