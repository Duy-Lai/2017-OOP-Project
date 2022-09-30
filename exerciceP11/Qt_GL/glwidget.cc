#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include "glwidget.h"

void GLWidget::initializeGL() {
  vue.init();
  timerId = startTimer(20);
}

void GLWidget::resizeGL(int width, int height) {
	glViewport(0, 0, width, height);
	QMatrix4x4 matrice;
	matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
	vue.setProjection(matrice);
}

void GLWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	s.dessine();
}

void GLWidget::keyPressEvent(QKeyEvent* event) {
	constexpr double petit_angle(5.0); // en degrés
	constexpr double petit_pas(1.0);
	switch (event->key()) {
		case Qt::Key_Left:
		vue.rotate(petit_angle, 0.0, -1.0, 0.0);
		break;
		case Qt::Key_Right:
		vue.rotate(petit_angle, 0.0, +1.0, 0.0);
		break;
		case Qt::Key_Up:
		vue.rotate(petit_angle, -1.0, 0.0, 0.0);
		break;
		case Qt::Key_Down:
		vue.rotate(petit_angle, +1.0, 0.0, 0.0);
		break;
		case Qt::Key_PageUp:
		case Qt::Key_W:
		vue.translate(0.0, 0.0,  petit_pas);
		break;
		case Qt::Key_PageDown:
		case Qt::Key_S:
		vue.translate(0.0, 0.0, -petit_pas);
		break;
		case Qt::Key_A:
		vue.translate( petit_pas, 0.0, 0.0);
		break;
		case Qt::Key_D:
		vue.translate(-petit_pas, 0.0, 0.0);
		break;
		case Qt::Key_R:
		vue.translate(0.0, -petit_pas, 0.0);
		break;
		case Qt::Key_F:
		vue.translate(0.0,  petit_pas, 0.0);
		break;
		case Qt::Key_Q:
		vue.rotate(petit_angle, 0.0, 0.0, -1.0);
		break;
		case Qt::Key_E:
		vue.rotate(petit_angle, 0.0, 0.0, +1.0);
		break;
		case Qt::Key_Home:
		vue.initializePosition();
		break;
		case Qt::Key_Space:
		pause();
		break;
	};
	updateGL();
}

void GLWidget::timerEvent(QTimerEvent* event) {
    Q_UNUSED(event);
    double dt = chronometre.restart() / 1000.0;
    s.evolue(dt);
    updateGL();
}

void GLWidget::pause() {
	if (timerId == 0) {
		timerId = startTimer(20);
		chronometre.restart();
	} else {
		killTimer(timerId);
		timerId = 0;
	}
}
