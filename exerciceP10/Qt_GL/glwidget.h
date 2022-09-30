#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QTime>
#include "vue_opengl.h"

class GLWidget : public QGLWidget {
	public:
	GLWidget(QWidget* parent = nullptr)
        : QGLWidget(parent), s(Environnement(new Air),&vue){
        {
            s.ajout_grain(new GrainLJ_1());
            s.ajout_grain(new GrainLJ_1(Vecteur3D(1.0)));
            s.ajout_grain(new GrainLJ_1(Vecteur3D(0.5,sqrt(3.0)/2.0)));
            s.ajout_grain(new GrainLJ_2(Vecteur3D(0.5,sqrt(3.0)/6.0,sqrt(6.0)/3.0)));
            s.ajout_dalle(new Dalle(Vecteur3D(4.0,-4.0,-0.9),Vecteur3D(0.0,0.0,0.1),8.0,8.0));
        }
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
