#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTime>
#include "vue_opengl.h"

class GLWidget : public QGLWidget {
	public:
	GLWidget(QWidget* parent = nullptr)
    : QGLWidget(parent), s(Environnement(new Air, new Eau, new Separateur(Vecteur3D(0.0,0.0,3.0),Vecteur3D(0.0,0.0,270.0))),&vue)
    {
        s.ajout_dalle(new Dalle(Vecteur3D(-90.0,-23.0,290.0),Vecteur3D(0.0,0.0,0.1),180.0,150.0,Vecteur3D(4.0,0.0,3.0)));
        s.ajout_sphere(new Sphere(Vecteur3D(-3.0,50.0,270.0),52.0));
        s.ajout_source(new Source(new GrainLJ_1(),Vecteur3D(-3.0,50.0,372.0)));
    }
	virtual ~GLWidget() {}
	private:
	virtual void initializeGL()                  override;
	virtual void resizeGL(int width, int height) override;
	virtual void paintGL()                       override;
	virtual void keyPressEvent(QKeyEvent* event) override;
	virtual void timerEvent(QTimerEvent* event)  override;
	void pause();
	VueOpenGL vue;
	int timerId;
	QTime chronometre;
	Systeme s;
};

#endif
