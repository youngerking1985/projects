#pragma once

#include "../../layerwidget/qt_widget_layer.h"
#include "layerwidget_global.h"
#include <QtGui/QColor>
#include <QtGui/QPixmap>

using namespace layerwidget;

namespace layerwidget
{
	struct Geometry
	{
		QPointF pt;
		QList<QPointF> pts;
		double radius;
		double length,width;
		double start_angle,end_angle;
		enum Type{ None , Point , Picture , Polyline , Ellipse , Rect , Polygon } type;
	};

	struct Style 
	{
		QPixmap pixmap;
		int size;
		QString info;
		QColor border_color,fill_color;
		int border_width;
		Qt::PenStyle border_type;
		Style(){
			size = 6;
			border_color = fill_color = Qt::green;
			border_width = 1;
			border_type = Qt::SolidLine;
		}
	};

	struct Feature 
	{
		Feature(const Geometry & geometry = Geometry(),const Style & style = Style())
			:style(style)
		{
			geo = geometry;
		}
		Geometry geo;
		Style style;
	};

	class LAYERWIDGET_EXPORT Qt_geometry_layer :
		public Qt_widget_layer
	{
	public:
		Qt_geometry_layer(void);
		~Qt_geometry_layer(void);

		int get_next_geometry_id();

		void add_points(const QList<QPointF> & pts, const QColor & color,int size = 3);
		int add_ellipse(const QPointF & pt, double length, double width, const Style & style = Style());

		int add_geometry(Geometry geo, const Style & style);
		QMap<int,Feature> & get_geometries() { return m_geometries; }

		void clear();

		void draw();

		QPointF convert(const QPointF & pt);
		double convert(double dis);

		QMap<int,Feature> m_geometries;
		int m_next_geometry_id;
	};
}


