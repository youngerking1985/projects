#ifndef RUNNER_H
#define RUNNER_H

#include <QtGui/QMainWindow>
#include <Ribbon/include/QtitanRibbon.h>
#include <Ribbon/include/QtnRibbonQuickAccessBar.h>
#include <tinyxml.h>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QFontComboBox>
#include <QProgressBar>
#include <QScrollBar>
#include <QSlider>
#include <QDockWidget>
#include <QStackedWidget>
#include <QTabWidget>
#include "component/component.h"

class Runner : public RibbonMainWindow
{
	Q_OBJECT

public:
	Runner(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Runner();

private:
	QSize sizeHint() const;

private:
	void loadUIFromXml(TiXmlElement *xmlNode);
	bool isUse(TiXmlElement *xmlNode);
	void connectSignals(TiXmlElement *xmlNode, QObject *sender, QString defaultSignal = "");
	void loadItems(TiXmlElement *xmlNode, RibbonGroup *group, QActionGroup *actionGroup = 0);
	QObject *loadItem(TiXmlElement *itemNode);
	void loadMainButton(TiXmlElement *xmlNode);
	void loadStatusBar(TiXmlElement *xmlNode);
	void loadQuickAccess(TiXmlElement *xmlNode);
	void loadRightAction(TiXmlElement *xmlNode);
	void loadPage(TiXmlElement *xmlNode);
	void loadToolBar(TiXmlElement *xmlNode);
	void loadDockWidget(TiXmlElement *xmlNode);
	void loadTabCenterWidget(TiXmlElement *xmlNode);

	void loadWidget(QWidget *widget, TiXmlElement *xmlNode);
	void loadAbstractButton(QAbstractButton *button, TiXmlElement *xmlNode);
	void loadAbstractSlider(QAbstractSlider *abstractSlider, TiXmlElement *xmlNode);
	void loadToolBar(QToolBar *toolbar, TiXmlElement *xmlNode);

	QAction *loadAction(TiXmlElement *xmlNode);
	QMenu *loadMenu(TiXmlElement *xmlNode);
	QCheckBox *loadCheckBox(TiXmlElement *xmlNode);
	QRadioButton *loadRadioButton(TiXmlElement *xmlNode);
	QLineEdit *loadLineEdit(TiXmlElement *xmlNode);
	QComboBox *loadComboBox(TiXmlElement *xmlNode);
	QSpinBox *loadSpinBox(TiXmlElement *xmlNode);
	QFontComboBox *loadFontComboBox(TiXmlElement *xmlNode);
	QLabel *loadLable(TiXmlElement *xmlNode);
	QProgressBar *loadProgressBar(TiXmlElement *xmlNode);
	QScrollBar *loadScrollBar(TiXmlElement *xmlNode);
	QSlider *loadSlider(TiXmlElement *xmlNode);
	RibbonSliderPane *loadRibbonSliderPane(TiXmlElement *xmlNode);

	Qt::Alignment toAlignment(QString s);
	Qt::CheckState toCheckState(QString s);
	Qt::ToolButtonStyle toToolButtonStyle(QString s);
	QFontComboBox::FontFilters toFontFilters(QString s);
	Qt::Orientation toOrientation(QString s);
	QSlider::TickPosition toTickPosition(QString s);
	Qt::ToolBarAreas toToolBarAreas(QString s);
	Qt::ToolBarArea toToolBarArea(QString s);
	Qt::DockWidgetAreas toDockWidgetAreas(QString s);
	QDockWidget::DockWidgetFeatures toDockWidgetFeatures(QString s);
	QTabWidget::TabPosition toTabPosition(QString s);
	QTabWidget::TabShape toTabShape(QString s);

	void createOptions();
	void test(TiXmlElement *xmlNode);

	void loadComponents(TiXmlElement *xmlNode);

private slots:
	void options(QAction* action);
	void optionsFont(QAction* act);

private:
	int m_defaultFont;
	QAction *m_actionDefault;
	QObjectList m_components;
	
};

#endif // RUNNER_H
