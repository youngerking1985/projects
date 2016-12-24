
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class DemoMainWindow : public QWidget
{
    Q_OBJECT
public:
    DemoMainWindow(const QString& productName, const QString& version);
    void setDemoWidget(QWidget* widget, QWidget* settings);
protected:
    void paintEvent(QPaintEvent* event);
protected slots:
    void aboutLinkActivated(const QString& link);
private:
    QLabel* m_infoButton;
    QWidget* m_demoWidget;
    QWidget* m_settings;
    QString m_productName;
    QString m_version;
    QHBoxLayout* hl;
};

