#include <gl\glew.h>
#include "layer_widget.h"
#include <qdebug>
#include <assert.h>
#include "swapbuffer_worker.h"
#include <QThreadPool>
#include "QtConcurrentMap"

namespace layer_wgt{


layer_widget::layer_widget()

{
	active_layer = -1;
}

layer_widget::~layer_widget()
{

}

#define TRANSLATE_EVENT(func, type)							\
layer_widget::##func##(##type## *e){							\
	if (active_layer == -1)									\
	{														\
		return;												\
	}														\
	if (active_layer < 0 || active_layer >= layers.count() )		\
	{														\
		active_layer = -1;									\
	}														\
	auto layer = layers.get_entry(active_layer);				\
	if (layer == 0)											\
	{														\
		return;												\
	}														\
	return layer->##func##(e);									\
}

void TRANSLATE_EVENT(mousePressEvent,QMouseEvent)
void TRANSLATE_EVENT(mouseReleaseEvent,QMouseEvent)
void TRANSLATE_EVENT(mouseMoveEvent,QMouseEvent)
void TRANSLATE_EVENT(mouseDoubleClickEvent,QMouseEvent)
void TRANSLATE_EVENT(wheelEvent,QWheelEvent)
void TRANSLATE_EVENT(keyPressEvent,QKeyEvent)
void TRANSLATE_EVENT(keyReleaseEvent,QKeyEvent)
void TRANSLATE_EVENT(enterEvent,QEvent)
void TRANSLATE_EVENT(leaveEvent,QEvent)

void layer_widget::initializeGL()
{
// 	QGLFormat ft = format();
// 	ft.setDoubleBuffer(true);
// 	setFormat(ft);
	bool res = format().doubleBuffer();
	assert(res);
//	setAutoBufferSwap(false);

	glewInit();

	glEnable(GL_MULTISAMPLE);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);

	glEnable(GL_LINE_SMOOTH);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

	//启用顶点数组
	glEnableClientState(GL_VERTEX_ARRAY);

	glEnable(GL_BLEND); 

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LINE_SMOOTH); 

	glEnable(GL_POINT_SMOOTH);

	glClearColor( 0.0, 0.0, 0.0, 0.0 );  
	glColor3f( 1.0, 1.0, 1.0 );  

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	//返回当前OpenGL实现的版本号
	printf("GL_VERSION:%s\n", glGetString(GL_VERSION));

	printf("GL_VENDOR:%s\n", glGetString(GL_VENDOR));

	printf("GL_RENDERER:%s\n", glGetString(GL_RENDERER));

	printf("GLU_VERSION:%s\n", glGetString(GLU_VERSION));

	printf("GLU_EXTENSIONS:%s\n", glGetString(GLU_EXTENSIONS));

	printf("GL_SHADING_LANGUAGE_VERSION:%s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	GLint nMaxStack = 0;
	glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH,&nMaxStack);
	printf("GL_MAX_MODELVIEW_STACK_DEPTH:%d\n", nMaxStack);

	if ( !GLEW_ARB_vertex_program )
	{
		fprintf(stderr, "ARB_vertex_programis missing!\n");
	}
	//获得OpenGL扩展信息s

	GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
	printf("GL_NUM_EXTENSIONS:%d\n", nExtensions);
}

// void layer_widget::paintGL()
// {
// 	glViewport( 0, 0, width(), height() );
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
// //	glClearColor(0.0, 0.0, 0.0, 1.0);
// 
// // 	glMatrixMode(GL_PROJECTION);
// // 	glLoadIdentity();
// // 
// // 	glMatrixMode(GL_MODELVIEW);
// // 	glLoadIdentity();
// 
// 	for (int i=0;i<layers.size();++i)
// 	{
// 		layers[i]->gl_draw();
// 	}
// 
// // 	QPainter p(this);
// // 	p.drawRect(50, 50, 50, 50);
// 
// // 	doneCurrent();
// // 	swapbuffer_down = false;
// // 	QThreadPool::globalInstance()->start( new swapbuffer_worker( this ), QThread::HighestPriority );
// 
// //	swapBuffers();
// }

void layer_widget::resizeGL( int width, int height )
{
 	glViewport(0, 0, (GLint)width, (GLint)height);  

	glMatrixMode( GL_PROJECTION );  
	glLoadIdentity();
  
	//定义剪裁面  
	rebuild_coor(); 

}

void layer_widget::attach(layer *l)
{
	if (l == 0)
	{
		return;
	}
	l->widget = this;
	layers.attach_entry(l);
}

void layer_widget::set_active_layer(layer *l)
{
	active_layer = get_layer_index(l);
}

int layer_widget::get_layer_index(layer *l)
{
	return layers.indexOf(l,0);
}

void layer_widget::paintEvent(QPaintEvent *event)
{
	
	//p.setRenderHint(QPainter::Antialiasing);

	makeCurrent();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glRotatef(-45, 0, 0, 1);

	glViewport( 0, 0, width(), height() );
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i=0;i<layers.size();++i)
	{
		layers[i]->gl_draw();
	}


// 	QList<render_layer_data> layers;
// 	for (int i=0; i<2; ++i)
// 	{
// 		render_layer_data layer;
// 		layer.layer = this->layers[i];
// 		layer.width = width();
// 		layer.height = height();
// 		layers << layer;
// 	}
// 
// 	doneCurrent();
// 	QThreadPool::globalInstance()->setMaxThreadCount(1);
// 	QFuture<void> res = QtConcurrent::map(layers, render_layer);
// 	res.waitForFinished();
// 
// 	makeCurrent();
// 
// 	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
// 	for (int i=0; i<layers.size(); ++i)
// 	{
// 		if (layers[i].framebuffer == 0)
// 		{
// 			continue;
// 		}
// 		glBindFramebuffer(GL_READ_FRAMEBUFFER, layers[i].framebuffer);
// 		glBlitFramebuffer(0, 0, width(), height(), 0, 0, width(), height(), GL_COLOR_BUFFER_BIT, GL_NEAREST);
// 		glDeleteFramebuffers(1, (GLuint *)&layers[i].framebuffer);
// 	}
	
// 	QPainter p;
// 	p.begin(this);
// 	p.setPen(QPen(Qt::red, 2));
// 	p.drawRect(50, 50, 100, 100);
// 	p.end();

	swapBuffers();
}

void layer_widget::render_layer(render_layer_data &layer)
{
	if (layer.layer == 0)
	{
		return;
	}

	layer.layer->widget->makeCurrent();
	GLuint renderbuffer = 0;
	glGenRenderbuffers(1, &renderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, layer.width, layer.height);

	GLuint framebuffer = 0;
	glGenFramebuffers(1, &framebuffer); 
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
	glViewport(0, 0, layer.width, layer.height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	layer.layer->gl_draw();

	layer.framebuffer = framebuffer;

	layer.layer->widget->doneCurrent();
}

}